#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {

    // this grayscale image but as we changing the pixel with colour read it as colour image to fix matrix
    auto img = imread("number_zero.jpg", IMREAD_COLOR);
    std::cout << "number of channels: " << img.channels() << std::endl;
    std::cout << "size of image" << img.size() << std::endl;

    // get channel 1
    Mat imgChannels[3];
    split(img,imgChannels);
    std::cout << imgChannels[0] << std::endl;

    // print out a pixel
    auto pixelAtPositionZero = img.at<Vec3b>(0,0);
    std::cout << pixelAtPositionZero << std::endl;

    auto windowName = "numberZero";
    namedWindow(windowName, WINDOW_NORMAL);
    imshow(windowName, img);
    waitKey(0);

    std::cout << "modify pixels in the image" << std::endl;
    // modify a set of pixels
    // set it to yellow
    img.at<Vec3b>(0,0)= Vec3b(0,255,255);
    // set it to cyan
    img.at<Vec3b>(1,1)= Vec3b(255,255,0);
    // set it to magenta
    img.at<Vec3b>(2,2)= Vec3b(255,0,255);
    imshow(windowName, img);
    waitKey(0);

    std::cout << "modify range of pixels in the image" << std::endl;
    img(Range(4,7),Range(0,3)).setTo(Scalar(255,0,0));
    img(Range(7,10),Range(0,3)).setTo(Scalar(0,255,0));
    img(Range(10,13),Range(0,3)).setTo(Scalar(0,0,255));
    imshow(windowName, img);
    waitKey(0);

    destroyAllWindows();

    return 0;
}
