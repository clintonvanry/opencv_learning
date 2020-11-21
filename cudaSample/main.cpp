#include <iostream>

#include <iostream>
#include <opencv2/opencv.hpp>

#include <opencv2/cudaimgproc.hpp>

using namespace cv;

int main() {
    std::cout << "Hello CUDA" << std::endl;

    auto img = imread("sample.jpg", IMREAD_GRAYSCALE);
    namedWindow("original", WINDOW_NORMAL);
    resizeWindow("original", 1920,1080);
    imshow("original", img);

    cv::cuda::GpuMat dst, src;
    src.upload(img);

    cv::Ptr<cv::cuda::CLAHE> ptr_clahe = cv::cuda::createCLAHE(5.0, cv::Size(8, 8));
    ptr_clahe->apply(src, dst);

    cv::Mat result;
    dst.download(result);

    namedWindow("result", WINDOW_NORMAL);
    resizeWindow("result", 1920,1080);
    cv::imshow("result", result);

    waitKey(0);

    destroyAllWindows();
    return 0;
}
