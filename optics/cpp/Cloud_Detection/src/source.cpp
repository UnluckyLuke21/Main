// Loading opencv libraries:
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>

#include <vector>

#include "include/source.hpp"

// Defining Function to search specific Color in an Image and return Grayscale Image:
cv::Mat srchCol(cv::Mat frame, std::vector<cv::Scalar> col){

    // Convert Frame from BGR to HSV:
    cv::cvtColor(frame, frame, cv::COLOR_BGR2HSV);

    // Create an Image to see the white spaces in the original Target:
    cv::Mat mask;
    cv::inRange(frame, col[0], col[0], mask);

    return mask;
}