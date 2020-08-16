#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {

    // read the image from disk
    auto img = imread("boy.jpg", IMREAD_COLOR);

    // create a clone of the image
    auto imgClone = img.clone();
    auto imgCloneWithCrop = imgClone.clone();

    // create a new image based on the image read from disk
    auto imgBlackNew = Mat(img.size(),img.type(), Scalar(0,0,0));

    // crop the image
    // x => 170 to 320
    // y => 40 to 200
    // rows, columns
    auto imgCrop = img(Range(40,200),Range(170,320));

    // add our crop image to a clone image
    auto cropHeight = imgCrop.size().height;
    auto cropWidth = imgCrop.size().width;
    // copy to the left of Face
    imgCrop.copyTo(imgCloneWithCrop(Range(40,40+ cropHeight),Range(10,10 + cropWidth)));
    // copy to the right of Face
    imgCrop.copyTo(imgCloneWithCrop(Range(40,40+ cropHeight),Range(330,330 + cropWidth)));

    // resizing image with exact dimensions
    int resizeUpWidth = 600;
    int resizeUpHeight = 900;
    Mat resizeImg;
    resize(img,resizeImg,Size(resizeUpWidth, resizeUpHeight),InterpolationFlags::INTER_LINEAR);

    // resizing image using scaling factors
    double scaleX = 1.5;
    double scaleY = 1.5;
    Mat resizeFactorImg;
    resize(img,resizeFactorImg,Size(),scaleX,scaleY, InterpolationFlags::INTER_LINEAR);


    std::cout << "Created a clone and new black image based on the boy.jpg" << std::endl;

    imshow("boy", img);
    imshow("clone", imgClone);
    imshow("black", imgBlackNew);
    imshow("crop", imgCrop);
    imshow("clone image with crop", imgCloneWithCrop);
    imshow("Manual Resize", resizeImg);
    imshow("Resize By Factor 1.5", resizeFactorImg);

    waitKey(0);

    std::cout << "change new image colour" << std::endl;
    imgBlackNew.setTo(Scalar(100,100,100));
    imshow("black to grey", imgBlackNew);
    waitKey(0);

    destroyAllWindows();
    return 0;
}
