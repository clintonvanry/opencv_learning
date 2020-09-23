#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

void GaussianBlur(Mat image);
void boxBlur(Mat image);
// non linear
void MedianFilter(Mat image);
// non linear
void BilateralFilter(Mat image);

int main() {
    std::cout << "Blurring" << std::endl;

    Mat imgSrc = imread("gaussian-noise.png");
    imshow("original", imgSrc);

    /*
    Note:
    The following should be noted while deciding which filter to use for your problem :

    1. Median filtering is the best way to smooth images which have salt-pepper type of noise (sudden high / low values in the neighborhood of a pixel).

    2. Gaussian filtering can be used if there is low Gaussian noise.

    3. Bilateral Filtering should be used if there is high level of Gaussian noise, and you want the edges intact while blurring other areas.

    4.In terms of execution speed, Gaussian filtering is the fastest and Bilateral filtering is the slowest.
     */



    boxBlur(imgSrc);
    GaussianBlur(imgSrc);
    MedianFilter(imgSrc);
    BilateralFilter(imgSrc);

    destroyAllWindows();

    return 0;
}

void boxBlur(Mat image)
{
    //A very common use case for convolution is blurring or smoothing or Low pass filtering.
    // It reduces the noise in the image. The noise in an image can be due to external factors like poor lighting or environment or
    // internal factors like a few pixels in the sensor may have gone bad. We can use image blurring/smoothing techniques to get rid of different types of noise.

    Mat dst1, dst2;

    // Box filter- kernel size 3
    blur( image, dst1, Size( 3, 3 ), Point(-1,-1) );

    //Box filter kernel size 7
    blur(image,dst2,Size(7,7),Point(-1,-1));

    imshow("box blur 3x3", dst1);
    imshow("box blur 7x7", dst2);
    waitKey(0);
}
void GaussianBlur(Mat image)
{
    /*
     * The box kernel explained in the previous section, weights the contribution of all pixels in the neighborhood equally.
     * A Gaussian Blur kernel, on the other hand, weights the contribution of a neighboring pixel based on the distance of the pixel from the center pixel.
     * Unlike the box kernel, the Gaussian kernel is not uniform. The middle pixel gets the maximum weight while the pixels farther away are given less weight.

     An image blurred using the Gaussian kernel looks less blurry compared to a box kernel of the same size.
     Small amount of Gaussian blurring is frequently used to remove noise from an image. It is also applied to the image prior to a noise sensitive image filtering operations.
     For example, the Sobel kernel used for calculating the derivative of an image is a combination of a Gaussian kernel and a finite difference kernel.
     */
    Mat dst1, dst2;

    // Apply gaussian filter
    GaussianBlur(image, dst1, Size( 5, 5 ), 0, 0 );

    // Increased sigma
    GaussianBlur(image,dst2,Size(25,25),50,50);

    imshow("GaussianBlur 5x5", dst1);
    imshow("GaussianBlur 25x25", dst2);
    waitKey(0);
}
void MedianFilter(Mat image)
{
    //Median blur filtering is a nonlinear filtering technique that is most commonly used to remove salt-and-pepper noise from images.
    // As the name suggests, salt-and-pepper noise shows up as randomly occurring white and black pixels that are sharply different from the surrounding.
    // In color images, salt-and-pepper noise may appear as small random color spots.

    int kernelSize = 5;

    Mat medianBlurred;
    // Performing Median Blurring and store in numpy array "medianBlurred"
    medianBlur(image,medianBlurred,kernelSize);
    imshow("medianBlurred", medianBlurred);
    waitKey(0);
}
void BilateralFilter(Mat image)
{
  //A Bilateral Filter is nonlinear, edge-preserving and noise-reducing smoothing filter.
  // Most smoothing filters (e.g. a Gaussian or a Box filter) have a parameter called  σs  (the s in the subscript stands for "spatial")
  // that determines the amount of smoothing. Often this value is closely related to the kernel size.
  // A typical smoothing filter replaces the intensity value of a pixel by the weighted sum of its neighbors.
  // The bigger the neighborhood, the smoother the filtered image looks. The size of the neighborhood is directly proportional to the parameter  σs .

    //diameter of the pixel neighbourhood used during filtering
    int dia=15;

    // Larger the value the distant colours will be mixed together
    // to produce areas of semi equal colors
    double sigmaColor=80;

    // Larger the value more the influence of the farther placed pixels
    // as long as their colors are close enough
    double sigmaSpace=80;

    Mat bilateralFiltered;

    // Apply bilateral filter
    bilateralFilter(image, bilateralFiltered, dia, sigmaColor, sigmaSpace);

    imshow("bilateralFiltered", bilateralFiltered);
    waitKey(0);
}