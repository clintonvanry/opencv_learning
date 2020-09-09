#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;

void Quiz3();

int main() {

    Quiz3();

    std::cout << "Threshold algorithms" << std::endl;
    auto imgSource = imread("threshold.png", IMREAD_GRAYSCALE);

    // Set threshold and maximum value
    auto thresh = 100;
    auto maxValue = 150;

    // threshold binary
    Mat binImg;
    auto start = std::chrono::high_resolution_clock::now();
    threshold(imgSource,binImg,thresh,maxValue, THRESH_BINARY);
    auto stop =std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "time taken " << duration.count() << " microseconds." << std::endl;

    Mat binInverseImg;
    start = std::chrono::high_resolution_clock::now();
    threshold(imgSource,binInverseImg,thresh,maxValue, THRESH_BINARY_INV);
    stop =std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "time taken " << duration.count() << " microseconds." << std::endl;

    Mat binTruncateImg;
    start = std::chrono::high_resolution_clock::now();
    threshold(imgSource,binTruncateImg,thresh,maxValue, THRESH_TRUNC);
    stop =std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "time taken " << duration.count() << " microseconds." << std::endl;

    Mat threshZeroImg;
    start = std::chrono::high_resolution_clock::now();
    threshold(imgSource,threshZeroImg,thresh,maxValue, THRESH_TOZERO);
    stop =std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "time taken " << duration.count() << " microseconds." << std::endl;

    Mat threshInverseZeroImg;
    start = std::chrono::high_resolution_clock::now();
    threshold(imgSource,threshInverseZeroImg,thresh,maxValue, THRESH_TOZERO_INV);
    stop =std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "time taken " << duration.count() << " microseconds." << std::endl;

    imshow("Original", imgSource);
    imshow("Binary Threshold", binImg);
    imshow("Binary Inverse Threshold", binInverseImg);
    imshow("Truncate Threshold", binTruncateImg);
    imshow("Zero Threshold", threshZeroImg);
    imshow("Inverse Zero Threshold", threshInverseZeroImg);

    waitKey(0);

    destroyAllWindows();

    return 0;
}

void Quiz3()
{
    Mat src = Mat::zeros(10,10,CV_8U);
    Mat dst;

    src.at<uchar>(1,1) = 120;
    src.at<uchar>(1,2) = 127;
    src.at<uchar>(1,3) = 127;
    src.at<uchar>(1,7) = 128;
    src.at<uchar>(1,8) = 128;
    src.at<uchar>(1,9) = 255;


    threshold(src,dst,127,255,THRESH_BINARY);

    std::cout << "dst" << std::endl;
    std::cout << dst << std::endl;

    imshow("dst", dst);
    auto k = waitKey(0);
    std::cout << k << std::endl;
}
