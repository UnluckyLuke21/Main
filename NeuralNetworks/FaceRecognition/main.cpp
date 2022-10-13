#include <iostream>
#include <vector>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include "../include/neuralnet.hpp"

using std::vector;
using std::cout;
using std::endl;

using cv::Mat;

int main(){

    // Face Detection:
    cv::CascadeClassifier faceCascade;
    faceCascade.load("haarcascade_frontalface_alt.xml");

    // Opening Video:
    Mat frame;
    Mat grayscaleFrame;
    cv::VideoCapture webcam(0);
    if(not webcam.isOpened()) return -1;

    vector<Mat> framesWithFace;

    while(1){
        webcam >> frame;
        cv::flip(frame, frame, 1);

        cv::cvtColor(frame, grayscaleFrame, cv::COLOR_BGR2GRAY);
        //cv::resize(grayscaleFrame, grayscaleFrame, cv::Size(28, 28));

        // Detect Faces:
        vector<cv::Rect> faces;
        faceCascade.detectMultiScale(grayscaleFrame, faces, 1.1, 3, 0, cv::Size(30, 30));

        framesWithFace.clear();
        int i = 0;

        for(cv::Rect area: faces){
            cv::Scalar drawColor = cv::Scalar(255, 0, 0);
            cv::rectangle(frame, cv::Point(cvRound(area.x), cvRound(area.y)), cv::Point(cvRound((area.x + area.width -1)), cvRound((area.y + area.height - 1))), drawColor);

            // Crop the Image:
            framesWithFace.push_back(frame(area));
            cv::resize(framesWithFace[i], framesWithFace[i], cv::Size(28, 28), cv::INTER_LINEAR);
            cv::resize(framesWithFace[i], framesWithFace[i], cv::Size(256, 256), cv::INTER_LINEAR);

            cv::cvtColor(framesWithFace[i], framesWithFace[i], cv::COLOR_BGR2GRAY);
            cv::imshow("Faces", framesWithFace[i++]);
        }

        //grayscaleFrame = frame(faces[0]);

        cv::imshow("Facecam", grayscaleFrame);
        cv::imshow("Live Webcam", frame);

        // Detect Face in the Image:


        if(cv::waitKey(33) >= 0) break;
    }

    // Create Training Data:
    vector<double> inputVals;
    vector<double> targetVals;
    vector<double> resultVals;

    inputVals.push_back(0);
    inputVals.push_back(0);
    targetVals.push_back(0);
    resultVals.push_back(0);

    vector<unsigned> topology;
    topology.push_back(2);
    topology.push_back(3);
    topology.push_back(1);
    Net myNet(topology);

    for(int i = 0; i < 10000; i++){

        // Select random a Case:
        int c = rand() % 4 + 1;
        
        switch (c){
            case 1:
                cout << "Case 1" << endl;
                // Change the Input:
                inputVals[0] = 0;
                inputVals[1] = 0;
                targetVals[0] = 0;

                cout << "Epoch: " << i + 1 << endl;
                cout << "Input: " << inputVals[0] << ", " << inputVals[1] << endl;
                cout << "Expected Output: " << targetVals[0] << endl;

                // Feed the Neural Net:
                myNet.feedForward(inputVals);
                myNet.backProp(targetVals);
                myNet.getResults(resultVals);

                cout << "Actual Output:   " << resultVals[0] << endl << endl;
                
                break;

            case 2:
                cout << "Case 2" << endl;
                // Change the Input:
                inputVals[0] = 1;
                inputVals[1] = 0;
                targetVals[0] = 1;

                // Feed the Neural Net:
                myNet.feedForward(inputVals);
                myNet.backProp(targetVals);
                myNet.getResults(resultVals);

                cout << "Epoch: " << i + 1 << endl;
                cout << "Input: " << inputVals[0] << ", " << inputVals[1] << endl;
                cout << "Expected Output: " << targetVals[0] << endl;

                cout << "Actual Output:   " << resultVals[0] << endl << endl;
                
                break;

            case 3:
                cout << "Case 3" << endl;
                // Change the Input:
                inputVals[0] = 0;
                inputVals[1] = 1;
                targetVals[0] = 1;

                // Feed the Neural Net:
                myNet.feedForward(inputVals);
                myNet.backProp(targetVals);
                myNet.getResults(resultVals);

                cout << "Epoch: " << i + 1 << endl;
                cout << "Input: " << inputVals[0] << ", " << inputVals[1] << endl;
                cout << "Expected Output: " << targetVals[0] << endl;

                cout << "Actual Output:   " << resultVals[0] << endl << endl;
                
                break;

            case 4:
                cout << "Case 4" << endl;
                // Change the Input:
                inputVals[0] = 1;
                inputVals[1] = 1;
                targetVals[0] = 0;

                // Feed the Neural Net:
                myNet.feedForward(inputVals);
                myNet.backProp(targetVals);
                myNet.getResults(resultVals);

                cout << "Epoch: " << i + 1 << endl;
                cout << "Input: " << inputVals[0] << ", " << inputVals[1] << endl;
                cout << "Expected Output: " << targetVals[0] << endl;

                cout << "Actual Output:   " << resultVals[0] << endl << endl;
                
                break;

            default:
                cout << "Default Case" << endl << endl;
        }
    }

    
    //myNet.showWeights();
    //myNet.store("model.txt");
    //myNet.load("model.txt");
    //myNet.showWeights();

    return 0;
}