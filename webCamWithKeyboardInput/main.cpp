#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    std::cout << "Simple webcam application" << std::endl;

    VideoCapture cap(1);

    std::cout << "Write out the video properties" << std::endl;
    auto videoWidth = cap.get(CAP_PROP_FRAME_WIDTH);
    auto videoHeight =cap.get(CAP_PROP_FRAME_HEIGHT);
    std::cout << "Width: " << videoWidth << " Height:" << videoHeight << std::endl;
    std::cout << "FrameCount:" << cap.get(CAP_PROP_FRAME_COUNT) << " FPS: " << cap.get(CAP_PROP_FPS ) << std::endl;

    if(!cap.isOpened())
    {
        std::cout << "Failed to open webcam." << std::endl;
    }

    int key = 0;
    while(true)
    {
        Mat img;
        cap >> img;
        if(key == 27){
            std::cout << "ESC keypressed and will exit" << std::endl;
            break;
        }
        if(key == 101 || key == 69){
            putText(img,"E is pressed, press Z or ESC", Point(100,180), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,255,0), 3);
        }

        if(key == 99 || key == 122){
            putText(img, "Z is pressed", Point(100,180), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,255,0), 3);
        }

        imshow("Image", img);
        key = waitKey(10000) & 0xFF;

    }
    cap.release();
    destroyAllWindows();


    return 0;
}
