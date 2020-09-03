#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

int main() {
    std::cout << "Morphological Operations" << std::endl;
    std::cout << "Dilation is used to merge or expand white regions which may be close to each other and" << std::endl;
    std::cout << "Erosion is used to separate or shrink white regions" << std::endl;

    auto imgDilation = imread("dilation_example.jpg", IMREAD_COLOR);
    imshow("Original Dilation Image", imgDilation);

    int kSize = 7;
    Mat kernel1 = getStructuringElement(cv::MORPH_ELLIPSE,Size(kSize,kSize));
    imshow("kernel1", 255*kernel1);

    Mat imageDilated;
    dilate(imgDilation,imageDilated,kernel1);
    imshow("Dilated image", imageDilated);

    kSize = 3;
    Mat kernel2 = getStructuringElement(cv::MORPH_ELLIPSE,Size(kSize,kSize));
    imshow("kernel1", 255*kernel2);
    Mat imageDilated2;
    dilate(imgDilation,imageDilated2,kernel2,Point(-1,-1),2);
    imshow("Dilated image 2 ", imageDilated2);

    auto imgErode = imread("erosion_example.jpg", IMREAD_COLOR);
    imshow("Original Erosion Image", imgErode);

    Mat imageEroded;
    erode(imgErode, imageEroded,kernel1);
    imshow("Eroded Image", imageEroded);

    Mat imageEroded2;
    erode(imgErode, imageEroded2,kernel2);
    imshow("Eroded Image 2", imageEroded2);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
