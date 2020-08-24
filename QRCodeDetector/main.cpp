#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void display(Mat &im, Mat &bbox) {

    std::cout << bbox << std::endl;
    std::cout << bbox.at<float>(0, 0) << endl;
    std::cout << bbox.at<float>(0, 1) << endl;

    std::cout << bbox.at<float>(0, 2) << endl;
    std::cout << bbox.at<float>(0, 3) << endl;

    std::cout << bbox.at<float>(0, 4) << endl;
    std::cout << bbox.at<float>(0, 5) << endl;

    std::cout << bbox.at<float>(0, 6) << endl;
    std::cout << bbox.at<float>(0, 7) << endl;

    Point p1 = Point(bbox.at<float>(0, 0), bbox.at<float>(0, 1));
    Point p2 = Point(bbox.at<float>(0, 4), bbox.at<float>(0, 5));

    rectangle(im, p1, p2, Scalar(255, 0, 255), 5, LINE_8);

    imshow("Result", im);

}


int main() {

    Mat img = imread("IDCard-Satya.png", IMREAD_COLOR);
    cout << img.size().height << " " << img.size().width;
    QRCodeDetector qrDecoder;

    Mat bbox, rectifiedImage;
    std::string opencvData = qrDecoder.detectAndDecode(img, bbox, rectifiedImage);

    if (opencvData.length() > 0) {
        cout << "QR Code Detected" << endl;
    } else {
        cout << "QR Code NOT Detected" << endl;
    }

    display(img, bbox);

    std::cout << opencvData << endl;

    waitKey(0);

    destroyAllWindows();

}
