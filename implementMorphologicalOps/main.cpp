#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

using namespace  cv;

void dialationExample();
void erosionExample();

int main() {


    //dialationExample();
    erosionExample();





    //waitKey(0);
    destroyAllWindows();

    return 0;
}

void dialationExample()
{
    Mat demoImage = Mat::zeros(Size(10,10), CV_8U);
    namedWindow("Demo Image", WINDOW_NORMAL);


    std::cout << "Adding random white blocks to the image" << std::endl;
    demoImage.at<uchar>(0,1) = 1;
    demoImage.at<uchar>(9,0) = 1;
    demoImage.at<uchar>(8,9) = 1;
    demoImage.at<uchar>(2,2) = 1;
    demoImage(Range(5,8), Range(5,8)).setTo(1);
    std::cout <<  "demo image with with blocks" << std::endl;
    std::cout << demoImage << std::endl;
    imshow("Demo Image", demoImage *255);
    waitKey(0);

    Mat element = getStructuringElement(MORPH_CROSS, Size(3,3));
    std::cout << "structured element:" << std::endl;
    std::cout <<  element << std::endl;

    int ksize = element.size().height;
    int height, width;
    height = demoImage.size().height;
    width = demoImage.size().width;


    Mat dilatedCrossKernel;
    dilate(demoImage, dilatedCrossKernel, element);
    std::cout << "expected output for dilation:" << std::endl;
    std::cout << dilatedCrossKernel << std::endl;
    namedWindow("cv dilated image", WINDOW_NORMAL);
    imshow("cv dilated image", dilatedCrossKernel *255);
    waitKey(0);

    // task
    int border = ksize/2;
    Mat paddedDemoImage = Mat::zeros(Size(height + border*2, width + border*2),CV_8UC1);
    copyMakeBorder(demoImage,paddedDemoImage,border,border,border,border,BORDER_CONSTANT,0);
    Mat paddedDilatedImage = paddedDemoImage.clone();
    Mat mask;
    Mat resizedFrame;

    std::cout << "paddedDemoImage:" << std::endl;
    std::cout << paddedDemoImage << std::endl;

    VideoWriter dilationVideoWriter("dilationScratch.avi",VideoWriter::fourcc('M','J','P','G'), 10, Size(50,50));
    for (int h_i = border; h_i < height + border; h_i++){
        for (int w_i = border; w_i < width + border; w_i++){
            ///
            /// YOUR CODE HERE
            ///
            Mat roi = paddedDemoImage(Range(h_i-border,h_i+border+1),
                                      Range(w_i-border,w_i+border+1));

            std::cout << roi << std::endl;

            bitwise_and(roi, element, mask);
            std::cout << "mask output:" << std::endl;
            std::cout << mask << std::endl;


            double minVal = 0, maxVal = 0;
            minMaxIdx(mask,&minVal, &maxVal);
            paddedDilatedImage.at<uchar>(h_i,w_i) = maxVal;

            // Resize output to 50x50 before writing it to the video
            ///
            /// YOUR CODE HERE
            ///
            resize(paddedDilatedImage*255, resizedFrame,Size(50,50), 0, 0, INTER_NEAREST);


            // Convert resizedFrame to BGR before writing
            ///
            /// YOUR CODE HERE
            ///
            resizedFrame.convertTo(resizedFrame,CV_8UC3);
            cvtColor(resizedFrame,resizedFrame, COLOR_GRAY2RGB);
            dilationVideoWriter.write(resizedFrame);

        }
    }

    // Release the VideoWriter object
    ///
    /// YOUR CODE HERE
    ///
    dilationVideoWriter.release();


    // Display final image (cropped)
    ///
    /// YOUR CODE HERE
    ///
    // Crop out the original dimension from the padded output image
    Mat dilatedImage = paddedDilatedImage(Range(border,border+height),Range(border,border+width));


    namedWindow("dilatedImage", WINDOW_NORMAL);
    imshow("dilatedImage",dilatedImage*255);
    waitKey(0);


}
void erosionExample()
{
    Mat demoImage = Mat::zeros(Size(10,10), CV_8U);

    std::cout << "Adding random white blocks to the image" << std::endl;
    demoImage.at<uchar>(0,1) = 1;
    demoImage.at<uchar>(9,0) = 1;
    demoImage.at<uchar>(8,9) = 1;
    demoImage.at<uchar>(2,2) = 1;
    demoImage(Range(5,8), Range(5,8)).setTo(1);
    std::cout <<  "demo image with with blocks" << std::endl;
    std::cout << demoImage << std::endl;
    namedWindow("Demo Image", WINDOW_NORMAL);
    imshow("Demo Image", demoImage *255);
    waitKey(0);

    Mat element = getStructuringElement(MORPH_CROSS, Size(3,3));
    std::cout << "structured element:" << std::endl;
    std::cout <<  element << std::endl;

    int ksize = element.size().height;
    int height, width;
    height = demoImage.size().height;
    width = demoImage.size().width;

    Mat ErodedCrossKernel;
    erode(demoImage, ErodedCrossKernel, element);
    std::cout << "expected output for erosion:" << std::endl;
    std::cout << ErodedCrossKernel << std::endl;
    namedWindow("cv eroded image", WINDOW_NORMAL);
    imshow("cv eroded image", ErodedCrossKernel*255);
    waitKey(0);

    int border = ksize/2;
    Mat paddedDemoImage = Mat::zeros(Size(height + border*2, width + border*2),CV_8UC1);
    copyMakeBorder(demoImage,paddedDemoImage,border,border,border,border,BORDER_CONSTANT,0);
    Mat mask;
    Mat resizedFrame;
    Mat paddedErodedImage = paddedDemoImage.clone();

    VideoWriter erosionVideoWriter("erosionScratch.avi",VideoWriter::fourcc('M','J','P','G'), 10, Size(50,50));

    for (int h_i = border; h_i < height + border; h_i++){
        for (int w_i = border; w_i < width + border; w_i++){
            ///
            /// YOUR CODE HERE
            ///
            Mat roi = paddedDemoImage(Range(h_i-border,h_i+border+1),
                                      Range(w_i-border,w_i+border+1));

            std::cout << roi << std::endl;

            bitwise_and(roi, element, mask);
            //std::cout << "mask output:" << std::endl;
            //std::cout << mask << std::endl;


            double minVal = 0, maxVal = 0;
            minMaxIdx(mask,&minVal, &maxVal);
            //std::cout << "(" << h_i << "," << w_i << ") " << "min:" << minVal << " max: " << maxVal << std::endl;

            // if we are the same leave it alone
            if(cv::sum(mask) == sum(element)){
                paddedErodedImage.at<uchar>(h_i, w_i) = maxVal;
            }
            else {
                paddedErodedImage.at<uchar>(h_i, w_i) = minVal;
            }


            // Resize output to 50x50 before writing it to the video
            ///
            /// YOUR CODE HERE
            ///
            resize(paddedErodedImage*255, resizedFrame,Size(50,50), 0, 0, INTER_NEAREST);


            // Convert resizedFrame to BGR before writing
            ///
            /// YOUR CODE HERE
            ///
            resizedFrame.convertTo(resizedFrame,CV_8UC3);
            cvtColor(resizedFrame,resizedFrame, COLOR_GRAY2RGB);
            erosionVideoWriter.write(resizedFrame);

        }
    }
    // Release the VideoWriter object
    ///
    /// YOUR CODE HERE
    ///
    erosionVideoWriter.release();

    // Display final image (cropped)
    ///
    /// YOUR CODE HERE
    ///
    Mat erodedImage = paddedErodedImage(Range(border,border+height),Range(border,border+width));

    std::cout << "eroded cropped output:" << std::endl;
    std::cout << erodedImage << std::endl;

    namedWindow("erodedImage", WINDOW_NORMAL);
    imshow("erodedImage",erodedImage*255);
    waitKey(0);

}