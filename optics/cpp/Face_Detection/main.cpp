#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <vector>

using std::cout;
using std::endl;

#define DEVELOPER_MODE 1
#define DEBUG 0

cv::CascadeClassifier faceCascade;

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

void faceDetection(cv::Mat frame){

    cv::Mat frameGray;
    cv::cvtColor(frame, frameGray, cv::COLOR_BGR2GRAY);

    // Detect Faces:
    std::vector<cv::Rect> faces;

    faceCascade.detectMultiScale(frameGray, faces);

    // Printing Rectangles on Faces in Frame:
    for(size_t i = 0; i < faces.size(); i++){

        cv::Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
        cv::rectangle(frame, faces[i].tl(), faces[i].br(), cv::Scalar(0, 255, 0), 3);
    }

    cv::imshow("Livew Face Detection", frame);

}

int main(){

    // Loading ther pre trained haar cascade classifier:
    std::string faceClassifier = "haarcascades/haarcascade_frontalface_alt2.xml";

    if(not faceCascade.load(faceClassifier)){

        cout << "Could not " << faceClassifier << " exiting program!" << endl;
        return -1;
    }

    cout << "Face Classifier loaded!" << endl;

    cv::VideoCapture webcam;
    if(not setupLivestream(webcam)) return -1;

    cv::Mat frame;
    while(webcam.read(frame)){

        if(frame.empty()){
            
            cout << "No Frame captured!" << endl;
            break;
        }

        // Flip the Image:
        cv::flip(frame, frame, 1);

        // Calling the Face Detection:
        faceDetection(frame);

        // Escape the Program:
        if(cv::waitKey(33) >= 0) break;
    }

    return 0;
}