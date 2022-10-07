#include "NeuralNetwork.hpp"

Node::Node (int connections) : connectionWeights(connections, 0.0){}

Layer::Layer (int n) : nodes(n, Node(0)){}