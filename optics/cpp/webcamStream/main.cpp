#include <opencv2/opencv.hpp>

#include <iostream>
#include <vector>

int main(){

    cv::namedWindow("Video Footage", cv::WINDOW_AUTOSIZE);
    cv::VideoCapture cap(0);

    if(!cap.isOpened()) return -1;

    cv::Mat frame;

    for(;;){

        cap >> frame;
        cv::imshow("Video Footage", frame);

        if(cv::waitKey(33) >= 0) break;
    }

    return 0;
}