#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    std::cout << "Homography" << std::endl;

    Mat refImage = imread("form.jpg");
    imshow("Reference form", refImage);
    waitKey(0);

    Mat scannedImage = imread("scanned-form.jpg");
    imshow("Scanned form", scannedImage);
    waitKey(0);

    int MAX_FEATURES = 500;
    float GOOD_MATCH_PERCENT = 0.15f;

    // Convert images to grayscale
    Mat refGray, scannedGray;
    cvtColor(refImage, refGray, COLOR_BGR2GRAY);
    cvtColor(scannedImage, scannedGray, COLOR_BGR2GRAY);

    // Variables to store keypoints and descriptors
    std::vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;

    // Detect ORB features and compute descriptors.
    Ptr<Feature2D> orb = ORB::create(MAX_FEATURES);
    orb->detectAndCompute(refGray, Mat(), keypoints1, descriptors1);
    orb->detectAndCompute(scannedGray, Mat(), keypoints2, descriptors2);

    // Match features.
    std::vector<DMatch> matches;
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
    matcher->match(descriptors1, descriptors2, matches, Mat());

    // Sort matches by score
    std::sort(matches.begin(), matches.end());

    // Remove not so good matches
    const int numGoodMatches = matches.size() * GOOD_MATCH_PERCENT;
    matches.erase(matches.begin()+numGoodMatches, matches.end());

    // Draw top matches
    Mat imMatches;
    drawMatches(scannedImage, keypoints1, refImage, keypoints2, matches, imMatches);
    imwrite("matches.jpg", imMatches);

    imshow("Matches",imMatches);
    waitKey(0);

    // Extract location of good matches
    std::vector<Point2f> points1, points2;

    for( size_t i = 0; i < matches.size(); i++ )
    {
        points1.push_back( keypoints1[ matches[i].queryIdx ].pt );
        points2.push_back( keypoints2[ matches[i].trainIdx ].pt );
    }

    // Find homography
    Mat h = findHomography( points1, points2, RANSAC );

    // Use homography to warp image
    Mat im1Reg;
    warpPerspective(scannedImage, im1Reg, h, refImage.size());

    imshow("Image",im1Reg);
    waitKey(0);
    // Print estimated homography
    std::cout << "Estimated homography : \n" << h << std::endl;

    destroyAllWindows();

    return 0;
}
