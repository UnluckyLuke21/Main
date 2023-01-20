// This C++ Program detects Color in every Pixel of the Image with HSV

// Loading opencv libraries:
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/dnn.hpp>


#include <iostream>
#include <vector>

#include "include/macros.hpp"
#include "include/source.hpp"

using std::cout;
using std::endl;

int main(){

    // Debug
    if(DEBUG) cout << "DEBUG: Starting Main" << endl;

    // Setup Camera:
    cv::Mat frame;
    cv::VideoCapture webcam;

    // Developer Mode:
    if(DEVELOPER_MODE) webcam.open(0, cv::CAP_V4L2);
    // User Mode:
    else webcam.open(0);

    // Debug
    if(DEBUG) cout << "DEBUG: Camera Model created!" << endl;

    // Check if VideoCapture is working:
    if(!webcam.isOpened()){ 
        
        cout << "Video Capture failed!" << endl;
        return -1;
    }

    // Debug
    if(DEBUG) cout << "DEBUG: Camera Opened successfully!" << endl;

    // Create Mat to safe Grayscale Image:
    cv::Mat mask;

    // Loop to compute everything:
    cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("White Boosted", cv::WINDOW_AUTOSIZE);

    // Debug
    if(DEBUG) cout << "DEBUG: Starting Loop!" << endl;

    while(webcam.read(frame)){

        // Resize the Frame:
        
        // Developer Mode:
        if(DEVELOPER_MODE) cv::resize(frame, frame, cv::Size(), WINDOW_SIZE * 1.5, WINDOW_SIZE * 1.5);
        // User Mode:
        else cv::resize(frame, frame, cv::Size(), WINDOW_SIZE * 0.75, WINDOW_SIZE * 0.75);

        // Flip the Image:
        cv::flip(frame, frame, 1);

        
        // Create copy of the Frame:
        cv::Mat frameHSV;
        cv::Mat frameBoosted;
        frame.copyTo(frameHSV);
        frame.copyTo(frameBoosted);

        mask = srchCol(frame, white);

        // Going trough every Pixel from the Original and from mask:
        // Find Pixels with pieces of Clouds:
        for(int i = 0; i < mask.rows; i++){

            for(int j = 0; j < mask.cols; j++){

                // Check if the Pixel is from a piece of a Cloud:
                if((int)mask.at<uchar>((int)i, (int)j) == 255){ // There is Just one Value in every mask Pixel -> mask is Grayscale:

                    frameBoosted.at<cv::Vec3b>((int)i, (int)j)[0] += 100;
                    frameBoosted.at<cv::Vec3b>((int)i, (int)j)[1] += 0;
                    frameBoosted.at<cv::Vec3b>((int)i, (int)j)[2] += 0;
                }
            }
        }

        if(DEBUG) cv::imshow("Mask", mask);

        cv::imshow("Original", frame);
        cv::imshow("White Boosted", frameBoosted);

        // Escape the Program:
        if(cv::waitKey(33) >= 0) break;
    }

    return 0;
}