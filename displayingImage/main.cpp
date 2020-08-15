#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    std::cout << "Display image in a window" << std::endl;
    // read the image
    auto img = imread("boy.jpg", IMREAD_COLOR);
    // this will display the image using a window with the name "boy"
    imshow("boy",img);
    // this will keep the window open and wait for user input
    waitKey(0);
    // good practice to close all windows.
    destroyAllWindows();

    std::cout << "closing all windows and exiting" << std::endl;

    return 0;
}
