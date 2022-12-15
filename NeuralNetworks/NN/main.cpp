#include <iostream>
#include <math.h>

#include "../include/Neuralnet.hpp"

using std::cout;
using std::endl;

int main(){

    // Providing a seed value
	srand((unsigned) time(NULL));

    // Create Input:
    vector<double> in;
    in.push_back(1);
    in.push_back(1);

    Net myNet(1, 1, 2, 1);
    myNet.print();
    myNet.fprint();

    myNet.initializeWeights();

    myNet.predict();

    return 0;
}