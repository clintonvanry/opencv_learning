#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// https://subscription.packtpub.com/book/application_development/9781785282690/1/ch01lvl1sec10/creating-a-black-and-white-pencil-sketch
// https://anishdubey.com/pencil-sketch-edge-detection-filter-images-opencv
Mat pencilSketch(Mat image, int arguments=0){

    Mat pencilSketchImage;
    cvtColor(image, pencilSketchImage,COLOR_BGR2GRAY);

    // remove the noise
    GaussianBlur(pencilSketchImage,pencilSketchImage,Size(3,3),0,0);

    //Detect edges
    Laplacian(pencilSketchImage, pencilSketchImage, -1, 5);

    // invert the image
    bitwise_not(pencilSketchImage,pencilSketchImage);

    threshold(pencilSketchImage, pencilSketchImage, 150, 255, THRESH_BINARY);

    return pencilSketchImage;
}
// https://analyticsindiamag.com/converting-an-image-to-a-cartoon/
Mat cartoonify(Mat image, int arguments=0){

    // smooth out
    Mat cartoonImage;
    for(int i = 1; i < 3; i++) {
        bilateralFilter(image, cartoonImage, 15, 30, 20);
    }

    // pencil image
    Mat pencilImage = pencilSketch(image);

    cvtColor(pencilImage,pencilImage,COLOR_GRAY2RGB);

    std::cout << typeToString( pencilImage.type()) << std::endl;
    std::cout << pencilImage.size() << std::endl;
    std::cout << typeToString( cartoonImage.type()) << std::endl;
    std::cout << cartoonImage.size() << std::endl;

    bitwise_and(cartoonImage,pencilImage,cartoonImage);

    return cartoonImage;
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
