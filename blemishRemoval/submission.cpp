#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>

using namespace std;
using namespace cv;

Mat imageSource;
Mat imageSource_copy;
Mat imageWithMakeUp;

bool debug = false;
Point mousePoint(0,0);

// forward declares
Mat getAreaOfInterest(Point point, int radius = 15);
std::vector<std::pair<Mat,Point>> getNeighbouringAreasOfInterest(int mouseX, int mouseY, int radius=15 );
std::pair<Mat,Point> getBestNeighbour(std::vector<std::pair<Mat,Point>> neighbours);
void drawROIforDeugging(Point point, Scalar colour, int radius = 15);
void resetImage();

void onMouse(int event, int x, int y, int flags, void *userdata){

    if(event == EVENT_LBUTTONDOWN){

        if(mousePoint != Point(x,y))
        {
            mousePoint =  Point(x,y);
            resetImage();
        }
        // get a roi from mouse click -- green for debug
        Mat roi = getAreaOfInterest(mousePoint);

        // find neighbouring patches to be used to fill the roi -- blue for debug
        std::vector<std::pair<Mat,Point>> neighbours = getNeighbouringAreasOfInterest(x,y);

        // get the best neighbour to use from the neighbours we have collected
        // the best neighbour is the one with the least gradient.
        // red for debug
        std::pair<Mat,Point> bestNeighbour = getBestNeighbour(neighbours);

        // clone best neighbour
        seamlessClone(bestNeighbour.first, imageSource,noArray(),mousePoint, imageSource, NORMAL_CLONE);

        // i am doing this in case debug is on want to remove the rectangles for the next click.
        if(debug)
        {
            seamlessClone(bestNeighbour.first, imageWithMakeUp, noArray(), mousePoint, imageWithMakeUp, NORMAL_CLONE);
        }


        if(debug)
        {
            // draw neighbours
            for(const auto& n : neighbours){
                drawROIforDeugging(n.second,Scalar(255,0,0));
            }

            // draw best neighbour
            drawROIforDeugging(bestNeighbour.second,Scalar(0,0,255));

            // draw region of interest from mouse click
            drawROIforDeugging(mousePoint, Scalar(0,255,0));
        }

    }
    if(event == EVENT_RBUTTONDOWN)
    {
        imageSource_copy.copyTo(imageSource);
    }

}




int main() {
    std::cout << "Blemish Removal" << std::endl;
    std::string windowName ="Blemish";

    namedWindow(windowName, WINDOW_NORMAL);
    setMouseCallback(windowName, onMouse);

    imageSource = imread("blemish.png", IMREAD_COLOR);
    imageSource_copy = imageSource.clone();
    imageWithMakeUp = imageSource.clone();

    int keyboardCode=0;
    int escapeKeyBoardCode = 27;

    while(true){
        imshow(windowName, imageSource);
        keyboardCode = waitKey(20) & 0xFF;;
        if(keyboardCode ==escapeKeyBoardCode){
            break;
        }
    }

    destroyAllWindows();

    return 0;
}

Mat getAreaOfInterest(Point point, int radius){
    int x = point.x - radius;
    int y = point.y - radius;
    int w = radius * 2 + 1;
    int h = radius * 2 + 1;

    // do we have a valid roi
    if (x < 0 || y < 0 || x + w > imageSource.cols || y + h > imageSource.rows)
    {
        return Mat();
    }

    Rect roi = Rect(x,y,w,h);

    return imageSource(roi);

}
std::vector<std::pair<Mat,Point>> getNeighbouringAreasOfInterest(int mouseX, int mouseY,  int radius ){

    std::vector<std::pair<Mat,Point>> neighbours;

    std::vector<Point> points;
    points.push_back(Point(mouseX-radius*2,mouseY-radius*2));
    points.push_back(Point(mouseX+radius*2,mouseY+radius*2));

    points.push_back(Point(mouseX,mouseY-radius*2));
    points.push_back(Point(mouseX-radius*2,mouseY));

    points.push_back(Point(mouseX+radius*2,mouseY-radius*2));
    points.push_back(Point(mouseX-radius*2,mouseY+radius*2));

    points.push_back(Point(mouseX+radius*2,mouseY));
    points.push_back(Point(mouseX,mouseY+radius*2));

    // get all the neighbours
    for(auto& p : points)
    {
         Mat neighbour = getAreaOfInterest(p);
         if(!neighbour.empty())
         {
             neighbours.push_back(std::make_pair(neighbour,p));
         }
    }
    return neighbours;

}
std::pair<Mat,Point> getBestNeighbour(std::vector<std::pair<Mat,Point>> neighbours)
{
    double minValue = 0.0;
    int indexBestNeighbour = 0;
    for(size_t i =0; i < neighbours.size(); i++){
        Mat sobelOutput;
        Sobel(neighbours[i].first,sobelOutput,-1,1,1);
        int val = static_cast<int>(sum(abs(sobelOutput))[0]);
        if (i == 0) {
            minValue = val;
        } else if (minValue > val) {
            minValue = val;
            indexBestNeighbour = i;
        }
    }

    return neighbours[indexBestNeighbour];

}

void drawROIforDeugging(Point point, Scalar colour, int radius)
{
    int x = point.x - radius;
    int y = point.y - radius;
    int w = radius * 2 + 1;
    int h = radius * 2 + 1;

    // do we have a valid roi
    if (x < 0 || y < 0 || x + w > imageSource.cols || y + h > imageSource.rows)
    {
        return;
    }

    Rect roi = Rect(x,y,w,h);

    if(debug){
        rectangle(imageSource, roi, colour,2);
    }

}
void resetImage()
{
    if(debug)
    {
        imageWithMakeUp.copyTo(imageSource);
    }

}