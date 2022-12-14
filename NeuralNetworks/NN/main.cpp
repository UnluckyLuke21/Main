#include <iostream>
#include <math.h>

#include "../include/Neuralnet.hpp"

using std::cout;
using std::endl;

int main(){

    Net myNet(2, 2, 4, 1);
    myNet.print();
    myNet.fprint();

    return 0;
}