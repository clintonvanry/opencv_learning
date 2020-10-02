#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

Mat imageSource;
Mat imageSource_copy;

// https://github.com/pgrudzien12/opencv-exercises/blob/master/blemish-removal/submission.py


void onMouse(int event, int x, int y, int flags, void *userdata){

}




int main() {
    std::cout << "Blemish Removal" << std::endl;
    std::string windowName ="Blemish";

    namedWindow(windowName, WINDOW_NORMAL);
    setMouseCallback(windowName, onMouse);

    imageSource = imread("blemish.png", IMREAD_COLOR);
    imageSource_copy = imageSource.clone();

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
