#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;

std::vector<Point2f> FindCornerPoints(const Mat& image);

int main() {

    std::cout << "Document Scanner Project" << std::endl;

    std::string originScannedDocumentWindow = "Original Scanned Document";
    Mat originalScannedDocument = imread("scanned-form.jpg", IMREAD_COLOR);
    namedWindow(originScannedDocumentWindow,WINDOW_NORMAL);
    imshow(originScannedDocumentWindow, originalScannedDocument);

    Size imageSize = originalScannedDocument.size();
    Rect areaOfInterest = Rect(Point(30, 180), Point( imageSize.width -30, imageSize.height-30));
    Mat displayAreaOfInterest = originalScannedDocument.clone();
    rectangle(displayAreaOfInterest,areaOfInterest,Scalar(255,0,0),3);
    std::string areaOfInterestWindow = "Area of Interest";
    namedWindow(areaOfInterestWindow,WINDOW_NORMAL);
    imshow(areaOfInterestWindow, displayAreaOfInterest);

    Mat mask;
    Mat bgdModel,fgdModel, foregroundOnly;
    grabCut(originalScannedDocument,mask,areaOfInterest,bgdModel,fgdModel,1, GC_INIT_WITH_RECT);
    bitwise_and(mask,1,mask);
    originalScannedDocument.copyTo(foregroundOnly,mask);

    Mat foregroundOnlyGray;
    cvtColor( foregroundOnly, foregroundOnlyGray, COLOR_BGR2GRAY );
    int thresh = 20;
    Mat canny_output;
    Canny( foregroundOnly, canny_output, thresh, thresh*2 );
    namedWindow("canny_output",WINDOW_NORMAL);
    imshow("canny_output", canny_output);

    std::vector<Point2f> doc = FindCornerPoints(canny_output);

    std::vector<Point2f> pts_dst;

    pts_dst.emplace_back(0,0);
    pts_dst.emplace_back(imageSize.width, 0);
    pts_dst.emplace_back(imageSize.width, imageSize.height);
    pts_dst.emplace_back(0, imageSize.height );
    Mat pers = getPerspectiveTransform(doc, pts_dst);

    //align document
    Mat alignedDoc = originalScannedDocument.clone();
    warpPerspective(originalScannedDocument, alignedDoc, pers, originalScannedDocument.size());

    std::string alignedScannedDocumentWindow = "Aligned Scanned Document";
    namedWindow(alignedScannedDocumentWindow,WINDOW_NORMAL);
    imshow(alignedScannedDocumentWindow, alignedDoc);

    imwrite("alignedScannedDocument.jpg",alignedDoc);

    waitKey(0);
    destroyAllWindows();
    return 0;
}
std::vector<Point2f> FindCornerPoints(const Mat& image)
{
    std::vector<Point2f> output;
    std::vector<std::vector<Point> > contours;
    std::vector<Vec4i> hierarchy;

    findContours( image, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    sort(contours.begin(), contours.end(), [](const std::vector<Point>& c1, const std::vector<Point>& c2){
        return contourArea(c1, false) > contourArea(c2, false);	});

    std::vector<Point> docContour = contours[0];

    double perimeter = arcLength(docContour,true);

    approxPolyDP(docContour,docContour, 0.02*perimeter, true);

    std::vector<Point2f> doc;

    std::vector<Point> sum = docContour;
    sort(sum.begin(), sum.end(),
         [](const Point& p1, const Point& p2) {return (p1.x  + p1.y) > (p2.x + p2.y);});

    std::vector<Point> diff;
    diff.push_back(sum[1]);
    diff.push_back(sum[2]);

    sort(diff.begin(), diff.end(), [](const Point& p1, const Point& p2) {return p1.x > p2.x ;});

    output.push_back(sum[3]);//Smallest sum for top left
    output.push_back(diff[0]);//Larger X than bottom left for top right
    output.push_back(sum[0]);//Largest sum for bottom right
    output.push_back(diff[1]);////Smaller X than top right for bottom left

    return output;
}
