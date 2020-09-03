#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    std::cout << "working with blobs" << std::endl;

    auto imgSource = imread("blob_detection.jpg", IMREAD_GRAYSCALE);
    // Set up detector with default parameters
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create();

    std::vector<KeyPoint> keypoints;
    detector->detect(imgSource,keypoints);

    int x,y;
    int radius;
    double diameter;
    cvtColor(imgSource, imgSource, COLOR_GRAY2BGR);
    for (int i=0; i < keypoints.size(); i++){
        KeyPoint k = keypoints[i];
        Point keyPt;
        keyPt = k.pt;
        x=(int)keyPt.x;
        y=(int)keyPt.y;
        // Mark center in BLACK
        circle(imgSource,Point(x,y),5,Scalar(255,0,0),-1);
        // Get radius of coin
        diameter = k.size;
        radius = (int)diameter/2.0;
        // Mark blob in GREEN
        circle(imgSource, Point(x,y),radius,Scalar(0,255,0),2);
    }

    imshow("blobs",imgSource);
    waitKey(0);

    destroyAllWindows();

    return 0;
}
