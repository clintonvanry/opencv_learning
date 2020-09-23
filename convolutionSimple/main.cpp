#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    std::cout << "Convolution" << std::endl;

    auto img = imread("sample.jpg");

    int kernelSize3 = 3, KernelSize5 = 5;
    // Create a 5x5 kernel with all elements equal to 1
    Mat kernel3 = Mat::ones(kernelSize3, kernelSize3, CV_32F);
    Mat kernel5 = Mat::ones(KernelSize5, KernelSize5, CV_32F);

    // Normalize kernel so sum of all elements equals 1
    kernel3 = kernel3 / (float)(kernelSize3*kernelSize3);
    kernel5 = kernel5 / (float)(KernelSize5*KernelSize5);

    // Print kernel
    std::cout << "kernel3" << std::endl;
    std::cout << kernel3 << std::endl;
    std::cout << "kernel5" << std::endl;
    std::cout << kernel5 << std::endl;

    Mat result3, result5;

    // Apply filter
    filter2D(img, result3, -1 , kernel3, Point(-1, -1), 0, BORDER_DEFAULT);
    filter2D(img, result5, -1 , kernel5, Point(-1, -1), 0, BORDER_DEFAULT);

    imshow("original", img);
    imshow("convolution kernerl 3x3", result3);
    imshow("convolution kernerl 5x5", result5);

    waitKey(0);

    destroyAllWindows();
    return 0;
}
