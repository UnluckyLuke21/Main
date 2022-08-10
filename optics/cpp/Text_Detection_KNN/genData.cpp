#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

#include <iostream>
#include <vector>

const int MIN_CONTOUR_AREA = 100;
const int RESIZED_IMAGE_WIDTH = 20;
const int RESIZED_IMAGE_HEIGHT = 30;

using std::cout;
using std::endl;
using std::vector;

int main(){

    cv::Mat imgTrainingNumbers;     // Input Image
    cv::Mat imgGrayscale;
    cv::Mat imgBlurred;             // Declare various Images
    cv::Mat imgThresh;
    cv::Mat imgThreshCopy;

    vector<vector<cv::Point>> ptContours;
    vector<cv::Vec4i> v4iHierarchy;

    cv::Mat matClassificationInts;  // These are our Training classifications. There need to be some conversions before writing to file later

    cv::Mat matTrainingImagesAsFlattenedFloats;

    // Letters and Digits:
    vector<int> intValidChars = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    imgTrainingNumbers = cv::imread("src/training_chars.png");

    if(imgTrainingNumbers.empty()){

        cout << "Error: Image not read from file" << endl;
        return -1;
    }

    cv::cvtColor(imgTrainingNumbers, imgGrayscale, cv::COLOR_BGR2GRAY);

    cv::GaussianBlur(imgGrayscale, imgBlurred, cv::Size(5, 5), 0);

    cv::adaptiveThreshold(imgBlurred, imgThresh, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY_INV, 11, 2);

    cv::imshow("imgThresh", imgThresh);

    imgThreshCopy = imgThresh.clone();

    cv::findContours(imgThreshCopy, ptContours, v4iHierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Loop for each Contour:
    for(int i = 0; i < ptContours.size(); i++){

        // Check if Contour is big enough to consider:
        if(cv::contourArea(ptContours[i]) > MIN_CONTOUR_AREA){

            cv::Rect boundingRect = cv::boundingRect(ptContours[i]);

            cv::rectangle(imgTrainingNumbers, boundingRect, cv::Scalar(0, 0, 255), 2);

            cv::Mat matROI = imgThresh(boundingRect);

            cv::Mat matROIResized;
            cv::resize(matROI, matROIResized, cv::Size(RESIZED_IMAGE_WIDTH, RESIZED_IMAGE_HEIGHT));

            cv::imshow("matROI", matROI);
            cv::imshow("matROIResized", matROIResized);
            cv::imshow("imgTrainingNumbers", imgTrainingNumbers);

            int intChar = cv::waitKey(0);

            if(intChar == 27) return 0;

            else if (std::find(intValidChars.begin(), intValidChars.end(), intChar) != intValidChars.end()){

                matClassificationInts.push_back(intChar);

                cv::Mat matImageFloat;
                matROIResized.convertTo(matImageFloat, CV_32FC1);

                cv::Mat matImageFlattenedFloat = matImageFloat.reshape(1, 1);

                matTrainingImagesAsFlattenedFloats.push_back(matImageFlattenedFloat);
            }
        }
    }

    cout << "Training Complete" << endl;

    // Save Classifications to File:

    cv::FileStorage fsClassifications("classifications.xml", cv::FileStorage::WRITE);

    if(fsClassifications.isOpened() == false){

        cout << "Error: Unable to open training classifications file, exiting program" << endl;
        return 0;
    }

    fsClassifications << "classifications" << matClassificationInts;
    fsClassifications.release();

    cv::FileStorage fsTrainingImages("images.xml", cv::FileStorage::WRITE);

    if(fsTrainingImages.isOpened() == false){

        cout << "Error: Unable to open training images file, exiting program" << endl;
        return 0;
    }

    fsTrainingImages << "images" << matTrainingImagesAsFlattenedFloats;
    fsTrainingImages.release();

    return 0;
}