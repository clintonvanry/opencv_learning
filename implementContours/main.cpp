#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    std::cout << "working with contours" << std::endl;

    auto imgSource = imread("Contour.png", IMREAD_COLOR);
    auto imgCopy = imgSource.clone();
    Mat imgGray;
    cvtColor(imgSource,imgGray, COLOR_BGR2GRAY);
    imshow("original", imgSource);
    imshow("gray image", imgGray);

    // Find all contours in the image
    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hierarchy;
    findContours(imgGray,contours,hierarchy,RETR_LIST, CHAIN_APPROX_SIMPLE);
    std::cout << "Number of vectors found:" << contours.size() << std::endl;

    // draw contours
    drawContours(imgSource, contours,-1, Scalar(0,255,0),6);
    imshow("RETR_LIST Contours of the image", imgSource);

    // find only the external contours
    findContours(imgGray,contours,hierarchy,RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    std::cout << "Number of vectors found:" << contours.size() << std::endl;
    imgSource = imgCopy.clone();
    drawContours(imgSource, contours,-1, Scalar(0,255,255),3);
    imshow("RETR_EXTERNAL Contours of the image", imgSource);

    // Draw only the 3rd contour
    // Note that right now we do not know
    // the numbering of contour in terms of the shapes
    // present in the figure
    imgSource = imgCopy.clone();
    drawContours(imgSource, contours,2, Scalar(255,255,0),3);
    imshow("3rd Contours of the image", imgSource);

    // Find all contours in the image
    findContours(imgGray, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    imgSource = imgCopy.clone();
    // Draw all the contours
    drawContours(imgSource, contours, -1, Scalar(255,0,255), 3);
    // centroid
    Moments moment;
    int x,y;
    Rect rect;
    for (size_t i=0; i < contours.size(); i++){
        // We will use the contour moments
        // to find the centroid
        moment = moments(contours[i]);
        x = int(moment.m10/double(moment.m00));
        y = int(moment.m01/double(moment.m00));

        // Mark the center
        circle(imgSource, Point(x,y), 10, Scalar(255,0,0), -1);

        // Mark the contour number
        putText(imgSource, std::to_string(i+1), Point(x+40,y-10), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,255),2);

        // Vertical rectangle
        rect = boundingRect(contours[i]);
        rectangle(imgSource, rect, Scalar(0,255,0), 2);
    }
    imshow("Centroid", imgSource);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
