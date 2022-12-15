#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

#pragma once

class Node{
public:
    Node(double v);
    double activation();
    double weightNo(int n);
private:
    double value;
    vector<double> weights;
};

class Net{
public:
    Net(int m, int n);

private:
    vector<vector<Node>> net;
};