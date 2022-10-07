#include <vector>

using std::vector;

// Node class
class Node{
    vector<double> connectionWeights;

public:
    Node(int connections);

    double activation();
};

// Layer class
class Layer{
    vector<Node> nodes;

public:
    Layer (int n);
};

// NeuralNetwork class
class NeuralNetwork{
    Layer inputLayer;
    vector<Layer> hiddenLayers;
    Layer OutputLayer;

public:
    NeuralNetwork (int inputNeurons, int nHLayers, int outputNeurons);
};