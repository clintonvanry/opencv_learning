#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <cmath>

using namespace cv;

// section 5 of the second paper. -> sum_modified_laplacian
// fps 5 and it appears the right answer is 95 - 97 frame number
// between 2 methods there is drift of 3-4 frames

// Implement Variance of absolute values of Laplacian - Method 1
// Input: image
// Output: Floating point number denoting the measure of sharpness of image

// Do NOT change the function name and definition

double var_abs_laplacian(Mat image){
    ///
    /// YOUR CODE HERE
    ///
    int kernelSize = 3;
    Mat laplacian;
    Laplacian(image, laplacian, CV_32F, kernelSize,1,0);
    Mat laplacian_abs = abs(laplacian);

    Mat mean;
    Mat stddev;
    cv::meanStdDev(laplacian_abs, mean, stddev);

    Mat variance;
    pow(stddev, 2, variance);
    Scalar sumResult = sum(variance);
    return sumResult.val[0];

}

// Implement Sum Modified Laplacian - Method 2
// Input: image
// Output: Floating point number denoting the measure of sharpness of image

// Do NOT change the function name and definition

double sum_modified_laplacian(Mat image){
    ///
    /// YOUR CODE HERE
    ///

    Mat kernelX = (Mat_<double>(3,3) << 0.0, 0.0, 0.0, -1.0, 2.0, -1.0, 0.0, 0.0, 0.0);
    Mat kernelY = (Mat_<double>(3,3) << 0.0, -1.0, 0.0, 0.0, 2.0, 0.0, 0.0, -1.0, 0.0);

    Mat laplacian_X;
    filter2D(image, laplacian_X, CV_32F, kernelX);

    Mat laplacian_Y;
    filter2D(image, laplacian_Y, CV_32F, kernelY);

    Scalar sumResult = sum(abs(laplacian_X) + abs(laplacian_Y));

    return sumResult.val[0];


}


int main() {

    std::string filename = "focus-test.mp4";
    VideoCapture cap(filename);

    // Read first frame from the video
    Mat frame;
    cap >> frame;

    // Display total number of frames in the video
    std::cout << "Total number of frames : " << static_cast<int>( cap.get(CAP_PROP_FRAME_COUNT)) << std::endl;
    std::cout << "Video Width : " << static_cast<int>( cap.get(CAP_PROP_FRAME_WIDTH)) << std::endl;
    std::cout << "Video Height : " << static_cast<int>( cap.get(CAP_PROP_FRAME_HEIGHT)) << std::endl;

    double maxV1 = 0;
    double maxV2 = 0;

    // Frame with maximum measure of focus
    // Obtained using methods 1 and 2
    Mat bestFrame1;
    Mat bestFrame2;

    // Frame ID of frame with maximum measure
    // of focus
    // Obtained using methods 1 and 2
    int bestFrameId1 = 0;
    int bestFrameId2 = 0;

    // Get measures of focus from both methods
    double val1 = var_abs_laplacian(frame);
    double val2 = sum_modified_laplacian(frame);


    // Specify the ROI for flower in the frame
    // UPDATE THE VALUES BELOW
    std::cout << "flower roi is 300x300" << std::endl;
    int topCorner = 180;
    int leftCorner = 600;
    int bottomCorner =  480;
    int rightCorner = 900;

    Mat flower;
    flower =  frame(Range(topCorner,bottomCorner),Range(leftCorner,rightCorner)); //frame(Range(170,485),Range(580,895));

    imshow("frame", frame);
    imshow("Flower", flower);
    waitKey(0);

    // Iterate over all the frames present in the video
    while (1){
        // Crop the flower region out of the frame
        flower = frame(Range(topCorner,bottomCorner),Range(leftCorner,rightCorner));

        // Get measures of focus from both methods
        val1 = var_abs_laplacian(flower);
        val2 = sum_modified_laplacian(flower);
        // If the current measure of focus is greater
        // than the current maximum
        if (val1 > maxV1){
            // Revise the current maximum
            maxV1 = val1;
            // Get frame ID of the new best frame
            bestFrameId1 = (int)cap.get(CAP_PROP_POS_FRAMES);
            // Revise the new best frame
            bestFrame1 = frame.clone();
            std::cout << "Frame ID of the best frame [Method 1]: " << bestFrameId1 << std::endl;
        }
        // If the current measure of focus is greater
        // than the current maximum
        if (val2 > maxV2){
            // Revise the current maximum
            maxV2 = val2;
            // Get frame ID of the new best frame
            bestFrameId2 = (int)cap.get(CAP_PROP_POS_FRAMES);
            // Revise the new best frame
            bestFrame2 = frame.clone();
            std::cout << "Frame ID of the best frame [Method 2]: " << bestFrameId2 << std::endl;
        }
        cap >> frame;
        if (frame.empty()) {
            break;
        }
    }

    std::cout << "================================================" << std::endl;

    // Print the Frame ID of the best frame
    std::cout << "Frame ID of the best frame [Method 1]: " << bestFrameId1 << std::endl;
    std::cout << "Frame ID of the best frame [Method 2]: " << bestFrameId2 << std::endl;

    cap.release();


    imshow("Best frame var_abs_laplacian", bestFrame1);
    imshow("Best frame sum_modified_laplacian", bestFrame2);
    waitKey();
    destroyAllWindows();


    return 0;

}
