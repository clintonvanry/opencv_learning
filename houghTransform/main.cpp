#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
void HoughLinesExample();
void HoughCirclesExample();

int main() {

    std::cout << "Hough Transform" << std::endl;

    HoughLinesExample();
    HoughCirclesExample();

    destroyAllWindows();

    return 0;
}
void HoughLinesExample()
{
    auto lanes = imread("lanes.jpg", IMREAD_COLOR);
    auto original = lanes.clone();
    // Convert the image to gray-scale
    Mat gray;
    cvtColor(lanes,gray,COLOR_BGR2GRAY);
    std::cout << typeToString(gray.type()) << std::endl;

    // Find the edges in the image using canny detector
    Mat edges;
    Canny(gray,edges,50,200);

    // Detect points that form a line
    std::vector<Vec4i> lines;
    HoughLinesP(edges,lines,1,CV_PI/180,100,10,250);

    // Draw lines on the image
    for (size_t i=0; i < lines.size(); i++){
        Vec4i line = lines[i];
        cv::line(lanes,Point(line[0],line[1]),Point(line[2],line[3]),Scalar(255,0,0),3,LINE_AA);
    }
    imshow("Hough Lines", lanes);
    imshow("original", original);
    waitKey(0);

}
void HoughCirclesExample()
{
    auto face = imread("circles.jpg",IMREAD_COLOR);
    auto original = face.clone();

    Mat gray;
    // Convert to gray-scale
    cvtColor(face, gray, COLOR_BGR2GRAY);

    // Blur the image to reduce noise
    Mat img_blur;
    medianBlur(gray,img_blur,5);
    // Apply hough transform on the image
    std::vector<Vec3f> circles;
    HoughCircles(img_blur, circles, HOUGH_GRADIENT, 1, 50, 450, 10, 30, 40);

    for( size_t i = 0; i < circles.size(); i++ )
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // Draw the outer circle
        circle( face, center, radius, Scalar(0, 255, 0), 2);
        // Draw the center of the circle
        circle( face, center, 2, Scalar(0, 0, 255), 3);
    }

    imshow("Hough Circles", face);
    imshow("original", original);
    waitKey(0);
}