#include "Matrix.hpp"

class Neuron{
    double value;
    vector<double> connectionWeights;


};

class Layer{
    vector<Neuron> neurons;
};

class NeuralNetwork{
    Layer inputLayer;
    vector<Layer> hiddenLayers;
    Layer OutputLayer;

public:
    NeuralNetwork();
};