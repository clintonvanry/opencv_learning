#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {

    std::cout << "Start with face image" << std::endl;
    auto img = imread("musk.jpg", IMREAD_COLOR);
    std::cout << "musk image size:" << img.size() << " channels:" << img.channels() << " dataType:" << typeToString(img.type()) << std::endl;

    std::cout << "convert to float for all 3 channels" << std::endl;
    img.convertTo(img, CV_32FC3);
    std::cout << "read in as 8 bit so divide by 255 to get the floating points" << std::endl;
    img = img / 255.0;
    std::cout << "img size:" << img.size() << " channels:" << img.channels() << " dataType:" << typeToString(img.type()) << std::endl;

    std::cout << "read the sunglass image." << std::endl;
    // note it it is unchanged as we want to read the alpha channel as well
    auto sunglassImg = imread("sunglass.png", IMREAD_UNCHANGED);
    std::cout << "sunglass image size:" << img.size() << " channels:" << img.channels() << " dataType:" << typeToString(img.type()) << std::endl;
    sunglassImg.convertTo(sunglassImg, CV_32F);
    std::cout << "read in as 8 bit so divide by 255 to get the floating points" << std::endl;
    sunglassImg /= 255.0;
    std::cout << "sunglass size:" << sunglassImg.size() << " channels:" << sunglassImg.channels() << " dataType:" << typeToString(sunglassImg.type()) << std::endl;

    std::cout << "resize sunglass image" << std::endl;
    auto resizeSunglassImg = sunglassImg.clone();
    resize(sunglassImg, resizeSunglassImg,Size(), 0.5, 0.5, InterpolationFlags::INTER_LINEAR);
    std::cout << "resizeSunglassImg size:" << resizeSunglassImg.size() << " channels:" << resizeSunglassImg.channels() << " dataType:" << typeToString(resizeSunglassImg.type()) << std::endl;

    std::cout << "retrieve the individual channels and group the gbr into one array." << std::endl;
    Mat sunglassChannels[4];
    Mat sunGlassGBRChannels[3];
    split(resizeSunglassImg,sunglassChannels);
    for(auto i = 0; i < resizeSunglassImg.channels() -1; i++)
    {
        sunGlassGBRChannels[i] = sunglassChannels[i];
    }
    Mat glassBGR, glassMask;
    merge(sunGlassGBRChannels,3,glassBGR);
    glassMask = sunglassChannels[3];

    imshow("Original Image",img);
    imshow("Original Sunglass", sunglassImg);
    imshow("Resize Sunglass", resizeSunglassImg);
    imshow("RGB Sunglass", glassBGR);
    imshow("Mask Sunglass", glassMask);

    waitKey(0);

    destroyAllWindows();

    return 0;
}
