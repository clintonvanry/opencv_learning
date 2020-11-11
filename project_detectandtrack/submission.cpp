#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>

using namespace cv;
using namespace dnn;

/*
 * Project tasks:
 * 1. Implement a fusion of detect and track so that it performs better in terms of speed and accuracy than TLD
 * 2. The output video should show the bounding box in GREEN when the algorithm is performing tracking and BLUE when it is performing detection
 * 3. The display should indicate if tracking fails.
 * Advice from project video: use yolo for detection
 */

Size videoFrameSize(0,0);
Size blobSize (416, 416);
int videoFps = 25;
int sportsBallIndex = 0;
int detected = 0, tracked = 0;  //determine whether to use detector or tracker
Rect2d bbox;
int frame_skip = 5;    //number of frames to skip when detecting (to speed up detection)

bool ReadClassificationFileAndSetSportsBallIndex(const std::string& filename);
void PrintVideoProperties(const VideoCapture& videoCapture);
void PrintLabelOnVideoFrame(Mat& videoFrame, const std::string& label);
void DrawBoundBoxOnVideoFrame(Mat& videoFrame, bool isTrackingBox );

// Get the names of the output layers
std::vector<std::string> getOutputsNames(const Net& net);
// Remove the bounding boxes with low confidence using non-maxima suppression
void postprocess(Mat& frame, const std::vector<Mat>& out);
void DetectBall(Mat& videoFrame, Net& net);

int main() {
    std::cout << "Detect and track the soccer ball in the video." << std::endl;
    std::string videoFilename = "./soccer-ball.mp4";
    std::string classificationFile = "../data/models/coco.names";

    if(!ReadClassificationFileAndSetSportsBallIndex(classificationFile)){
        std::cout << "failed to read file" << std::endl;
        return -1;
    }


    // Give the configuration and weight files for the model
    std::string modelConfiguration = "../data/models/yolov3.cfg";
    // not include in the project as it is too big.
    std::string modelWeights = "../data/models/yolov3.weights";
    // Load the network
    Net net = readNetFromDarknet(modelConfiguration, modelWeights);


    // check to see if the video can be used and is in the directory to be read.
    VideoCapture videoCapture(videoFilename);
    if(!videoCapture.isOpened())
    {
        std::cerr << "Failed to open video file" << std::endl;
        videoCapture.release();
        return -1;
    }
    PrintVideoProperties(videoCapture);

    std::string windowName = "Detect and track";
    namedWindow(windowName, WINDOW_NORMAL);
    resizeWindow(windowName, videoFrameSize.width, videoFrameSize.height);

    Ptr<Tracker> tracker;
    tracker = TrackerKCF::create();

    std::string outputFilename = "detectAndTrackOutput.mp4";
    Mat videoFrame, blob;
    int frameNumber = 0;
    std::string label;

    VideoWriter videoWriter;
    videoWriter.open(outputFilename,VideoWriter::fourcc('M','J','P','G'),videoFps,videoFrameSize);


    // play the video
    while(waitKey(1) < 0){

        videoCapture >> videoFrame;
        frameNumber++;
        std::cout << "video frame number:" << frameNumber << std::endl;

        if(videoFrame.empty()){
            std::cout << "Reached the end of the video file." << std::endl;
            std::cout << "Output file is stored as " << outputFilename << std::endl;
            waitKey(2500);
            break;
        }

        if(detected == 0 && tracked == 0 && frameNumber % frame_skip == 0) {

            DetectBall(videoFrame, net);

            if (detected == 1) {
                tracker = TrackerCSRT::create();
                tracker->init(videoFrame, bbox);
                detected = 0;
                tracked = 1;
            }

            // Put efficiency information. The function getPerfProfile returns the overall time for inference(t) and the timings for each of the layers(in layersTimes)
            std::vector<double> layersTimes;
            double freq = getTickFrequency() / 1000;
            double t = net.getPerfProfile(layersTimes) / freq;
            label = format("Detection on frame %d Inference time for a frame : %.2f ms",frameNumber,  t);
            PrintLabelOnVideoFrame(videoFrame,label);
        }
        else if(detected == 0 && tracked == 1)
        {
            bool ok = tracker->update(videoFrame, bbox);

            if (ok)
            {
                std::cout << "Tracking success" << std::endl;

                label = format("Tracking success on frame %d.",frameNumber);
                PrintLabelOnVideoFrame(videoFrame,label);
                // Tracking success : Draw the tracked object
                DrawBoundBoxOnVideoFrame(videoFrame,true);

            }
            else
            {
                label = format("Tracking failure on frame %d.",frameNumber);
                PrintLabelOnVideoFrame(videoFrame,label);
                tracked = 0;
                tracker.release();
            }
        }
        if (detected == 0 && tracked == 0)
        {
            std::cout << "Detection and Tracking failure" << std::endl;
            label = format("Detection and Tracking failure on frame %d.",frameNumber);
            PrintLabelOnVideoFrame(videoFrame,label);

        }

        videoWriter.write(videoFrame);
        imshow(windowName, videoFrame);

    }

    // cleanup
    videoCapture.release();
    videoWriter.release();
    destroyAllWindows();
    return 0;
}

void DetectBall(Mat& videoFrame, Net& net)
{
    Mat blob;
    // Create a 4D blob from a video frame.
    blobFromImage(videoFrame, blob, 1 / 255.0, blobSize, Scalar(0, 0, 0), true, false);

    //Sets the input to the network
    net.setInput(blob);

    // Runs the forward pass to get output of the output layers
    std::vector<Mat> outs;
    net.forward(outs, getOutputsNames(net));
    postprocess(videoFrame, outs);

}


void PrintLabelOnVideoFrame(Mat& videoFrame, const std::string& label)
{
    putText(videoFrame, label, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 255),2);
}
void DrawBoundBoxOnVideoFrame(Mat& videoFrame,  bool isTrackingBox )
{
    if(isTrackingBox)
    {
        rectangle(videoFrame, bbox, Scalar(0, 255, 0), 2, 1);
    }
    else{
        rectangle(videoFrame, bbox, Scalar(255, 0, 0), 2, 1);
    }
}
void PrintVideoProperties(const VideoCapture& videoCapture)
{
    int width, height, fps;

    width = static_cast<int>( videoCapture.get(CAP_PROP_FRAME_WIDTH));
    height = static_cast<int>(videoCapture.get(CAP_PROP_FRAME_HEIGHT));
    fps = static_cast<int>( videoCapture.get(CAP_PROP_FPS));

    std::cout << "Video width: " << width << std::endl;
    std::cout << "Video height: " << height << std::endl;
    std::cout << "Video duration: " << videoCapture.get(CAP_PROP_FRAME_COUNT) << std::endl;
    std::cout << "Video fps: " << fps  << std::endl;

    // needed for the recording
    videoFrameSize = Size(width,height);
    videoFps = fps;
}
bool ReadClassificationFileAndSetSportsBallIndex(const std::string& filename)
{
    std::vector<std::string> classes;
    std::ifstream streamReader(filename);
    if(!streamReader){
        std::cerr << "Cannot open file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while(std::getline(streamReader,line))
    {
        if(!line.empty()){
            classes.push_back(line);
        }
    }
    streamReader.close();

    auto match = std::find(classes.begin(), classes.end(),"sports ball");
    if(match != classes.end()){
        sportsBallIndex = match - classes.begin();
    }

    return true;
}
std::vector<std::string> getOutputsNames(const Net& net)
{
    static std::vector<std::string> names;
    if (names.empty())
    {
        //Get the indices of the output layers, i.e. the layers with unconnected outputs
        std::vector<int> outLayers = net.getUnconnectedOutLayers();

        //get the names of all the layers in the network
        std::vector<String> layersNames = net.getLayerNames();

        // Get the names of the output layers in names
        names.resize(outLayers.size());
        for (size_t i = 0; i < outLayers.size(); ++i) {
            names[i] = layersNames[outLayers[i] - 1];
        }
    }
    return names;
}

// Remove the bounding boxes with low confidence using non-maxima suppression
void postprocess(Mat& frame, const std::vector<Mat>& outs)
{
    //float confidenceThreshold  = 0.5;
    float confidenceThreshold  = 0.5;
    float nmsThreshold = 0.8;  // Non-maximum suppression threshold 0.4
    std::vector<int> classIds;
    std::vector<float> confidences;
    std::vector<Rect> boxes;

    for (const auto & out : outs)
    {
        // Scan through all the bounding boxes output from the network and keep only the
        // ones with high confidence scores. Assign the box's class label as the class
        // with the highest score for the box.
        auto* data = (float*)out.data;
        for (int j = 0; j < out.rows; ++j, data += out.cols)
        {
            Mat scores = out.row(j).colRange(5, out.cols);
            Point classIdPoint;
            double confidence;
            // Get the value and location of the maximum score
            minMaxLoc(scores, nullptr, &confidence, nullptr, &classIdPoint);
            if (confidence > confidenceThreshold)
            {
                int centerX = (int)(data[0] * frame.cols);
                int centerY = (int)(data[1] * frame.rows);
                int width = (int)(data[2] * frame.cols);
                int height = (int)(data[3] * frame.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;

                classIds.push_back(classIdPoint.x);
                confidences.push_back((float)confidence);
                boxes.emplace_back(left, top, width, height);
            }
        }
    }

    // Perform non maximum suppression to eliminate redundant overlapping boxes with
    // lower confidences
    std::vector<int> indices;
    NMSBoxes(boxes, confidences, confidenceThreshold, nmsThreshold, indices);
    for (int idx : indices)
    {
        if(classIds[idx] == sportsBallIndex)
        {
            Rect box = boxes[idx];

            detected = 1;
            bbox.x = box.x;
            bbox.y = box.y;
            bbox.width = box.width;
            bbox.height = box.height;
            DrawBoundBoxOnVideoFrame(frame,false);
        }

    }
}