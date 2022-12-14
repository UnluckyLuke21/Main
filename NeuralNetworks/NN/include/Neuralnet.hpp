#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

#pragma once

class Node;

typedef vector<Node> Layer;

class Node{
public:
    Node(double v);
    double activation();
    double getWeightNo(int n);
    double getVal();
private:
    double value;
    vector<double> weights;
};

class Net{
public:
    Net(int m_inputNodes, int m_hiddenLayers, int m_NodesInHiddenLayer, int m_outputNodes);
    void print();
    void fprint();
    double predict();


private:
    vector<Layer> net;
};