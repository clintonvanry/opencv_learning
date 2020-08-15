#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    std::cout << "Display image in a window" << std::endl;

    // read the image
    auto img = imread("boy.jpg", IMREAD_COLOR);
    std::cout << "number of channel is " << img.channels() << std::endl;
    std::cout << "size of the image is " << img.size() << std::endl;

    auto windowName = "boy";

    // default is not to resize the window
    namedWindow(windowName,WINDOW_NORMAL);

    // this will display the image using a window with the name "boy"
    imshow(windowName,img);

    // this will keep the window open and wait for user input
    auto keyPressed = waitKey(0);
    std::cout << "key pressed is " << (char)keyPressed << std::endl;

    // good practice to close all windows.
    destroyAllWindows();

    std::cout << "closing all windows and exiting" << std::endl;

    return 0;
}
