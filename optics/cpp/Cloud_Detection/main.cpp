// This C++ Program only detects white spaces

// Loading opencv libraries:
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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

    // Loading the Image:
    cv::Mat target = cv::imread("clouds.jpg");
    cout << "Target Size: " << target.size() << endl;
    cv::resize(target, target, cv::Size(target.size().width / 2, target.size().height / 2), cv::INTER_LINEAR);
    cout << "Target Size: " << target.size() << endl;

    cv::Mat original = cv::imread("clouds.jpg");
    cv::resize(original, original, cv::Size(original.size().width / 2, original.size().height / 2), cv::INTER_LINEAR);
    cv::imshow("Original", original);

    // Create second Picture:
    cv::Mat background;
    target.copyTo(background);

    // Convert the Target Image from BGR to HSV:
    cv::cvtColor(target, target, cv::COLOR_BGR2HSV);

    // Create an Image to see the white spaces in the original Target:
    cv::Mat mask;
    cv::inRange(target, whiteLow, whiteHigh, mask);
    cv::imshow("white", mask);

    // Going trough every Pixel from the Original and from mask:
    //cv::cvtColor(mask, mask, cv::COLOR_HSV2RGB);

    cout << "Mask Size Width: " << mask.size().width << "   Mask Size Height: " << mask.size().height <<endl;
    cout << "Background Size: " << background.size() << endl;

    background.copyTo(original);

    // Contours in original:
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cv::drawContours(original, contours, -1, (0, 255, 0), 3);
    cv::imshow("Contours", original);

    // Find Pixels with pieces of Clouds:
    cv::cvtColor(background, background, cv::COLOR_BGR2RGB);
    for(int i = 0; i < background.rows; i++){

        for(int j = 0; j < background.cols; j++){

            // Check if the Pixel is from a piece of a Cloud:
            if((int)mask.at<uchar>((int)i, (int)j) == 255){ // There is Just one Value in every mask Pixel -> mask is Grayscale:

                background.at<cv::Vec3b>((int)i, (int)j)[0] += 100;
                background.at<cv::Vec3b>((int)i, (int)j)[1] += 0;
                background.at<cv::Vec3b>((int)i, (int)j)[2] += 0;
            }
        }
    }

    cv::cvtColor(background, background, cv::COLOR_RGB2BGR);

    cv::imshow("Original Boosted", background);

    cv::waitKey(0);

    return 0;
}