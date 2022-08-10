#include "../include/source.hpp"

#include <iostream>

// Loading opencv libraries:
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>

#include "../include/macros.hpp"


using std::cout;
using std::endl;

int setupLivestream(cv::VideoCapture& cap){

    // Developer Mode
    if(DEVELOPER_MODE) cap.open(0, cv::CAP_V4L2);
    // User Mode
    else cap.open(0);

    // Debug
    if(DEBUG) cout << "DEBUG: Camera Model created!" << endl;

    // Check if VideoCapture is working:
    if(!cap.isOpened()){ 
        
        cout << "Video Capture failed!" << endl;
        return -1;
    }

    // Debug
    if(DEBUG) cout << "DEBUG: Camera Opened successfully!" << endl;

    return 1;
}