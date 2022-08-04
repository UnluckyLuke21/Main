# pragma once

#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>

#include <vector>

#define DEBUG 0

#define WEBCAM_STREAM 1

#define WINDOW_SIZE 0.75

// Defining HSV Colors for Detection in Image as Vector of cv::Scalar:

// White:
std::vector<cv::Scalar> white = {cv::Scalar(0, 12, 127), cv::Scalar(180, 155, 255)};

// Black:

// Red:

// Green:

// Blue:
