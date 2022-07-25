// This C++ Program only detects white spaces

// Loading opencv libraries:
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <vector>

using std::cout;
using std::endl;

// HSV Value Range for the Clouds from Gimp (in opencv there are other Values):
// H 0 - 360
// S 5 - 61
// V 50 - 100

// Defining the White Range:
cv::Scalar whiteLow = cv::Scalar(0, 12, 127);
cv::Scalar whiteHigh = cv::Scalar(180, 155, 255);

int main(){

    // Setup Camera:
    cv::Mat frame;
    cv::VideoCapture webcam(0);

    // Check if VideoCapture is working:
    if(!webcam.isOpened()){ 
        
        cout << "Video Capture failed!" << endl;
        return -1;
    }

    // Loop to compute everything:
    while(webcam.read(frame)){

        // Resize the Frame:
        cv::resize(frame, frame, cv::Size(), 0.5, 0.5);

        
        // Create copy of the Frame:
        cv::Mat frameHSV;
        cv::Mat frameBoosted;
        frame.copyTo(frameHSV);
        frame.copyTo(frameBoosted);

        // Create HSV Color of the Frame:
        cv::cvtColor(frameHSV, frameHSV, cv::COLOR_BGR2HSV);

        // Create an Image to see the white spaces in the original Target:
        cv::Mat mask;
        cv::inRange(frameHSV, whiteLow, whiteHigh, mask);
        cv::imshow("Mask", mask);

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

        cv::imshow("Original", frame);
        cv::imshow("Boosted", frameBoosted);

        // Escape the Program:
        if(cv::waitKey() == 'q') break;
    }

    return 0;
}