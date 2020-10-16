#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <opencv2/opencv.hpp>

namespace fs = std::filesystem;

using namespace cv;
int main() {
    std::cout << "Panarama stitching assignment" << std::endl;
    Mat finalResult = imread("scene_result.png");

    std::vector<Mat> images;
    std::vector<std::string> files;
    std::string destination = "panorama.jpg";

    std::string pathToSceneImages = "../scene";
    for(const auto & fileEntry : fs::directory_iterator(pathToSceneImages))
    {
        files.push_back( fileEntry.path().string());
        std::cout << fileEntry.path() << std::endl;
    }

    std::sort(files.begin(),files.end());
    for (size_t i = 0; i < files.size(); ++i)
    {
        Mat img = imread(files[i]); // load the image
        if (img.empty())            // invalid image, skip it.
        {
            std::cout << files[i] << " is invalid!" << std::endl;
            continue;
        }

        // Create a list of images
        images.push_back(img);
    }

    // code here to complete the task.
    Mat panorama;
    Stitcher::Mode mode = Stitcher::PANORAMA;
    Ptr<Stitcher> imageStitcher = Stitcher::create(mode);
    Stitcher::Status status = imageStitcher->stitch(images,panorama);

    if (status != Stitcher::OK)
    {
        std::cout << "Can't stitch images, error code = " << int(status) << std::endl;
        return EXIT_FAILURE;
    }

    imwrite(destination,panorama);

    imshow("Desired Result", finalResult);
    imshow("Result", panorama);

    waitKey(0);
    return 0;
}
