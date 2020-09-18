#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

Mat convertBGRtoGray(Mat image);
Mat convertBGRtoHSV(Mat image);
void printDiff(Mat img1, Mat img2);

int main()
{

    auto img = imread("sample.jpg");
    auto img2 = imread("sample01.jpg");




    std::cout << typeToString(img.type()) << std::endl;
    namedWindow("sample", WINDOW_NORMAL);
    imshow("sample", img);
    waitKey(0);

    Mat gray_cv;
    cvtColor(img, gray_cv, COLOR_BGR2GRAY);
    std::cout << typeToString(gray_cv.type()) << std::endl;
    Mat gray = convertBGRtoGray(img);


    Mat diffGray;
    absdiff(gray,gray_cv,diffGray);
    printDiff(gray, gray_cv);

    imshow("Gray::Result from custom function", gray);
    imshow("Gray::Result from OpenCV function", gray_cv);
    imshow("Gray::Difference", diffGray);
    waitKey(0);


    //Mat imgTest = Mat(1,1, CV_8UC3, Scalar(47,88,129));
    //https://stackoverflow.com/questions/44896166/converting-a-single-bgr-color-with-cvtcolor-and-using-the-result-to-extract-that
    Mat imgTest = Mat(1,1, CV_8UC3, Scalar(126,105,98));
    Mat hsv = convertBGRtoHSV(imgTest);
    Mat hsv_cv;
    cvtColor(imgTest,hsv_cv,COLOR_BGR2HSV);

    Mat diffHSV;
    absdiff(hsv,hsv_cv,diffHSV);
    printDiff(hsv, hsv_cv);

    imshow("HSV::Result from custom function", hsv);
    imshow("HSV::Result from OpenCV function", hsv_cv);
    imshow("HSV::Difference", diffHSV);
    waitKey(0);


    destroyAllWindows();

    return 0;
}

Mat convertBGRtoGray(Mat image)
{
    // Formulae: gray = (0.299 * red channel) + (0.587 * green channel) +  (0.114 * blue channel)
    Mat workingImage;
    image.convertTo(workingImage,CV_32FC3);

    float blueFactor = 0.114, greenFactor = 0.587, redFactor = 0.299;
    Mat bgrChannels[3];

    split(workingImage, bgrChannels);

    multiply(bgrChannels[0],blueFactor,bgrChannels[0]);
    multiply(bgrChannels[1],greenFactor,bgrChannels[1]);
    multiply(bgrChannels[2],redFactor,bgrChannels[2]);

    add(bgrChannels[0],bgrChannels[1],bgrChannels[0]);
    add(bgrChannels[0],bgrChannels[2],bgrChannels[0]);

    Mat gray;
    bgrChannels[0].convertTo(gray, CV_8UC1);
    std::cout << typeToString(gray.type()) << std::endl;


    return gray;

}




Mat convertBGRtoHSV(Mat image)
{
    Mat hsv_Image = image.clone();

    // compute the max, min and difference
    const int BLUE = 0, GREEN =1, RED = 2;
    for(int row = 0 ; row < image.rows; row++)
    {
        for(int col=0; col < image.cols; col++)
        {
            Vec3b pixel = image.at<Vec3b>(row,col);
            float blue = pixel[BLUE]/255.0f, red = pixel[RED]/255.0f, green = pixel[GREEN]/255.0f;

            float value = std::max<float>(std::max<float>(blue,green),red);
            float minPixel = std::min<float>(std::min<float>(blue,green),red);
            float diffPixel = value - minPixel;

            float hue= -1, saturation = -1;

            // saturation calculation
            if(value == 0.0f)
            {
                saturation = 0.0f;
            }
            else
            {
                saturation = diffPixel / value;
            }

            // hue calculation
            if (value == red)
            {
                hue = 60 * ((green - blue) / diffPixel) ;
            }
            else if (value == green)
            {
                hue = 120 + 60 * ((blue - red) / diffPixel);
            }
            else{
                hue = 240 + 60 * ((red - green) / diffPixel);
            }


            // final adjustment
            if(hue < 0){
                hue+=360.0f;
            }

            // get to 8bit image
            value *= 255.0f;
            saturation *=255.0f;
            hue /=2.0f;

            Vec3b hsvPixel;
            hsvPixel[0] = static_cast<int>(  std::round(hue));
            hsvPixel[1] = static_cast<int>(  std::round(saturation));
            hsvPixel[2] = static_cast<int>(  std::round(value));

            hsv_Image.at<Vec3b>(row,col) = hsvPixel;

        }
    }


    Mat hsv_cv;
    cvtColor(image,hsv_cv,COLOR_BGR2HSV);
    std::cout << "conversion from opencv" << std::endl;
    std::cout << hsv_cv << std::endl;
    //imshow("hsv_cv", hsv_cv);
    //waitKey(0);

    std::cout << "manual conversion" << std::endl;
    std::cout << hsv_Image << std::endl;
    //imshow("hsv_Image", hsv_Image);
    //waitKey(0);


    return hsv_Image;
}
void printDiff(Mat img1, Mat img2) {
    Mat imgDiff;
    absdiff(img1, img2, imgDiff);
    for (int row = 0; row < imgDiff.rows; row++)
    {
        for (int col = 0; col < imgDiff.cols; col++)
        {
            if(imgDiff.at<uchar>(row,col) != 0){
                std::cout<< "difference at (" << row << " , " << col << ")" << std::endl;
            }
        }
    }


}
