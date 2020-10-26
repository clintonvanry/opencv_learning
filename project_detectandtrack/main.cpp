#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

/*
 * Project tasks:
 * 1. Implement a fusion of detect and track so that it performs better in terms of speed and accuracy than TLD
 * 2. The output video should show the bounding box in GREEN when the algorithm is performing tracking and BLUE when it is performing detection
 * 3. The display should indicate if tracking fails.
 * Advice from project video: use yolo for detection
 */

Size videoFrameSize(0,0);
int videoFps = 25;

void PrintVideoProperties(const VideoCapture& videoCapture);

int main() {
    std::cout << "Detect and track the soccer ball in the video." << std::endl;

    std::string videoFilename = "./soccer-ball.mp4";

    // check to see if the video can be used and is in the directory to be read.
    VideoCapture videoCapture(videoFilename);
    if(!videoCapture.isOpened())
    {
        std::cout << "Failed to open video file" << std::endl;
        videoCapture.release();
        return -1;
    }
    PrintVideoProperties(videoCapture);

    // cleanup
    videoCapture.release();
    destroyAllWindows();
    return 0;
}
void PrintVideoProperties(const VideoCapture& videoCapture)
{
    int width=0, height=0, fps=0;

    width = videoCapture.get(CAP_PROP_FRAME_WIDTH);
    height = videoCapture.get(CAP_PROP_FRAME_HEIGHT);
    fps = videoCapture.get(CAP_PROP_FPS);
    std::cout << "Video width: " << width << std::endl;
    std::cout << "Video height: " << height << std::endl;
    std::cout << "Video duration: " << videoCapture.get(CAP_PROP_FRAME_COUNT) << std::endl;
    std::cout << "Video fps: " << fps  << std::endl;

    // needed for the recording
    videoFrameSize = Size(width,height);
    videoFps = fps;
}