#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void ProcessCoinsA();
void ProcessCoinsB();
Mat displayConnectedComponents(Mat &im);

int main() {
    std::cout << "coin detection assignment" << std::endl;
    ProcessCoinsA();
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

    imshow("image", image);
    waitKey(0);

    // Step 2.1: Convert Image to Grayscale
    // Convert image to grayscale
    // Store it in the variable imageGray
    ///
    /// YOUR CODE HERE
    ///
    Mat imageGray;
    cv::cvtColor(image,imageGray, COLOR_BGR2GRAY);

    // display image
    imshow("Gray image", imageGray);
    waitKey(0);



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
    imshow("Blue", imageB );
    imshow("Green", imageG);
    imshow("Red", imageR);

    waitKey(0);


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
    cout << croppedImage << endl;

    Mat imageThreshBinInv;
    // THRESH_BINARY_INV
    auto result = threshold(imageGray, imageThreshBinInv, 40, 255, THRESH_BINARY_INV);

    // display image
    imshow("imageThreshBinary", imageThreshBinInv );
    waitKey(0);

    //Step 3.2: Perform morphological operations
    // You will have to carry out this step with different kernel size,
    // kernel shape and morphological operations to see which one (or more) suits you the most.
    // Do not remove those intermediate images and make sure to document your findings.

    ///
    /// YOUR CODE HERE
    ///

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

    // Print the number of coins detected as well.

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

    // display image

    // Step 4.4: Perform Connected Component Analysis
    // In the final step, perform Connected Component Analysis (CCA) on the binary image to find out the number of connected components.
    // Do you think we can use CCA to calculate number of coins? Why/why not?

    // Find connected components
    // Use displayConnectedComponents function provided above
    ///
    /// YOUR CODE HERE
    ///
    // Print: Number of connected components detected = 11

    // display image

    // Step 4.5: Detect coins using Contour Detection
    // In the final step, perform Contour Detection on the binary image to find out the number of coins.

    // Find all contours in the image
    ///
    /// YOUR CODE HERE
    ///

    // Print the number of contours found
    ///
    /// YOUR CODE HERE
    ///

    //Print: Number of contours found = 10

    // Draw all contours
    ///
    /// YOUR CODE HERE
    ///

    // display image

    // Let's only consider the outer contours.

    // Remove the inner contours
    // Display the result
    ///
    /// YOUR CODE HERE
    ///

    // display image

    //So, we only need the inner contours. The easiest way to do that will be to remove the outer contour using area.

    // Print area and perimeter of all contours
    ///
    /// YOUR CODE HERE
    ///

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

    // Remove this contour and plot others
    ///
    /// YOUR CODE HERE
    ///

    // display image

    // Fit circles on coins
    ///
    /// YOUR CODE HERE
    ///

    // Number of coins detected = 9

    // display image
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

    imshow("image", image);
    waitKey(0);

    // Step 2.1: Convert Image to Grayscale

    // Convert image to grayscale
    // Store it in the variable imageGray
    ///
    /// YOUR CODE HERE
    ///

    // display image

    //Step 2.2: Split Image into R,G,B Channels
    // Split cell into channels
    // Store them in variables imageB, imageG, imageR
    ///
    /// YOUR CODE HERE
    ///

    // display imageB, imageG, imageR

    // Step 3.1: Perform Thresholding
    // You will have to carry out this step with different threshold values to see which one suits you the most.
    // Do not remove those intermediate images and make sure to document your findings.

    ///
    /// YOUR CODE HERE
    ///

    // display image

    // Step 3.2: Perform morphological operations
    // You will have to carry out this step with different kernel size, kernel shape and morphological operations to see which one (or more) suits you the most.
    // Do not remove those intermediate images and make sure to document your findings.

    ///
    /// YOUR CODE HERE
    ///

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
    Ptr<SimpleBlobDetector> detector  = SimpleBlobDetector::create(params);

    // Step 4.2: Detect Coins
    // Hints
    // Use detector->detect(image,keypoints) to detect the blobs (coins).
    // The output of the function is a list of keypoints where each keypoint is unique for each blob.

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

    // display image

    // Step 4.4: Perform Connected Component Analysis
    // In the final step, perform Connected Component Analysis (CCA) on the binary image to find out the number of connected components.
    // Do you think we can use CCA to calculate number of coins? Why/why not?

    // # Find connected components
    ///
    /// YOUR CODE HERE
    ///

    // Print Number of connected components detected = 12

    ///
    /// YOUR CODE HERE
    ///

    // display image

    // Step 4.5: Detect coins using Contour Detection
    // In the final step, perform Contour Detection on the binary image to find out the number of coins.

    // Find all contours in the image
    ///
    /// YOUR CODE HERE
    ///

    // Print the number of contours found
    ///
    /// YOUR CODE HERE
    ///

    // Print: Number of contours found = 13

    // Draw all contours
    ///
    /// YOUR CODE HERE
    ///

    // display image

    // Let's only consider the outer contours.
    // Remove the inner contours
    // Display the result
    ///
    /// YOUR CODE HERE
    ///

    // Print: Number of contours found = 1

    // What do you think went wrong? As we can see, the outer box was detected as a contour and with respect to it,
    // all other contours are internal and that's why they were not detected. How do we remove that? Let's see if we can use area of contours here.

    // Print area and perimeter of all contours
    ///
    /// YOUR CODE HERE
    ///

    /*
    Contour #1 has area = 145738 and perimeter = 1455.98
    Contour #2 has area = 217499 and perimeter = 1788.13
    Contour #3 has area = 256717 and perimeter = 1929.95
    Contour #4 has area = 242456 and perimeter = 1871.08
    Contour #5 has area = 247177 and perimeter = 1884.15
    Contour #6 has area = 13668 and perimeter = 441.161
    Contour #7 has area = 27054.5 and perimeter = 626.86
    Contour #8 has area = 224098 and perimeter = 1785.87
    Contour #9 has area = 220072 and perimeter = 1782.43
    Contour #10 has area = 142108 and perimeter = 1430.26
    Contour #11 has area = 211140 and perimeter = 1741.88
    Contour #12 has area = 255666 and perimeter = 1905.85
    Contour #13 has area = 8.28649e+06 and perimeter = 12041.4
     */

    // Print maximum area of contour
    // This will be the box that we want to remove
    ///
    /// YOUR CODE HERE
    ///

    // Print: Maximum area of contour = 8.28649e+06

    // Remove this contour and plot others
    ///
    /// YOUR CODE HERE
    ///

    // display image

    // Now, we have to remove the internal contours. Again here we can use area or perimeter.

    // Print area and perimeter of all contours
    ///
    /// YOUR CODE HERE
    //

    /*
    Contour #1 has area = 145738 and perimeter = 1455.98
    Contour #2 has area = 217499 and perimeter = 1788.13
    Contour #3 has area = 256717 and perimeter = 1929.95
    Contour #4 has area = 242456 and perimeter = 1871.08
    Contour #5 has area = 247177 and perimeter = 1884.15
    Contour #6 has area = 13668 and perimeter = 441.161
    Contour #7 has area = 27054.5 and perimeter = 626.86
    Contour #8 has area = 224098 and perimeter = 1785.87
    Contour #9 has area = 220072 and perimeter = 1782.43
    Contour #10 has area = 142108 and perimeter = 1430.26
    Contour #11 has area = 211140 and perimeter = 1741.88
    Contour #12 has area = 255666 and perimeter = 1905.85
     */

    // Notice carefully that there are 2 contours that have area smaller than others. In our case, those are contours 6 and 7. Let's remove them.
    // Remove contours
    ///
    /// YOUR CODE HERE
    ///

    // Draw revised contours
    ///
    /// YOUR CODE HERE
    ///

    // display image

    // Fit circles on coins
    ///
    /// YOUR CODE HERE
    ///

    // Print:Number of coins detected = 10

    // display image

}