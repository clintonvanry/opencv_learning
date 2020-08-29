#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;

// Point to store the top left corner
Point m_topLeftCorner;
// Source and working image
Mat m_imgSource, m_imgWorking;
std::string m_windowName = "Assignment 2 Face Annotation Tool";
// call back method.
void drawRectangle(int action, int x, int y, int flags, void *userdata);
// small utility methods
void resetImage();
void saveCropImage(int x, int y);

int main()
{
    // read the original image and create a working image to be used for cropping
    m_imgSource = imread("sample.jpg", IMREAD_COLOR);

    // This is least amounts of lines of code to achieve the objective of the assignment however I believe they want to test
    // our understanding of the callback
    // attempt 1
    //m_roiCrop = selectROI(m_imgSource,true,false);
    //auto crop = m_imgSource(m_roiCrop);
    //imwrite("face.png",crop);
    //waitKey(0);

    // attempt 2
    // create a working image to draw roi
    resetImage();

    // setup the callback
    namedWindow(m_windowName, WINDOW_AUTOSIZE);
    setMouseCallback(m_windowName,drawRectangle);

    int keyBoardCode = 0;
    const int ESC_KEYBOARD_CODE = 27;
    const int C_KEYBOARD_CODE = 99;

    while(keyBoardCode != ESC_KEYBOARD_CODE)
    {
        imshow(m_windowName, m_imgWorking);
        putText(m_imgWorking, "Choose top left corner, and drag?.", Point(10,30), FONT_HERSHEY_SIMPLEX, 0.7,Scalar(255,255,255), 2 );
        keyBoardCode= waitKey(20)& 0xFF;

        if(keyBoardCode == C_KEYBOARD_CODE)
        {
            // reset the image
            resetImage();
        }
    }
    // clean up
    destroyAllWindows();
    return 0;
}

void drawRectangle(int action, int x, int y, int flags, void *userdata)
{
    std::cout <<  "X: " << x << " Y:" << y << std::endl;
    // Action to be taken when left mouse button is pressed
    if( action == EVENT_LBUTTONDOWN )
    {
        auto color =  Scalar(255,255,0);
        // clear the image of dots if the user did not drag causing the event EVENT_LBUTTONUP not to fire
        resetImage();
        m_topLeftCorner = Point(x,y);
        rectangle(m_imgWorking, m_topLeftCorner, m_topLeftCorner,color, 2, LINE_8 );
    }

    if(action == EVENT_LBUTTONUP)
    {
        auto color =  Scalar(255,255,0);
        auto bottomRightCorner = Point(x,y);
        // draw rectangle
        rectangle(m_imgWorking, m_topLeftCorner, bottomRightCorner,color, 2, LINE_8 );
        // crop the image to be saved to disk
        saveCropImage(x, y);
    }
}
void saveCropImage(int x, int y)
{
    // we need to do this in case user drags up
    auto min_x = std::min(m_topLeftCorner.x, x);
    auto max_x = std::max(m_topLeftCorner.x, x);
    auto min_y = std::min(m_topLeftCorner.y, y);
    auto max_y = std::max(m_topLeftCorner.y, y);

    auto crop_height = max_y - min_y;
    auto crop_width = max_x - min_x;
    auto roi = Rect(min_x, min_y, crop_width,crop_height);
    auto cropImg = m_imgSource(roi);
    imwrite("face.png",cropImg);
}
void resetImage()
{
    m_imgSource.copyTo(m_imgWorking);
}