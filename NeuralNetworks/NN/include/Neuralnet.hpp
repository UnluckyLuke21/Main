#include <vector>
#include <iostream>
#include <cstdlib>
#include <math.h>

using std::vector;
using std::cout;
using std::endl;

#define BIAS 1

#pragma once

class Node;

typedef vector<Node> Layer;

class Node{
public:
    Node(double v);
    void initWeights(int numNextNodes);
    double getWeightNo(int n);
    double getVal();
    void setValue(double v);
    void biasTrue();
private:
    double value;
    vector<double> weights;
    bool bias = false;
};

class Net{
public:
    //  m_inputNodes = Number of Input Nodes
    //  m_hiddenLayers = Number of Hidden Layers
    //  m_NodesInHiddenLayer = Number of Nodes in a hidden Layer
    //  m_outputNodes = Number of Output Nodes
    Net(int m_inputNodes, int m_hiddenLayers, int m_NodesInHiddenLayer, int m_outputNodes);
    void print();
    double sigmoid(double v);
    void printWeights();
    void fprint();
    void initializeWeights();
    void predict();
    void setInput(vector<double> input);
private:
    vector<Layer> net;
};