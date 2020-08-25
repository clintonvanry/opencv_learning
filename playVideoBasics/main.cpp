#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    std::cout << "Play chaplin video" << std::endl;

    VideoCapture videoCapture("chaplin.mp4", cv::CAP_FFMPEG);

    std::cout << "Write out the video properties" << std::endl;
    auto videoWidth = videoCapture.get(CAP_PROP_FRAME_WIDTH);
    auto videoHeight =videoCapture.get(CAP_PROP_FRAME_HEIGHT);
    std::cout << "Width: " << videoWidth << " Height:" << videoHeight << std::endl;
    std::cout << "FrameCount:" << videoCapture.get(CAP_PROP_FRAME_COUNT) << " FPS: " << videoCapture.get(CAP_PROP_FPS ) << std::endl;
    std::cout << "FOURCC:" <<  videoCapture.get(CAP_PROP_FOURCC )  << std::endl;


    if(!videoCapture.isOpened())
    {
        std::cout << "Failed to open the video file." << std::endl;
    }

    std::cout << "Create a new chaplin video" << std::endl;
    VideoWriter videoWriter("chaplinNew.mp4", VideoWriter::fourcc('M','J','P','G'),10,Size(videoWidth,videoHeight));

    while (videoCapture.isOpened())
    {
        Mat videoFrame;
        videoCapture >> videoFrame;
        if(videoFrame.empty()){
            break;
        }
        videoWriter.write(videoFrame);
        imshow("VideoFrame", videoFrame);

        waitKey(25); // framerate
    }

    videoCapture.release();
    videoWriter.release();
    destroyAllWindows();


    return 0;
}
