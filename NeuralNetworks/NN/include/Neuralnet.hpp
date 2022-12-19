#include <vector>
#include <iostream>
#include <cstdlib>

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
    void initWeights(int numNextNodes);
    double getWeightNo(int n);
    double getVal();
    void setValue(double v);
private:
    double value;
    vector<double> weights;
};

class Net{
public:
    //  m_inputNodes = Number of Input Nodes
    //  m_hiddenLayers = Number of Hidden Layers
    //  m_NodesInHiddenLayer = Number of Nodes in a hidden Layer
    //  m_outputNodes = Number of Output Nodes
    Net(int m_inputNodes, int m_hiddenLayers, int m_NodesInHiddenLayer, int m_outputNodes);
    void print();
    void printWeights();
    void fprint();
    void initializeWeights();
    void predict();
    void setInput(vector<double> input);
private:
    vector<Layer> net;
};