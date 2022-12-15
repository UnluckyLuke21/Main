#include <iostream>
#include <math.h>

#include "../include/Neuralnet.hpp"

using std::cout;
using std::endl;

int main(){

    // Providing a seed value
	srand((unsigned) time(NULL));

    Net myNet(2, 2, 4, 1);
    myNet.print();
    myNet.fprint();

    myNet.initializeWeights();

    return 0;
}