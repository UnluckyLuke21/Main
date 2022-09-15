#include "NeuralNetwork.hpp"

Neuron::Neuron (int connections) : connectionWeights(connections, 0.0){}

Layer::Layer (int n) : neurons(n, Neuron(0)){}

NeuralNetwork::NeuralNetwork (int inputNeurons, int nHLayers, int outputNeurons) : inputLayer(inputNeurons), 