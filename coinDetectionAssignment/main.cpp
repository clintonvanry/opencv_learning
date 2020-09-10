#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include<iterator>

using namespace std;
using namespace cv;

void ProcessCoinsA();
void ProcessCoinsB();
Mat displayConnectedComponents(Mat &im);

int main() {
    std::cout << "coin detection assignment" << std::endl;
    //ProcessCoinsA();
    ProcessCoinsB();
    destroyAllWindows();
    return 0;
}
void ProcessCoinsA()
{
    // Image path
    string imagePath = "CoinsA.png";
    // Read image
    // Store it in the variable image
    ///
    /// YOUR CODE HERE
    ///
    Mat image = imread(imagePath, IMREAD_COLOR);
    Mat imageCopy = image.clone();

    //imshow("image", image);
    //waitKey(0);

    // Step 2.1: Convert Image to Grayscale
    // Convert image to grayscale
    // Store it in the variable imageGray
    ///
    /// YOUR CODE HERE
    ///
    Mat imageGray;
    cv::cvtColor(image,imageGray, COLOR_BGR2GRAY);

    // display image
    //imshow("Gray image", imageGray);
    //waitKey(0);



    //Step 2.2: Split Image into R,G,B Channels
    // Split cell into channels
    // Store them in variables imageB, imageG, imageR
    ///
    /// YOUR CODE HERE
    ///
    Mat imageB, imageG, imageR;
    Mat imageRGBA[3];
    split(image, imageRGBA);

    imageB = imageRGBA[0];
    imageG = imageRGBA[1];
    imageR = imageRGBA[2];


    // display imageB, imageG, imageR
    //imshow("Blue", imageB );
    //imshow("Green", imageG);
    //imshow("Red", imageR);

    //waitKey(0);


    //Step 3.1: Perform Thresholding
    //You will have to carry out this step with different threshold values to see which one suits you the most.
    // Do not remove those intermediate images and make sure to document your findings.

    ///
    /// YOUR CODE HERE
    ///


    // get a portion of the image so that we can see what numbers the coin represent
    Rect roi(imageGray.cols / 2,imageGray.rows / 2 ,100 , 60);
    Mat croppedImage = imageGray(roi);
    double cropMin=0,cropMax=0;
    minMaxIdx(croppedImage,&cropMin, &cropMax);
    auto cropMean =  mean(croppedImage);
    cout << "min: " << cropMin << " max: " << cropMax << " mean:" << cropMean << endl;
    //cout << croppedImage << endl;

    Mat imageThreshBinInv;
    // THRESH_BINARY_INV
    //threshold(imageGray, imageThreshBinInv, 40, 255, THRESH_BINARY_INV);
    //  imageG gave me a better result
    threshold(imageG, imageThreshBinInv, 40, 255, THRESH_BINARY_INV);


    // display image
    //imshow("imageThreshBinary", imageThreshBinInv );
    //waitKey(0);

    //Step 3.2: Perform morphological operations
    // You will have to carry out this step with different kernel size,
    // kernel shape and morphological operations to see which one (or more) suits you the most.
    // Do not remove those intermediate images and make sure to document your findings.

    ///
    /// YOUR CODE HERE
    ///

    // Summary:
    // smaller kernel size gave me a better result. I have settled on 3
    // In terms of interations I found that 4 gave me the best result.
    // MORPH_CROSS was better the cv::MORPH_ELLIPSE
    int kSizeDilate = 3; // 5
    //int kSizeDilate2 = 3;
    int kSizeErode = 3;
    Mat kernelDilate = getStructuringElement(cv::MORPH_ELLIPSE,Size(kSizeDilate,kSizeDilate));
    //Mat kernelDilate2 = getStructuringElement(cv::MORPH_CROSS,Size(kSizeDilate2,kSizeDilate2)); MORPH_ELLIPSE
    Mat kernelErode = getStructuringElement(cv::MORPH_ELLIPSE,Size(kSizeErode,kSizeErode));
    Mat imageMorph;
    dilate(imageThreshBinInv, imageMorph,kernelDilate,Point(-1,-1),4);
    //dilate(imageMorph, imageMorph,kSizeDilate2,Point(-1,-1),2);
    erode(imageMorph, image, kernelErode,Point(-1,-1),5);
    //dilate(imageMorph, imageMorph,kernelDilate,Point(-1,-1),4);
    imshow("imageMorph",image );

    waitKey(0);


    ///
    /// YOUR CODE HERE
    ///

    // display image

    // Get structuring element/kernel which will be used for dilation
    ///
    /// YOUR CODE HERE
    ///

    ///
    /// YOUR CODE HERE
    ///

    // display image

    // Step 4.1: Create SimpleBlobDetector

    // Setup SimpleBlobDetector parameters.
    SimpleBlobDetector::Params params;

    params.blobColor = 0;

    params.minDistBetweenBlobs = 2;

    // Filter by Area
    params.filterByArea = false;

    // Filter by Circularity
    params.filterByCircularity = true;
    params.minCircularity = 0.8;

    // Filter by Convexity
    params.filterByConvexity = true;
    params.minConvexity = 0.8;

    // Filter by Inertia
    params.filterByInertia = true;
    params.minInertiaRatio = 0.8;

    // Set up detector with params
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

    // Step 4.2: Detect Coins
    // Hints
    // Use detector->detect(image,keypoints) to detect the blobs (coins).
    // The output of the function is a list of keypoints where each keypoint is unique for each blob.
    std::vector<KeyPoint> keypoints;
    detector->detect(image,keypoints);


    // Print the number of coins detected as well.
    std::cout << "Number of coins detected =" << keypoints.size() << std::endl;

    // Detect blobs
    ///
    /// YOUR CODE HERE
    ///

    // Print number of coins detected
    ///
    /// YOUR CODE HERE
    ///

    // Note that we were able to detect all the 9 coins. So that's your benchmark.

    // Step 4.3: Display the detected coins on original image
    // Make sure to mark the center of the blobs as well. Use only the functions discussed in Image Annotation section in Week 1


    // Hints
    // You can extract the coordinates of the center and the diameter of a blob using k.pt and k.size where k is a keypoint.

    // Mark coins using image annotation concepts we have studied so far
    int x,y;
    int radius;
    double diameter;
    ///
    /// YOUR CODE HERE
    ///

    Mat img = imageCopy.clone();
    for (auto k : keypoints){
        Point keyPt;
        keyPt = k.pt;
        x=(int)keyPt.x;
        y=(int)keyPt.y;
        // Mark center in BLACK
        circle(img,Point(x,y),5,Scalar(255,0,0),-1);
        // Get radius of coin
        diameter = k.size;
        radius = (int)diameter/2.0;
        // Mark blob in GREEN
        circle(img, Point(x,y),radius,Scalar(0,255,0),2);
    }

    // display image

    imshow("img",img );
    waitKey(0);

    // Step 4.4: Perform Connected Component Analysis
    // In the final step, perform Connected Component Analysis (CCA) on the binary image to find out the number of connected components.
    // Do you think we can use CCA to calculate number of coins? Why/why not?

    // Find connected components
    // Use displayConnectedComponents function provided above
    ///
    /// YOUR CODE HERE
    ///
    Mat inverse;
    bitwise_not(image, inverse);

    Mat imLabels;
    int componentCount = connectedComponents(inverse,imLabels);
    std::cout << "Number of connected components detected =" << componentCount << std::endl;


    // Print: Number of connected components detected = 11

    // display image
    Mat connectComponentImage =  displayConnectedComponents(imLabels);
    imshow("connectComponentImage",connectComponentImage );
    waitKey(0);
    return;
    // Step 4.5: Detect coins using Contour Detection
    // In the final step, perform Contour Detection on the binary image to find out the number of coins.

    // Find all contours in the image
    ///
    /// YOUR CODE HERE
    ///

    // Find all contours in the image
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours(image, contours, hierarchy, RETR_TREE , CHAIN_APPROX_SIMPLE);


    // Print the number of contours found
    ///
    /// YOUR CODE HERE
    ///

    cout << "Number of contours found = " << contours.size() << std::endl;
    //Print: Number of contours found = 10

    // Draw all contours
    ///
    /// YOUR CODE HERE
    ///
    Mat imgContour = imageCopy.clone();
    drawContours(imgContour, contours, -1, Scalar(0,255,0), 2);

    // display image
    imshow("imgContour",imgContour );
    waitKey(0);

    // Let's only consider the outer contours.
    vector<vector<Point> > contoursExternal;
    findContours(image, contoursExternal, hierarchy, RETR_EXTERNAL , CHAIN_APPROX_SIMPLE);
    std::cout << "Number of external contours found = " << contoursExternal.size() << std::endl;

    // Remove the inner contours
    // Display the result
    ///
    /// YOUR CODE HERE
    ///
    Mat imgContourExternal = imageCopy.clone();
    drawContours(imgContourExternal, contoursExternal, -1, Scalar(0,255,0), 6);
    // display image
    imshow("imgContourExternal",imgContourExternal );
    waitKey(0);

    //So, we only need the inner contours. The easiest way to do that will be to remove the outer contour using area.

    // Print area and perimeter of all contours
    ///
    /// YOUR CODE HERE
    ///

    double area;
    double perimeter;
    for (size_t i=0; i < contours.size(); i++){
        area = contourArea(contours[i]);
        perimeter = arcLength(contours[i],true);
        std::cout << "Contour #" << i+1 << " has area = " << area << " and perimeter = " << perimeter << std::endl;
    }

    /*
    Contour #1 has area = 11350.5 and perimeter = 402.718
    Contour #2 has area = 14402.5 and perimeter = 460.316
    Contour #3 has area = 9291.5 and perimeter = 374.919
    Contour #4 has area = 14746 and perimeter = 460.759
    Contour #5 has area = 9644.5 and perimeter = 372.576
    Contour #6 has area = 39574.5 and perimeter = 755.879
    Contour #7 has area = 17939 and perimeter = 509.529
    Contour #8 has area = 8518.5 and perimeter = 350.434
    Contour #9 has area = 16633 and perimeter = 488.558
    Contour #10 has area = 388699 and perimeter = 2503.31
     */

    // Print maximum area of contour
    // This will be the box that we want to remove
    ///
    /// YOUR CODE HERE
    ///
    std::cout << "Maximum area of contour = " << contourArea(contoursExternal[0]) << std::endl;

    // Remove this contour and plot others
    ///
    /// YOUR CODE HERE
    ///

    Mat imgContourInternalOnly = imageCopy.clone();
    contours.erase(std::remove(contours.begin(), contours.end(),contoursExternal[0]),contours.end());
    drawContours(imgContourInternalOnly, contours, -1, Scalar(255,255,0), 2);
    // display image
    imshow("imgContourInternalOnly",imgContourInternalOnly );
    waitKey(0);

    // Fit circles on coins
    ///
    /// YOUR CODE HERE
    ///

    // Number of coins detected = 9
    Mat imgContourCircle = imageCopy.clone();
    Point center;

    Moments moment;

    for (auto & contour : contours){

        moment = moments(contour);
        x = int(moment.m10/double(moment.m00));
        y = int(moment.m01/double(moment.m00));
        center = Point(x, y);
        // draw the center
        //circle(imgContourCircle,center,10, Scalar(0,0,255), -1);
        // Fit a circle
        Point2f cent;
        float rad;
        minEnclosingCircle(contour, cent, rad);
        circle(imgContourCircle,cent,10, Scalar(0,0,255), -1);
        circle(imgContourCircle,cent,rad, Scalar(255,0,0), 4);
    }
    // display image
    imshow("imgContourCircle",imgContourCircle );
    waitKey(0);

}
Mat displayConnectedComponents(Mat &im)
{
    // Make a copy of the image
    Mat imLabels = im.clone();

    // First let's find the min and max values in imLabels
    Point minLoc, maxLoc;
    double min, max;

    // The following line finds the min and max pixel values
    // and their locations in an image.
    minMaxLoc(imLabels, &min, &max, &minLoc, &maxLoc);

    // Normalize the image so the min value is 0 and max value is 255.
    imLabels = 255 * (imLabels - min) / (max - min);

    // Convert image to 8-bits
    imLabels.convertTo(imLabels, CV_8U);

    // Apply a color map
    Mat imColorMap;
    applyColorMap(imLabels, imColorMap, COLORMAP_JET);

    return imColorMap;
}

void ProcessCoinsB()
{
    // Image path
    string imagePath = "CoinsB.png";
    // Read image
    // Store it in variable image
    ///
    /// YOUR CODE HERE
    ///
    Mat image = imread(imagePath, IMREAD_COLOR);
    Mat imageCopy = image.clone();

    //imshow("image", image);
    //waitKey(0);

    // Step 2.1: Convert Image to Grayscale


    // Convert image to grayscale
    // Store it in the variable imageGray
    ///
    /// YOUR CODE HERE
    ///

    Mat imageGray;
    cv::cvtColor(image,imageGray, COLOR_BGR2GRAY);

    // display image

    //Step 2.2: Split Image into R,G,B Channels
    // Split cell into channels
    // Store them in variables imageB, imageG, imageR
    ///
    /// YOUR CODE HERE
    ///
    Mat imageB, imageG, imageR;
    Mat imageRGBA[3];
    split(image, imageRGBA);

    imageB = imageRGBA[0];
    imageG = imageRGBA[1];
    imageR = imageRGBA[2];

    // display imageB, imageG, imageR

    // display imageB, imageG, imageR
    //imshow("Blue", imageB );
    //imshow("Green", imageG);
    //imshow("Red", imageR);

    //waitKey(0);

    std::cout << imageG.size() << std::endl;

    // Step 3.1: Perform Thresholding
    // You will have to carry out this step with different threshold values to see which one suits you the most.
    // Do not remove those intermediate images and make sure to document your findings.

    ///
    /// YOUR CODE HERE
    ///
    Mat dst;
    // THRESH_BINARY_INV
    //threshold(imageGray, imageThreshBinInv, 40, 255, THRESH_BINARY_INV);
    //  imageG gave me a better result
    //threshold(imageG, imageThreshBinInv, 125, 255, THRESH_BINARY_INV);
    //threshold(imageGray, imageThreshBinInv, 120, 255, THRESH_BINARY);
    threshold(imageB, dst, 124, 255, THRESH_BINARY);


    namedWindow("imageThreshBinInv", WINDOW_NORMAL);
    // display image
    imshow("imageThreshBinInv", dst );
    waitKey(0);
    // display image

    // Step 3.2: Perform morphological operations
    // You will have to carry out this step with different kernel size, kernel shape and morphological operations to see which one (or more) suits you the most.
    // Do not remove those intermediate images and make sure to document your findings.



    int kSizeMorphExCoinB = 5;
    //MORPH_RECT
    Mat kernelMorphExCoinB = getStructuringElement(cv::MORPH_ELLIPSE,Size(kSizeMorphExCoinB,kSizeMorphExCoinB));
    Mat morphEx;
    morphologyEx(dst,morphEx,MORPH_CLOSE,kernelMorphExCoinB,Point(-1,-1),3);  // 6 // 25


    namedWindow("morphEx", WINDOW_NORMAL);
    imshow("morphEx",morphEx );
    waitKey(0);

    int kSizeMorphCloseExCoinB = 5;
    Mat kernelMorphCloseCoinB = getStructuringElement(cv::MORPH_ELLIPSE,Size(kSizeMorphCloseExCoinB,kSizeMorphCloseExCoinB));

    // MORPH_CLOSE
    morphologyEx(morphEx,morphEx,MORPH_OPEN,kernelMorphCloseCoinB,Point(-1,-1),30);  // 6
    namedWindow("morphExClose", WINDOW_NORMAL);
    imshow("morphExClose",morphEx );
    waitKey(0);


    Mat imageEroded;
    int kSizeErodeCoinB = 3; // 3
    Mat kernelErodeCoinB = getStructuringElement(cv::MORPH_ELLIPSE,Size(kSizeErodeCoinB,kSizeErodeCoinB));
    erode(morphEx, imageEroded, kSizeErodeCoinB,Point(-1,-1),3); // 5 // 6

    namedWindow("imageEroded", WINDOW_NORMAL);
    imshow("imageEroded",imageEroded );
    waitKey(0);



    // Step 4.1: Create SimpleBlobDetector
    // Setup SimpleBlobDetector parameters.
    SimpleBlobDetector::Params params;
    params.blobColor = 0;

    params.minDistBetweenBlobs = 2;

    // Filter by Area
    params.filterByArea = false;

    // Filter by Circularity
    params.filterByCircularity = true;
    params.minCircularity = 0.8;

    // Filter by Convexity
    params.filterByConvexity = true;
    params.minConvexity = 0.8;

    // Filter by Inertia
    params.filterByInertia = true;
    params.minInertiaRatio = 0.8;

    // Set up detector with params
    Ptr<SimpleBlobDetector> detector  = SimpleBlobDetector::create(params);

    // Step 4.2: Detect Coins
    // Hints
    // Use detector->detect(image,keypoints) to detect the blobs (coins).
    // The output of the function is a list of keypoints where each keypoint is unique for each blob.
    std::vector<KeyPoint> keypoints;
    detector->detect(imageEroded,keypoints);


    // Print the number of coins detected as well.
    std::cout << "Number of coins detected =" << keypoints.size() << std::endl;



    // Print the number of coins detected as well.

    // Detect blobs
    ///
    /// YOUR CODE HERE
    ///

    // Print number of coins detected
    ///
    /// YOUR CODE HERE
    ///

    // Print Number of coins detected = 8
    // Note that we were able to detect 8 coins. So, that's your benchmark.

    // Step 4.3: Display the detected coins on original image
    // Make sure to mark the center of the blobs as well. Use only the functions discussed in Image Annotation section in Week 1

    // Hints
    // You can extract the coordinates of the center and the diameter of a blob using k.pt and k.size where k is a keypoint.

    // Mark coins using image annotation concepts we have studied so far
    ///
    /// YOUR CODE HERE
    ///

    ///
    /// YOUR CODE HERE
    ///
    int x,y;
    int radius;
    double diameter;
    ///
    /// YOUR CODE HERE
    ///

    Mat img = imageCopy.clone();
    for (const auto& k : keypoints){
        Point keyPt;
        keyPt = k.pt;
        x=(int)keyPt.x;
        y=(int)keyPt.y;
        // Mark center in BLACK
        circle(img,Point(x,y),5,Scalar(255,0,0),-1);
        // Get radius of coin
        diameter = k.size;
        radius = (int)diameter/2.0;
        // Mark blob in GREEN
        circle(img, Point(x,y),radius,Scalar(0,255,0),2);
    }

    // display image
    namedWindow("img", WINDOW_NORMAL);
    imshow("img",img );

    //waitKey(0);

    // Step 4.4: Perform Connected Component Analysis
    // In the final step, perform Connected Component Analysis (CCA) on the binary image to find out the number of connected components.
    // Do you think we can use CCA to calculate number of coins? Why/why not?

    // # Find connected components
    ///
    /// YOUR CODE HERE
    ///
    Mat inverseImage;
    bitwise_not(imageEroded, inverseImage);
    Mat imLabels;
    int componentCount = connectedComponents(inverseImage,imLabels);
    std::cout << "Number of connected components detected =" << componentCount << std::endl;
    // Print Number of connected components detected = 12

    ///
    /// YOUR CODE HERE
    ///

    // display image
    Mat connectComponentImage =  displayConnectedComponents(imLabels);
    namedWindow("connectComponentImage", WINDOW_NORMAL);
    imshow("connectComponentImage",connectComponentImage );
    waitKey(0);

    // Step 4.5: Detect coins using Contour Detection
    // In the final step, perform Contour Detection on the binary image to find out the number of coins.

    // Find all contours in the image
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    // RETR_CCOMP RETR_TREE
    findContours(imageEroded, contours, hierarchy, RETR_TREE  , CHAIN_APPROX_SIMPLE);


    // Print the number of contours found
    ///
    /// YOUR CODE HERE
    ///

    cout << "Number of contours found = " << contours.size() << std::endl;

    // Print: Number of contours found = 13

    // Draw all contours
    ///
    /// YOUR CODE HERE
    ///

    // display image
    Mat imgContour = imageCopy.clone();
    drawContours(imgContour, contours, -1, Scalar(0,255,0), 2);

    // display image
    namedWindow("imgContour", WINDOW_NORMAL);
    imshow("imgContour",imgContour );
    waitKey(0);

    // Let's only consider the outer contours.
    // Remove the inner contours
    // Display the result
    ///
    /// YOUR CODE HERE
    ///

    // Print: Number of contours found = 1

    // Let's only consider the outer contours.
    vector<vector<Point> > contoursExternal;
    findContours(imageEroded, contoursExternal, hierarchy, RETR_EXTERNAL , CHAIN_APPROX_SIMPLE);
    std::cout << "Number of external contours found = " << contoursExternal.size() << std::endl;

    // Remove the inner contours
    // Display the result
    ///
    /// YOUR CODE HERE
    ///
    Mat imgContourExternal = imageCopy.clone();
    drawContours(imgContourExternal, contoursExternal, -1, Scalar(0,255,0), 6);
    // display image
    namedWindow("imgContourExternal", WINDOW_NORMAL);
    imshow("imgContourExternal",imgContourExternal );
    waitKey(0);

    // What do you think went wrong? As we can see, the outer box was detected as a contour and with respect to it,
    // all other contours are internal and that's why they were not detected. How do we remove that? Let's see if we can use area of contours here.

    // Print area and perimeter of all contours
    ///
    /// YOUR CODE HERE
    ///
    double area;
    double perimeter;
    for (size_t i=0; i < contours.size(); i++){
        area = contourArea(contours[i]);
        perimeter = arcLength(contours[i],true);
        std::cout << "Contour #" << i+1 << " has area = " << area << " and perimeter = " << perimeter << std::endl;
    }


    // Print maximum area of contour
    // This will be the box that we want to remove
    ///
    /// YOUR CODE HERE
    ///
    std::cout << "Maximum area of contour = " << contourArea(contoursExternal[0]) << std::endl;

    // Print: Maximum area of contour = 8.28649e+06

    // Remove this contour and plot others
    ///
    /// YOUR CODE HERE
    ///
    Mat imgContourInternalOnly = imageCopy.clone();
    contours.erase(std::remove(contours.begin(), contours.end(),contoursExternal[0]),contours.end());
    drawContours(imgContourInternalOnly, contours, -1, Scalar(255,255,0), 6);

    // display image
    namedWindow("imgContourInternalOnly", WINDOW_NORMAL);
    imshow("imgContourInternalOnly",imgContourInternalOnly );
    waitKey(0);
    // Now, we have to remove the internal contours. Again here we can use area or perimeter.

    // Print area and perimeter of all contours
    ///
    /// YOUR CODE HERE
    //
    for (size_t i=0; i < contours.size(); i++){
        area = contourArea(contours[i]);
        perimeter = arcLength(contours[i],true);
        std::cout << "Contour #" << i+1 << " has area = " << area << " and perimeter = " << perimeter << std::endl;
    }


    // Notice carefully that there are 2 contours that have area smaller than others. In our case, those are contours 6 and 7. Let's remove them.
    // Remove contours
    ///
    /// YOUR CODE HERE
    ///
    std::cout << "contours count: " << contours.size() << std::endl;
    std::cout << "remove the small square inner contours" << std::endl;
    // remove the smaller contours that are less than 800
    contours.erase(std::remove_if(contours.begin(), contours.end(),[](const auto &contour){
        return arcLength(contour,true) <=800;
    }),contours.end());
    std::cout << "after contours count" << contours.size() << std::endl;

    std::cout << "sort the contours ascending" << std::endl;
    std::sort(contours.begin(), contours.end(),[] (const auto &lhs, const auto &rhs)
    {
        return contourArea(lhs) < contourArea(rhs);
    });

    std::cout << "sorted contours" << std::endl;
    for (size_t i=0; i < contours.size(); i++){
        area = contourArea(contours[i]);
        perimeter = arcLength(contours[i],true);
        std::cout << "Contour #" << i+1 << " has area = " << area << " and perimeter = " << perimeter << std::endl;
    }

    vector<vector<Point>> contourLess2;
    std::copy(contours.begin()+2, contours.end(), back_inserter(contourLess2));

    std::cout << "contours: " << contours.size() << " contourLess2: " << contourLess2.size() << std::endl;
    // Draw revised contours
    ///
    /// YOUR CODE HERE
    ///
    // putText(image, to_string(i+1), Point(x+40,y-10), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,255),2);

    Moments moment;
    Point center;

    // display image
    Mat imgContourCircleWithNumbers = imageCopy.clone();
    for (size_t i=0; i < contours.size(); i++){

        moment = moments(contours[i]);
        x = int(moment.m10/double(moment.m00));
        y = int(moment.m01/double(moment.m00));
        center = Point(x, y);
        // draw the center
        //circle(imgContourCircle,center,10, Scalar(0,0,255), -1);
        // Fit a circle
        Point2f cent;
        float rad;
        minEnclosingCircle(contours[i], cent, rad);
        circle(imgContourCircleWithNumbers,cent,10, Scalar(0,0,255), -1);
        circle(imgContourCircleWithNumbers,cent,rad, Scalar(255,0,0), 4);
        putText(imgContourCircleWithNumbers, to_string(i+1), Point(x+40,y-10), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,255),4);
    }
    namedWindow("imgContourCircleWithNumbers", WINDOW_NORMAL);
    imshow("imgContourCircleWithNumbers",imgContourCircleWithNumbers );
    waitKey(0);

    // Fit circles on coins
    ///
    /// YOUR CODE HERE
    ///

    Mat imgContourCircle = imageCopy.clone();
    for (size_t i=0; i < contours.size(); i++){

        moment = moments(contours[i]);
        x = int(moment.m10/double(moment.m00));
        y = int(moment.m01/double(moment.m00));
        center = Point(x, y);
        // draw the center
        //circle(imgContourCircle,center,10, Scalar(0,0,255), -1);
        // Fit a circle
        Point2f cent;
        float rad;
        minEnclosingCircle(contours[i], cent, rad);
        circle(imgContourCircle,cent,10, Scalar(0,0,255), -1);
        circle(imgContourCircle,cent,rad, Scalar(255,0,0), 4);
    }
    // display image
    namedWindow("imgContourCircle", WINDOW_NORMAL);
    imshow("imgContourCircle",imgContourCircle );
    waitKey(0);
    // Print:Number of coins detected = 10

    // display image




}