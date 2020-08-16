#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {

    std::cout << "Start" << std::endl;
    auto img = imread("musk.jpg", IMREAD_COLOR);

    imshow("Original Image",img);
    waitKey(0);

    destroyAllWindows();

    return 0;
}
