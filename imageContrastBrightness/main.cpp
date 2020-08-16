#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    // read the image from disk
    auto img = imread("boy.jpg", IMREAD_COLOR);
    std::cout << "Original image dataType:" << typeToString(img.type())   << std::endl;

    // convert this to float
    auto imgContrastClone = img.clone();
    double scalingFactor = 1/255.0;
    double shift = 0;
    imgContrastClone.convertTo(imgContrastClone, CV_32FC3, scalingFactor, shift);

    std::cout << "Contrast: The difference in intensity between the brightest and darkest regions of a given image. "
                 "Higher the difference, higher is the contrast. The maximum contrast of an image is also known as Dynamic Range. "
                 "In an image with good contrast, objects are easily discernible." << std::endl;
    std::cout << "Create a contrast by 30%" << std::endl;
    double contrastPercentage = 30.0;
    imgContrastClone.convertTo(imgContrastClone, CV_64F);
    imgContrastClone = imgContrastClone * (1+ contrastPercentage/100.0);
    std::cout << "Contrast image dataType:" << typeToString(imgContrastClone.type())   << std::endl;

    std::cout << "Brightness is a measure of light falling on the scene. "
                 "In RGB color space, it can be thought of as the arithmetic mean of the R, G and B color values. "
                 "To make an image brighter, the intensity values should be increased by some offset and vice-versa." << std::endl;
    std::cout << "Increase the brightness by 50%" << std::endl;
    Mat brightImage;
    int brightnessOffset = 50;
    // split to 3 channels
    Mat brightnessChannels[3];
    split(img,brightnessChannels);
    for(auto i=0; i < img.channels(); i++){
        add(brightnessChannels[i],brightnessOffset,brightnessChannels[i]);
    }
    merge(brightnessChannels,img.channels(), brightImage);
    std::cout << "Brightness image dataType:" << typeToString(brightImage.type())   << std::endl;

    imshow("Original", img);
    imshow("contrast 30%", imgContrastClone);
    imshow("brightness 50%", brightImage);
    waitKey(0);

    destroyAllWindows();

    return 0;
}
