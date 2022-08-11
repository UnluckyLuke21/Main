// Loading opencv libraries:
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/all_layers.hpp>

#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;

int main(){

    string file_path = "/home/programming/optics/cpp/Object_Detection/";
    vector<string> class_names;
    ifstream ifs(string("src/object_detection_classes_coco.txt").c_str());
    string line;

    if(not ifs.is_open()){

        cout << "Error: Unable to open object_detection_classes_coco.txt, exiting program" << endl;
        return -1;
    }

    // Load all class names inside the Vector:
    while(getline(ifs, line)){

        cout << line << endl;
        class_names.push_back(line);
    }

    auto net = cv::dnn::readNet("src/frozen_inference_graph.pb", "/src/ssd_mobilenet_v2_coco.pbtxt.txt", "TensorFlow");

    return 0;
}