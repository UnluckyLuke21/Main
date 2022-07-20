#include <iostream>
//#include <pybind11/pybind11.h>

#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/core/core.hpp>

using namespace std;

int main(){

    cv::Mat frame;
    frame = cv::imread("example.jpeg");

    cout << "Test" << endl;

    if(frame.empty()) cout << "Image not successfully loaded! " << endl;

    cv::imshow("Image", frame);

    cout << "Test in Optics cpp!" << endl;

    cv::waitKey(0);

    return 0;
}

