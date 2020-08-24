#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

void NaiveAnnotateOfText(const Mat& originalImg);
void AnnotateOfText(const Mat& originalImg);

int main() {
    std::cout << "Start with boy image" << std::endl;
    auto img = imread("boy.jpg", IMREAD_COLOR);

    std::cout << "Draw a green line on boy forehead" << std::endl;
    auto imgLine = img.clone();
    // The line starts from (200,80) and ends at (280,80)
    // The color of the line is GREEN (Recall that OpenCV uses BGR format)
    // Thickness of line is 3px
    // Linetype is LINE_AA
    line(imgLine,Point(200,80),Point(280, 80),Scalar(0,255,0),3,LINE_AA);

    std::cout << "Draw a red circle around the boy" << std::endl;
    auto imgCircle = img.clone();
    // if you want to fill the circle set the thickness to -1
    circle(imgCircle,Point(250,125),100,Scalar(0,0,255),5,LINE_AA);

    std::cout << "Draw a ellipses around the boy" << std::endl;
    auto imgEllipse = img.clone();
    ellipse(imgEllipse, Point(250, 125), Point(100, 50), 135, 0, 360,
            Scalar(255, 0, 0), 3, LINE_AA);

    ellipse(imgEllipse, Point(250, 125), Point(100, 50), 90, 0, 360,
            Scalar(0, 0, 255), 3, LINE_AA);

    ellipse(imgEllipse, Point(250, 125), Point(100, 50), 45, 0, 360,
            Scalar(0, 255, 0), 3, LINE_AA);

    std::cout << "Draw a rectangle around the boy" << std::endl;
    auto imgRec = img.clone();
    rectangle(imgRec, Point(170, 50), Point(300, 200),
              Scalar(255, 0, 255), 5, LINE_8);

    std::cout << "Adding text to image" << std::endl;


    imshow("Original Boy", img);
    imshow("Boy with green line", imgLine);
    imshow("Boy with red circle", imgCircle);
    imshow("Boy with ellipses", imgEllipse);
    imshow("Boy with rectangle", imgRec);
    NaiveAnnotateOfText(img);
    AnnotateOfText(img);
    waitKey(0);

    destroyAllWindows();
    return 0;
}
void NaiveAnnotateOfText(const Mat& originalImg){
    std::cout << "Naive method of adding text to image" << std::endl;
    std::cout << "issues with naive approach are:" << std::endl;
    std::cout << "if the background is blue" << std::endl;
    std::cout << "the text is clipped. Letter g" << std::endl;
    std::cout << "the text is not centered" << std::endl;
    std::cout << "the text is to big" << std::endl;

    auto imgText = originalImg.clone();

    std::string textStr = "I am studying";
    double fontScale = 1.5;
    int fontFace = FONT_HERSHEY_COMPLEX;
    Scalar fontColor = Scalar(250, 10, 10);
    int fontThickness = 2;

    putText(imgText, textStr, Point(20, 350), fontFace, fontScale, fontColor, fontThickness, LINE_AA);

    imshow("Naive adding text to image", imgText);

}
void AnnotateOfText(const Mat& originalImg)
{
    std::cout << "Adding text to image" << std::endl;
    auto imgText = originalImg.clone();

    std::cout<<"Instead of using a fontScale, let us use a text height of 20 pixels to determine the fontScale and and write the same text again." << std::endl;
    int pixelHeight = 20;
    int fontFace = FONT_HERSHEY_COMPLEX;
    int fontThickness = 2;
    // Calculate the fontScale
    auto fontScale = getFontScaleFromHeight(fontFace, pixelHeight, fontThickness);
    std::cout << "fontScale = " << fontScale << std::endl;

    std::cout << "Get the width and height of the text beforehand" << std::endl;
    int imageHeight = imgText.rows;
    int imageWidth = imgText.cols;
    int baseLine = 0;
    std::string textStr = "I am studying";
    auto textSize = getTextSize(textStr,fontFace,fontScale,fontThickness, &baseLine);
    int textWidth = textSize.width;
    int textHeight = textSize.height;
    std::cout << "TextWidth = " << textWidth << ", TextHeight = " << textHeight << ", baseLine = " << baseLine;

    // Get the coordinates of text box bottom left corner
    // The xccordinate will be such that the text is centered
    int xcoordinate = (imageWidth - textWidth)/2;
    // The y coordinate will be such that the entire box is just 10 pixels above the bottom of image
    int ycoordinate = (imageHeight - baseLine - 10);

    std::cout << "TextBox Bottom Left = (" << xcoordinate << "," << ycoordinate << ")";

    // Draw the Canvas using a filled rectangle
    Scalar canvasColor = Scalar(255, 255, 255);
    Point canvasBottomLeft (xcoordinate,ycoordinate+baseLine);
    Point canvasTopRight (xcoordinate+textWidth, ycoordinate-textHeight);

    rectangle(imgText, canvasBottomLeft, canvasTopRight, canvasColor, -1);

    std::cout << "Canvas Bottom Left = " << canvasBottomLeft << ", Top Right = " << canvasTopRight;

    // Now draw the baseline ( just for reference )
    int lineThickness = 2;
    Point lineLeft (xcoordinate, ycoordinate);
    Point lineRight (xcoordinate+textWidth, ycoordinate);
    Scalar lineColor = Scalar(0,255,0);

    line(imgText, lineLeft, lineRight, lineColor, lineThickness, LINE_AA);

    // Finally Draw the text
    Scalar fontColor = Scalar(250, 10, 10);
    putText(imgText, textStr, Point(xcoordinate,ycoordinate), fontFace, fontScale,
            fontColor, fontThickness, LINE_AA);

    imshow("Annotate boy",imgText);
}