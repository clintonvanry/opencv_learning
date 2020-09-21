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

    // use cv2.laplacian function


    return 0;
}

// Implement Sum Modified Laplacian - Method 2
// Input: image
// Output: Floating point number denoting the measure of sharpness of image

// Do NOT change the function name and definition

double sum_modified_laplacian(Mat image){
    ///
    /// YOUR CODE HERE
    ///

    // use cv2.filter2D function

    return 0;
}


int main() {

    std::string filename = "focus-test.mp4";
    VideoCapture cap(filename);

    // Read first frame from the video
    Mat frame;
    cap >> frame;

    // Display total number of frames in the video
    std::cout << "Total number of frames : " << (int)cap.get(CAP_PROP_FRAME_COUNT) << std::endl;

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
    int topCorner = 0;
    int leftCorner = 0;
    int bottomCorner = frame.size().height;
    int rightCorner = frame.size().width;

    Mat flower;
    flower = frame(Range(topCorner,bottomCorner),Range(leftCorner,rightCorner));

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


    return 0;
}
