#include <iostream>
#include <vector>

#include "../include/neuralnet.hpp"

using std::vector;
using std::cout;
using std::endl;

int main(){

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
    Net n(topology);

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