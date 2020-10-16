#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
// as a reference on how to do this.
// https://medium.com/fnplus/blue-or-green-screen-effect-with-open-cv-chroma-keying-94d4a6ab2743

/*
 * Controls: You can build a simple interface using HighGUI. It should contain the following parts.

   1. Color Patch Selector : The interface should show a video frame and the user should be allowed to select a patch of green screen from the background.
      For simplicity, this patch can be a rectangular patch selected from a single frame. However,
      it is perfectly find to build an interface where you select multiple patches from one or more frames of the video.

   2. Tolerance slider : This slider will control how different the color can be from the mean of colors sampled in the previous step
      to be included in the green background.

   3. Softness slider (Optional): This slider will control the softness of the foreground mask at the edges.

   4. Color cast slider (Optional): In a green screen environment, some of the green color also gets cast on the subject.
   There are some interesting ways the color cast can be reduced, but during the process of removing the color cast some artifacts are get introduced.
   So, this slider should control the amount of color cast removal we want.

 */

Mat backgroundImage;
Mat astroidImageFromVideo;
Mat astroidImageFromVideoClone;
Mat patchFromAsteroidImage;
Mat blendedImage;
Size blurKernel(0,0);
Size videoFrameSize(0,0);
int videoFps = 25;

Point mousePointLBUTTONDOWN(0,0);
Point mousePointLBUTTONUP(0,0);
bool mousePressed = false;

Scalar lowerHSV(120,255,255);
Scalar higherHSV(0,0,0);
Scalar sampleLowerHSV(120,255,255);
Scalar sampleHigherHSV(0,0,0);
Scalar meanOfPatch(0,0,0);
int previousTrackbarPosition = 0;

int scaleFactor =0;
void PrintVideoProperties(const VideoCapture& videoCapture);
void GrabFrameFromVideo(VideoCapture& videoCapture);
void Tolerance(int trackbarPosition, void* userData);
void Softness(int trackbarPosition, void* userData);
void SelectPatch(int event, int x, int y, int flags, void *userdata);
void resetImage();
void SetChromaLevelsFromPath();
void SetChromaLevelsFromTrackbarValue(int trackbarPosition);
void BlendImageWithChromaLevels(bool showOutput = true);
void RecordVideo();

int main() {
    std::cout << "Chroma keying example" << std::endl;
    std::cout << "Please select a region of interest on the asteriod image" << std::endl;
    std::cout << "Please use the slider of Tolerance to adjust. I found the tolerance level 67 to be quite good." << std::endl;
    std::cout << "Please use the slider of Softness to adjust. I found the softness level 39 to be quite good." << std::endl;
    std::cout << "Once you have finished adjusting. Press the letter 'r' to create the output video." << std::endl;
    std::cout << "Press the escape key to exit." << std::endl;


    backgroundImage = imread("background.jpg",IMREAD_COLOR);
    std::string videoFilename = "greenscreen-asteroid.mp4";
    
    // check to see if the video can be used and is in the directory to be read.
    VideoCapture videoCapture(videoFilename);
    if(!videoCapture.isOpened())
    {
        std::cout << "Failed to open video file" << std::endl;
        videoCapture.release();
        return -1;
    }

    PrintVideoProperties(videoCapture);
    GrabFrameFromVideo(videoCapture);
    videoCapture.release();

    std::string astroidWindow = "Asteroid";
    std::string astroidToleranceTrackbarName = "Tolerance";
    std::string astroidSoftnessTrackbarName = "Softness";
    namedWindow(astroidWindow,WINDOW_AUTOSIZE);

    createTrackbar(astroidToleranceTrackbarName,astroidWindow,&scaleFactor,100,Tolerance);
    setTrackbarMin(astroidToleranceTrackbarName,astroidWindow,0);
    setTrackbarMax(astroidToleranceTrackbarName,astroidWindow,100);

    createTrackbar(astroidSoftnessTrackbarName,astroidWindow,&scaleFactor,100,Softness);
    setTrackbarMin(astroidSoftnessTrackbarName,astroidWindow,0);
    setTrackbarMax(astroidSoftnessTrackbarName,astroidWindow,100);

    setMouseCallback(astroidWindow,SelectPatch);

    imshow(astroidWindow,astroidImageFromVideo);
    int keycode =  waitKey(0) & 0xFF;
    // letter r to do perform the recording of the video
    if(keycode == 114)
    {
        RecordVideo();
    }

    // clean up

    destroyAllWindows();
    return 0;
}


void GrabFrameFromVideo(VideoCapture& videoCapture)
{
    // go to the 4th second and grab a frame
    int frameAt4thSecond = 100;
    videoCapture.set(CAP_PROP_POS_FRAMES,frameAt4thSecond);
    videoCapture >> astroidImageFromVideo;
    astroidImageFromVideoClone = astroidImageFromVideo.clone();
    // set back to position zero
    videoCapture.set(CAP_PROP_POS_FRAMES,0);
}
void Tolerance(int trackbarPosition, void* userData)
{
    std::cout << trackbarPosition << std::endl;
    // reset back to the sample values
    lowerHSV = sampleLowerHSV;
    higherHSV = sampleHigherHSV;
    if(trackbarPosition == 0){
        previousTrackbarPosition = 0;
    }
    else{
        int trackbarValue = trackbarPosition - previousTrackbarPosition;
        SetChromaLevelsFromTrackbarValue(trackbarValue);
    }

    std::cout << lowerHSV << std::endl;
    std::cout << higherHSV << std::endl;
    std::cout << "sample" << std::endl;
    std::cout << sampleLowerHSV << std::endl;
    std::cout << sampleHigherHSV << std::endl;

    BlendImageWithChromaLevels();

}
void Softness(int trackbarPosition, void* userData)
{
    std::cout << trackbarPosition << std::endl;

    // has to be greater than zero and divisible by 2
    if(trackbarPosition % 2 && trackbarPosition > 0){
        blurKernel = Size(trackbarPosition,trackbarPosition);
    }

    BlendImageWithChromaLevels();
}
void SelectPatch(int event, int x, int y, int flags, void *userdata)
{

    if(event == EVENT_LBUTTONDOWN)
    {
        if(mousePointLBUTTONDOWN != Point(x,y))
        {
            mousePointLBUTTONDOWN =  Point(x,y);
            mousePointLBUTTONUP = Point(x,y);
            mousePressed = true;
            resetImage();
        }
    }
    else if(event == EVENT_MOUSEMOVE)
    {
        if(mousePressed)
        {
            resetImage();
            mousePointLBUTTONUP = Point(x,y);
            line(astroidImageFromVideo,mousePointLBUTTONDOWN,Point(x,y),Scalar(0,0,255),2);
            imshow("Asteroid", astroidImageFromVideo);
        }
    }
    else if (event == EVENT_LBUTTONUP)
    {
        mousePointLBUTTONUP = Point(x,y);
        mousePressed = false;
        resetImage();
        Rect patchROI = Rect(mousePointLBUTTONDOWN,mousePointLBUTTONUP);
        rectangle(astroidImageFromVideo, patchROI, Scalar(255,0,0),2);

        Mat image_hsv;
        cvtColor(astroidImageFromVideoClone, image_hsv, COLOR_BGR2HSV);

        patchFromAsteroidImage = image_hsv(patchROI);
        //imshow("patch", patchFromAsteroidImage);
        imshow("Asteroid", astroidImageFromVideo);
        SetChromaLevelsFromPath();
        BlendImageWithChromaLevels();

    }


}
void SetChromaLevelsFromTrackbarValue(int trackbarPosition)
{
    std::cout << "Trackbar value: " << trackbarPosition << std::endl;
    int min = 0, max = 0;
    // update the hue values
    min = lowerHSV[0];
    max = higherHSV[0];
    if(min - trackbarPosition < 0){
        min = 0;
    }
    else{
        min -= trackbarPosition;
    }
    if(max + trackbarPosition >180){
        max = 180;
    }
    else{
        max += trackbarPosition;
    }
    lowerHSV[0] = min;
    higherHSV[0] = max;

    // update the saturation
    min = lowerHSV[1];
    max = higherHSV[1];
    if(min - trackbarPosition < 0){
        min = 0;
    }
    else{
        min -= trackbarPosition;
    }
    if(max + trackbarPosition >255){
        max = 255;
    }
    else{
        max += trackbarPosition;
    }
    lowerHSV[1] = min;
    higherHSV[1] = max;

    // update the value
    min = lowerHSV[2];
    max = higherHSV[2];
    if(min - trackbarPosition < 0){
        min = 0;
    }
    else{
        min -= trackbarPosition;
    }
    if(max + trackbarPosition >255){
        max = 255;
    }
    else{
        max += trackbarPosition;
    }
    lowerHSV[2] = min;
    higherHSV[2] = max;

}
void SetChromaLevelsFromPath(){

    std::vector<Mat> hsvChannels(3);
    split(patchFromAsteroidImage, hsvChannels);

    double min = 0, max =0;
    // hue
    minMaxLoc(hsvChannels[0],&min, &max);
    std::cout << "min: " << min << " max: " << max  << std::endl;
    lowerHSV[0] = (min -2) < 0 ? min : min-2 ;
    higherHSV[0] = max + 2;

    // sat
    minMaxLoc(hsvChannels[1],&min, &max);
    std::cout << "min: " << min << " max: " << max  << std::endl;
    lowerHSV[1] = (min -100) < 0 ? min : min -100;
    higherHSV[1] = max + 100;

    // value
    minMaxLoc(hsvChannels[2],&min, &max);
    std::cout << "min: " << min << " max: " << max  << std::endl;
    lowerHSV[2] = min;
    higherHSV[2] = max;

    // mean
    meanOfPatch = mean(patchFromAsteroidImage);
    std::cout << "mean: " <<meanOfPatch << std::endl;

    // store a history of this sample
    sampleLowerHSV = lowerHSV;
    sampleHigherHSV = higherHSV;

}
void BlendImageWithChromaLevels(bool showOutput)
{
    Mat image_hsv;
    cvtColor(astroidImageFromVideoClone, image_hsv, COLOR_BGR2HSV);

    std::cout << lowerHSV << std::endl;
    std::cout << higherHSV << std::endl;

    Mat background_mask;
    inRange(image_hsv, lowerHSV, higherHSV, background_mask);

    blendedImage = astroidImageFromVideoClone.clone();

    if(blurKernel.height > 0)
    {
        GaussianBlur(background_mask, background_mask, blurKernel,0,0);
    }

    backgroundImage.copyTo(blendedImage, background_mask);
    if(showOutput)
    {
        imshow("Blended Image", blendedImage);
    }

}
void resetImage()
{
    astroidImageFromVideoClone.copyTo(astroidImageFromVideo);
}
void PrintVideoProperties(const VideoCapture& videoCapture)
{
    int width=0, height=0, fps=0;

    width = videoCapture.get(CAP_PROP_FRAME_WIDTH);
    height = videoCapture.get(CAP_PROP_FRAME_HEIGHT);
    fps = videoCapture.get(CAP_PROP_FPS);
    std::cout << "Video width: " << width << std::endl;
    std::cout << "Video height: " << height << std::endl;
    std::cout << "Video duration: " << videoCapture.get(CAP_PROP_FRAME_COUNT) << std::endl;
    std::cout << "Video fps: " << fps  << std::endl;

    // needed for the recording
    videoFrameSize = Size(width,height);
    videoFps = fps;
}
void RecordVideo()
{
    std::string videoFilename = "./greenscreen-asteroid.mp4";
    std::string outputVideoFilename = "./output.mp4";

    // check to see if the video can be used and is in the directory to be read.
    VideoCapture videoReader(videoFilename);
    VideoWriter  videoWriter(outputVideoFilename,VideoWriter::fourcc('M','J','P','G'),videoFps,videoFrameSize);

    int counter = 0;
    while(videoReader.isOpened())
    {
        videoReader >> astroidImageFromVideoClone;
        if(astroidImageFromVideoClone.empty())
        {
            break;
        }

        // apply the chroma levels and blur
        BlendImageWithChromaLevels(false);

        // save to disk
        videoWriter.write(blendedImage);
        imshow("VideoFrame", blendedImage);
        waitKey(25);
        counter++;

        std::cout << "Video Frame Number: " << counter << std::endl;

    }

    //clean up
    videoReader.release();
    videoWriter.release();
}