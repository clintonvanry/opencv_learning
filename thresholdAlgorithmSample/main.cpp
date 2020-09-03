#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;


int main() {
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
