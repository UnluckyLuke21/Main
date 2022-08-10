// Loading opencv libraries:
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <vector>

#include "include/macros.hpp"
#include "include/source.hpp"

using std::cout;
using std::endl;

int main(){

    // Setup Livestream from Webcam:
    cv::VideoCapture webcam;
    if(setupLivestream(webcam));
    else return -1;

    // Loop to compute everything:
    cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);

    // Debug
    if(DEBUG) cout << "DEBUG: Starting Loop!" << endl;

    cv::Mat frame;

    while(webcam.read(frame)){

        // Flip the Image:
        cv::flip(frame, frame, 1);

        cv::imshow("Original", frame);

        // Escape the Program:
        if(cv::waitKey(33) >= 0) break;
    }


    return 0;
}