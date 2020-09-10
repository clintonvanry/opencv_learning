#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

Mat convertBGRtoGray(Mat image);
Mat convertBGRtoHSV(Mat image);

int main()
{

    auto img = imread("sample.jpg");
    namedWindow("sample", WINDOW_NORMAL);
    imshow("sample", img);
    waitKey(0);

    Mat gray = convertBGRtoGray(img);
    Mat gray_cv;
    cvtColor(img, gray_cv, COLOR_BGR2GRAY);

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
    Mat gray_cv;
    cvtColor(image, gray_cv, COLOR_BGR2GRAY);
    return gray_cv;
}

Mat convertBGRtoHSV(Mat image)
{
    Mat hsv_cv;
    cvtColor(image,hsv_cv,COLOR_BGR2HSV);
    return hsv_cv;
}