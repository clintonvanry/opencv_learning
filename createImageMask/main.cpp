#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {

    // read the image from disk
    auto img = imread("boy.jpg", IMREAD_COLOR);

    std::cout << "Find the red pixels in the image" << std::endl;
    std::cout << "The red channel should have high intensity ( keep the range of pixel values from 150 to 255 )" << std::endl;
    std::cout << "The other 2 channels should have low intensity ( keep the range of pixel values in Blue and Green channels between 0 to 100)" << std::endl;

    Mat maskRed;
    // BGR
    inRange(img,Scalar(0,0,150), Scalar(100,100,255), maskRed);

    imshow("Original Image",img);
    imshow("Image that had red is displayed with white pixels",maskRed);
    waitKey(0);

    destroyAllWindows();

    return 0;
}
