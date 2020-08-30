#include <iostream>
#include <string>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

int maxScaleUp = 100;
int scaleFactor = 1;
int scaleType = 0;
int maxType = 1;
Mat imgSource;

std::string windowName = "Resize Image";
std::string trackbarValue = "Scale";
std::string trackbarType = "Type: \n 0: Scale Up \n 1: Scale Down";

void scaleImage(int, void*);

int main() {
    std::cout << "read image" << std::endl;

    // load an image
    // cmake copies the truth.png to the debug directory
    imgSource = imread("truth.png");
    std::cout << imgSource.size() << std::endl;

    // Create a window to display results
    namedWindow(windowName, WINDOW_AUTOSIZE);

    createTrackbar(trackbarValue, windowName, &scaleFactor, maxScaleUp, scaleImage);
    createTrackbar(trackbarType, windowName, &scaleType, maxType, scaleImage);

    scaleImage(25,nullptr);

    const int ESC_KEYBOARD_CODE = 27;
    while(true){
        auto keyBoardCode= waitKey(20)& 0xFF;
        if(keyBoardCode == ESC_KEYBOARD_CODE)
        {
            break;
        }
    }
    // cleanup
    destroyAllWindows();

    return 0;
}

void scaleImage(int, void*){
    double scaleFactorDouble;

    if(scaleType == 0){
        scaleFactorDouble = 1 + scaleFactor/100.0;
        std::cout << "Scale up by: " << scaleFactorDouble << std::endl;
    }
    else{
        scaleFactorDouble = 1 - scaleFactor/100.0;
        // scaling down to zero causes an exception
        // this is not needed for scaling up as zero means original size.
        if(scaleFactorDouble == 0){
            scaleFactorDouble = 0.01;
        }
        std::cout << "Scale down by: " << scaleFactorDouble << std::endl;
    }


    Mat scaledImage;
    resize(imgSource, scaledImage, Size(), scaleFactorDouble, scaleFactorDouble, INTER_LINEAR);
    imshow(windowName, scaledImage);
}