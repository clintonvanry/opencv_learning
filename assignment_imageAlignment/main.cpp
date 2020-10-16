#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    std::cout << "Image alignment" << std::endl;

    Mat img = imread("emir.jpg",IMREAD_GRAYSCALE);
    // Find the width and height of the color image
    Size sz = img.size();
    int height = sz.height / 3;
    int width = sz.width;

    std::cout << sz << std::endl;

    // Extract the three channels from the gray scale image
    std::vector<Mat>channels;
    channels.push_back(img( Rect(0, 0,         width, height)));
    channels.push_back(img( Rect(0, height,    width, height)));
    channels.push_back(img( Rect(0, 2*height,  width, height)));

    Mat blue = channels[0];
    Mat green = channels[1];
    Mat red = channels[2];

    imshow("original",img);
    imshow("blue", blue);
    imshow("green", green);
    imshow("red", red);

    waitKey(0);

    return 0;
}
