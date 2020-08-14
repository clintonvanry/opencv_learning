#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;

std::string type2str(uint type) {
    std::string r;

    uchar depth = type & (unsigned int) CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (type >> (unsigned int) CV_CN_SHIFT);

    switch (depth) {
        case CV_8U:
            r = "8U";
            break;
        case CV_8S:
            r = "8S";
            break;
        case CV_16U:
            r = "16U";
            break;
        case CV_16S:
            r = "16S";
            break;
        case CV_32S:
            r = "32S";
            break;
        case CV_32F:
            r = "32F";
            break;
        case CV_64F:
            r = "64F";
            break;
        default:
            r = "User";
            break;
    }

    r += "C";
    r += (std::to_string(chans + '0'));

    return r;
}

int main() {

    auto imagePath = "number_zero.jpg";
    auto testImage = imread(imagePath, 0);

    std::cout << "Display image as matrix" << std::endl;
    std::cout<< testImage << std::endl;

    std::cout << "Data type = " << type2str(testImage.type()) << std::endl;
    std::cout << "Image Dimensions = " << testImage.size();
    return 0;
}
