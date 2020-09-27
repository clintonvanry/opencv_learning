#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat cartoonify(Mat image, int arguments=0){

    Mat cartoonImage;

    /// YOUR CODE HERE
    cartoonImage = image.clone();

    return cartoonImage;
}

Mat pencilSketch(Mat image, int arguments=0){

    Mat pencilSketchImage;

    /// YOUR CODE HERE
    pencilSketchImage = image.clone();

    return pencilSketchImage;
}

int main() {
    std::cout << "Instagram filter" << std::endl;

    Mat expectedOutput = imread("expectedOutput.JPG");

    string imagePath = "trump.jpg";
    Mat image = imread(imagePath);

    Mat cartoonImage = cartoonify(image);
    Mat pencilSketchImage = pencilSketch(image);

    imshow("Original", image);
    imshow("Cartoon", cartoonImage);
    imshow("Pencil Sketch", pencilSketchImage);
    imshow("Expected Output", expectedOutput);
    waitKey(0);
    destroyAllWindows();

    return 0;
}
