#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;

/*
 *
Grading Rubric
1. Step 1: Read Image - No Marks

2. Step 2: Detect Features - 6 Marks

3. Step 3: Match Features - 6 Marks

4. Step 4: Calculate Homography - 12 Marks

5. Step 5: Warping Image - 6 Marks

6. Step 6: Merge Channels - No Marks
*/

int main() {
    std::cout << "Image alignment" << std::endl;

    //**************** STEP 1 ******************************************************************************************
    Mat img = imread("emir.jpg",IMREAD_GRAYSCALE);
    // Find the width and height of the color image
    Size sz = img.size();
    int height = sz.height / 3;
    int width = sz.width;

    std::cout << sz << std::endl;

    // Extract the three channels from the gray scale image
    std::vector<Mat>channels;
    channels.push_back(img( Rect(0, 0,         width, height)));
    channels.push_back(img( Rect(0, height,    width, height)));
    channels.push_back(img( Rect(0, 2*height,  width, height)));

    Mat blue = channels[0];
    Mat green = channels[1];
    Mat red = channels[2];

    imshow("original",img);
    imshow("blue", blue);
    imshow("green", green);
    imshow("red", red);

    waitKey(0);
    //**************** STEP 1 ******************************************************************************************

    //**************** STEP 2 ******************************************************************************************
    /*
    Step 2: Detect Features - 6 Marks
    We will align Blue and Red frame to the Green frame. Take a minute and think about a valid reason.

    If you align blue and red channels, it might not give very good results since they are visually very different.
    You may have to do a lot parameter tuning ( MAX_FEATURES, GOOD_MATCH_PERCENT, etc) to get them aligned.
    On the other hand, Blue and Green channels are reasonably similar. Thus, taking green as the base channel will produce best results.
    We detect ORB features in the 3 frames.
    Although we need only 4 features to compute the homography, typically hundreds of features are detected in the two images.
    We control the number of features using the parameter MAX_FEATURES in the C++ code.

    Set MAX_FEATURES and GOOD_MATCH_PERCENT ( You may need to play around with these parameters to get the desired result)
    */

    ///
    /// YOUR CODE HERE
    ///

    std::vector<KeyPoint> keypointsBlue;
    std::vector<KeyPoint> keypointsGreen;
    std::vector<KeyPoint> keypointsRed;


    // Detect ORB features and compute descriptors.
    // You need to find the keypoints and descriptors for each channel using ORB and store them in respective variables
    // e.g. keyPointsBlue and descriptorsBlue are the keypoints and descriptors for the blue channel

    ///
    /// YOUR CODE HERE
    ///


    //**************** STEP 2 ******************************************************************************************

    //**************** STEP 3 ******************************************************************************************
    /*
    Step 3: Match Features
    We find the matching features in the two images, sort them by goodness of match and keep only a small percentage of original matches.
    We finally display the good matches on the images and write the file to disk for visual inspection.
    We use the hamming distance as a measure of similarity between two feature descriptors.
    The matched features are shown in the figure below by drawing a line connecting them.
    Notice, we have many incorrect matches and thefore we will need to use a robust method to calculate homography in the next step.
    */
    Mat img2;
    drawKeypoints(blue, keypointsBlue, img2, Scalar(255,0,0), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    imshow("Blue features", img2);

    drawKeypoints(green, keypointsGreen, img2, Scalar(0,255,0), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    imshow("Green features", img2);

    drawKeypoints(red, keypointsRed, img2, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    imshow("Red features", img2);

    // Step 3: Match Features - 6 Marks
    // You need to find the matching features in the Green channel and blue/red channel,
    // sort them by goodness of match and keep only a small percentage of original matches.
    // We finally display the good matches on the images and write the file to disk for visual inspection.
    // Use the hamming distance as a measure of similarity between two feature descriptors.

    // Let's first match features between blue and Green channels.
    // Match features.
    ///
    /// YOUR CODE HERE
    ///
    int GOOD_MATCH_PERCENT = 5;
    std::vector<DMatch> matchesBlueGreen;
    // Match features between blue and Green channels
    ///
    /// YOUR CODE HERE
    ///

    // Sort matches by score
    std::sort(matchesBlueGreen.begin(), matchesBlueGreen.end());

    // Remove not so good matches
    int numGoodMatches = matchesBlueGreen.size() * GOOD_MATCH_PERCENT;
    matchesBlueGreen.erase(matchesBlueGreen.begin()+numGoodMatches, matchesBlueGreen.end());

    // Draw top matches
    Mat imMatchesBlueGreen;
    drawMatches(blue, keypointsBlue, green, keypointsGreen, matchesBlueGreen, imMatchesBlueGreen);

    imshow("BlueGreenMatches",imMatchesBlueGreen);
    waitKey(0);

    // We will repeat the same process for Red and Green channels this time.
    // Find the matches between Red and Green channels and save them in matchesRedGreen variable
    std::vector<DMatch> matchesRedGreen;

    // Match features between Red and Green channels
    ///
    /// YOUR CODE HERE
    ///

    // Sort matches by score
    std::sort(matchesRedGreen.begin(), matchesRedGreen.end());

    // Remove not so good matches
    numGoodMatches = matchesRedGreen.size() * GOOD_MATCH_PERCENT;
    matchesRedGreen.erase(matchesRedGreen.begin()+numGoodMatches, matchesRedGreen.end());

    // Draw top matches
    Mat imMatchesRedGreen;
    drawMatches(red, keypointsRed, green, keypointsGreen, matchesRedGreen, imMatchesRedGreen);

    imshow("RedGreenMatches",imMatchesRedGreen);
    waitKey(0);
    //**************** STEP 3 ******************************************************************************************

    //**************** STEP 4 ******************************************************************************************
    /*
    Step 4: Calculate Homography - 12 Marks
    Next, you need to compute the homography between the green and red/blue channels using the matches and keypoints computed in the previous step.

    Let's first calculate the homography between Blue and Green channels.
    */

    // Find the homography matrix between the Blue and Green channel and name it hBlueGreen

    // Extract location of good matches
    ///
    /// YOUR CODE HERE
    ///

    // Find homography
    ///
    /// YOUR CODE HERE
    ///

    //Similarly, we can calculate the homography between Green and Red channels.
    //Find the homography matrix between the Red and Green channel and name it hRedGreen

    // Extract location of good matches
    ///
    /// YOUR CODE HERE
    ///

    // Find homography
    ///
    /// YOUR CODE HERE
    ///
    //**************** STEP 4 ******************************************************************************************

    //**************** STEP 5 ******************************************************************************************
    /*
    Step 5: Warping Image - 6 Marks
    Once an accurate homography has been calculated, the transformation can be applied to all pixels in one image to map it to the other image.
    This is done using the warpPerspective function in OpenCV.

    We map the Blue and Red channels to Green channel pixels.
    */

    //Find the warped images blueWarped and redWarped using the warpPerspective function

    // Use homography to find blueWarped and RedWarped images
    ///
    /// YOUR CODE HERE
    ///
    Mat blueWarped;
    Mat redWarped;




    imshow("Blue channel aligned w.r.t green channel", blueWarped);
    imshow("Red channel aligned w.r.t green channel", redWarped);
    waitKey(0);

    //**************** STEP 5 ******************************************************************************************

    //**************** STEP 6 ******************************************************************************************
    /*
    Step 6: Merge Channels
    Finally, let's merge the channels to form the final colored image.
    */
    Mat colorImage;
    std::vector<Mat> colorImageChannels {blueWarped, green, redWarped};
    merge(colorImageChannels,colorImage);

    Mat originalImage;
    merge(channels,originalImage);

    imshow("Original Mis-aligned Image",originalImage);
    imshow("Aligned Image",colorImage);
    waitKey(0);
    //**************** STEP 6 ******************************************************************************************

    destroyAllWindows();
    return 0;
}
