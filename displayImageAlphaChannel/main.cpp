#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {

    auto img = imread("panther.png", IMREAD_UNCHANGED);
    std::cout << "number of channels:" << img.channels() << std::endl;
    std::cout << "size of image:" << img.size() << std::endl;

    // retrieve the BGR channels
    Mat imgPNGChannels[4];
    Mat imgBGROnly;
    split(img, imgPNGChannels);

    merge(imgPNGChannels,3,imgBGROnly);
    Mat imgMask = imgPNGChannels[3];

    auto imageBGRWindowName = "pather without mask. BGR";
    auto imageAlphaWindowName = "pather mask";
    auto imageFullWindowName = "pather";

    imshow(imageBGRWindowName, imgBGROnly);
    imshow(imageAlphaWindowName, imgMask);
    imshow(imageFullWindowName, img);
    waitKey(0);

    destroyAllWindows();

    return 0;
}
