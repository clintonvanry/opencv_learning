#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

Mat convertBGRtoGray(Mat image);
Mat convertBGRtoHSV(Mat image);

int main()
{

    auto img = imread("sample.jpg");
    std::cout << typeToString(img.type()) << std::endl;
    namedWindow("sample", WINDOW_NORMAL);
    imshow("sample", img);
    waitKey(0);

    Mat gray_cv;
    cvtColor(img, gray_cv, COLOR_BGR2GRAY);
    std::cout << typeToString(gray_cv.type()) << std::endl;
    Mat gray = convertBGRtoGray(img);


    Mat diffGray;
    absdiff(gray,gray_cv,diffGray);

    imshow("Gray::Result from custom function", gray);
    imshow("Gray::Result from OpenCV function", gray_cv);
    imshow("Gray::Difference", diffGray);
    waitKey(0);

    Mat hsv = convertBGRtoHSV(img);
    Mat hsv_cv;
    cvtColor(img,hsv_cv,COLOR_BGR2HSV);

    Mat diffHSV;
    absdiff(hsv,hsv_cv,diffHSV);

    imshow("HSV::Result from custom function", hsv);
    imshow("HSV::Result from OpenCV function", hsv_cv);
    imshow("HSV::Difference", diffHSV);
    waitKey(0);


    destroyAllWindows();

    return 0;
}

Mat convertBGRtoGray(Mat image)
{
    // Formulae: gray = (0.299 * red channel) + (0.587 * green channel) +  (0.114 * blue channel)
    Mat workingImage;
    image.convertTo(workingImage,CV_32FC3);

    float blueFactor = 0.114, greenFactor = 0.587, redFactor = 0.299;
    Mat bgrChannels[3];

    split(workingImage, bgrChannels);

    multiply(bgrChannels[0],blueFactor,bgrChannels[0]);
    multiply(bgrChannels[1],greenFactor,bgrChannels[1]);
    multiply(bgrChannels[2],redFactor,bgrChannels[2]);

    add(bgrChannels[0],bgrChannels[1],bgrChannels[0]);
    add(bgrChannels[0],bgrChannels[2],bgrChannels[0]);

    Mat gray;
    bgrChannels[0].convertTo(gray, CV_8UC1);

    std::cout << typeToString(gray.type()) << std::endl;
    imshow("gray", gray);
    waitKey(0);

    return gray;

}

Mat convertBGRtoHSV(Mat image)
{
    Mat hsv_cv;
    cvtColor(image,hsv_cv,COLOR_BGR2HSV);
    return hsv_cv;
}