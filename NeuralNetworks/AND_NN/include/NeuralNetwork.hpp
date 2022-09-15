#include "Matrix.hpp"

class Layer{
    vector<double> neurons;
};

class NeuralNetwork{
    Matrix inputLayer;
    Matrix hiddenLayers;
    Matrix OutputLayer;

public:
    NeuralNetwork();
};