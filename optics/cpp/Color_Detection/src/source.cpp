#include "../include/source.hpp"

#include <vector>

// Loading opencv libraries:
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>

// Defining Function to search specific Color in an Image and return Grayscale Image:
cv::Mat srchCol(cv::Mat frame, std::vector<cv::Scalar> col){

    // Copy frame:
    cv::Mat frameHSV;
    frame.copyTo(frameHSV);

    // Convert Frame from BGR to HSV:
    cv::cvtColor(frameHSV, frameHSV, cv::COLOR_BGR2HSV);

    // Create an Image to see the white spaces in the original Target:
    cv::Mat mask;
    cv::inRange(frameHSV, col[0], col[1], mask);

    return mask;
}