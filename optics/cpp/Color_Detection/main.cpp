// This C++ Program detects Color in every Pixel of the Image

// Loading opencv libraries:
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <vector>

#include "include/macros.hpp"
#include "include/source.hpp"

using std::cout;
using std::endl;

int main(){

    // Setup Camera:
    cv::Mat frame;
    cv::VideoCapture webcam(0);

    // Check if VideoCapture is working:
    if(!webcam.isOpened()){ 
        
        cout << "Video Capture failed!" << endl;
        return -1;
    }

    // Create Mat to safe Grayscale Image:
    cv::Mat mask;

    // Loop to compute everything:
    cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("White Boosted", cv::WINDOW_AUTOSIZE);

    while(webcam.read(frame)){

        // Resize the Frame:
        cv::resize(frame, frame, cv::Size(), WINDOW_SIZE, WINDOW_SIZE);

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