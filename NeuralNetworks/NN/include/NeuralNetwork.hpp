#include <vector>

using std::vector;

class Neuron{
    vector<double> connectionWeights;

public:
    Neuron (int connections);

    double activation();
};

class Layer{
    vector<Neuron> neurons;

public:
    Layer (int n);
};

class NeuralNetwork{
    Layer inputLayer;
    vector<Layer> hiddenLayers;
    Layer OutputLayer;

public:
    NeuralNetwork (int inputNeurons, int nHLayers, int outputNeurons);
};