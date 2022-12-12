#include "../include/neuralnet.hpp"
#include <cstdlib>
#include <fstream>
#pragma once

//************************* class Node *****************************

Node::Node(unsigned numOutputs, unsigned myIndex){

    for(int i = 0; i < numOutputs; i++){
        m_outputWeights.push_back(Connection());
        m_outputWeights.back().weight = randomWeight();
    }

    m_myIndex = myIndex;

    learningRate = 0.1;
    alpha = 0.5;
}

void Node::setOutputVal(double val){ m_outputVal = val;}

double Node::getOutpoutVal(void) const{ return m_outputVal;}

double Node::randomWeight(void){return rand() / double(RAND_MAX);}

void Node::feedForward(Layer &prevLayer){

    double sum = 0.0;

    // Sum the Inputs and include the Bias:
    for(int i = 0; i < prevLayer.size(); i++){
        sum += prevLayer[i].getOutpoutVal() * prevLayer[i].m_outputWeights[m_myIndex].weight;
    }

    m_outputVal = activationFunction(sum);
}

void Node::calcOutputGradients(double targetVal){

    double delta = targetVal - m_outputVal;
    m_gradient = delta * Node::activationFunctionDerivative(m_outputVal);
}

void Node::calcHiddenGradients(const Layer &nextLayer){

    double dow = sumDOW(nextLayer);
    m_gradient = dow * Node::activationFunctionDerivative(m_outputVal);
}

double Node::activationFunction(double x){ return tanh(x);}

double Node::activationFunctionDerivative(double x){ return 1.0 - x * x;}

double Node::sumDOW(const Layer &nextLayer) const{

    double sum = 0.0;

    for(int i = 0; i < nextLayer.size() - 1; i++){
        sum += m_outputWeights[i].weight * nextLayer[i].m_gradient;
    }
}

void Node::updateInputWeights(Layer &prevLayer){

    for(int i = 0; i < prevLayer.size(); i++){
        Node &node = prevLayer[i];
        double oldDeltaWeight = node.m_outputWeights[m_myIndex].deltaWeights;

        //double newDeltaWeight = learningRate * node.getOutpoutVal() * m_gradient + alpha * oldDeltaWeight;
        double newDeltaWeight = 
            learningRate
            * node.getOutpoutVal()
            * m_gradient
            + alpha
            * oldDeltaWeight;

        node.m_outputWeights[m_myIndex].deltaWeights = newDeltaWeight;
        node.m_outputWeights[m_myIndex].weight += newDeltaWeight; 
    }
}

//************************* class Net *****************************

Net::Net(const vector<unsigned> &topology){

    unsigned numLayers = topology.size();

    // Add Layers to the Neural Net:
    for(int i = 0; i < numLayers; i++){
        m_layers.push_back(Layer());

        // Calculate Number of weights for Node:
        unsigned numOutputs = i == topology.size() - 1 ? 0 : topology[i + 1];

        // Add Nodes to the Layer:
        for(int j = 0; j <= topology[i]; j++){ // <= Operator for the extra Bias Node
            m_layers.back().push_back(Node(numOutputs, j));

            std::cout << "Made a Node!" << std::endl;
        }

        m_layers.back().back().setOutputVal(1.0);
    }

    m_recentAverageSmoothingFactor = 100.0;
}

void Net::store(string path){

    // Store Weights to file:
    std::ofstream file;
    file.open(path);

    // Iterate through Layers:
    for(int i = 0; i < m_layers.size(); i++){
        // Iterate through Nodes:
        for(int j = 0; j < m_layers[i].size(); j++){

            for(int k = 0; k < m_layers[i][j].m_outputWeights.size(); k++){
                file << m_layers[i][j].m_outputWeights[k].deltaWeights << endl;
                file << m_layers[i][j].m_outputWeights[k].weight << endl;
            }
        }
    }
    cout << "Stored Weights!" << endl;
}

void Net::load(string path){

    cout << "Loading Model..." << endl;
    
    std::ifstream file(path);
    if(!file.is_open()){
        cout << "Could not open " << path << endl;
        return;
    }

    string line;
    double value;
    vector<double> values;

    while(not file.eof()){
        file >> line;
        values.push_back(std::stod(line));
    }
    file.close();

    int iter = 0;

    // Iterate through Layers:
    for(int i = 0; i < m_layers.size(); i++){
        // Iterate through Nodes:
        for(int j = 0; j < m_layers[i].size(); j++){

            for(int k = 0; k < m_layers[i][j].m_outputWeights.size(); k++){
                m_layers[i][j].m_outputWeights[k].deltaWeights = values[iter++];
                m_layers[i][j].m_outputWeights[k].weight = values[iter++];
            }
        }
    }
    file.close();
}

void Net::showWeights(void){

    cout << "Showing Weights: " << endl << endl;

    // Iterate through Layers:
    for(int i = 0; i < m_layers.size(); i++){
        // Iterate through Nodes:
        cout << "Layer " << i + 1 << endl;
        for(int j = 0; j < m_layers[i].size(); j++){
            cout << "Node " << j + 1 << endl;

            for(int k = 0; k < m_layers[i][j].m_outputWeights.size(); k++){
                cout << m_layers[i][j].m_outputWeights[k].deltaWeights << endl;
                cout << m_layers[i][j].m_outputWeights[k].weight << endl << endl;
            }
        }
    }
}

void Net::predict(const vector<double> &inputVals){
    
}

void Net::getResults(vector<double> &resultVals) const{

    resultVals.clear();

    for (unsigned n = 0; n < m_layers.back().size() - 1; ++n) {
        resultVals.push_back(m_layers.back()[n].getOutpoutVal());
    }
}

void Net::feedForward(const vector<double> &inputVals){

    // Check if Layer size is right:
    assert(inputVals.size() == m_layers[0].size() - 1);

    // Assign Inputs to the Inputnodes:
    for(int i = 0; i < inputVals.size(); i++){
        m_layers[0][i].setOutputVal(inputVals[i]);
    }

    // forward propagate:
    for(int i = 1; i < m_layers.size(); i++){
        Layer &prevLayer = m_layers[i - 1];
        for(int j = 0; j < m_layers[i].size() - 1; j++){
            m_layers[i][j].feedForward(prevLayer);
        }
    }
}

void Net::backProp(const vector<double> &targetVals){

    // Calculate overall net error:
    Layer &outputLayer = m_layers.back();
    m_error = 0.0;

    for(int i = 0; i < outputLayer.size() - 1; i++){
        double delta = targetVals[i] - outputLayer[i].getOutpoutVal();
        m_error += delta * delta;
    }
    m_error /= outputLayer.size() - 1;
    m_error = sqrt(m_error);

    // Imlement a recent average measurement:
    m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor + m_error) / (m_recentAverageSmoothingFactor + 1.0);
    
    // Calculate ouput Layer gradients:
    for(int i = 0; i < outputLayer.size() - 1; i++){
        outputLayer[i].calcOutputGradients(targetVals[i]);
    }

    // Calculate gradients on hidden Layers
    for(int i = m_layers.size() - 2; i > 0; i--){
        Layer &hiddenLayer = m_layers[i];
        Layer &nextLayer = m_layers[i + 1];

        for(int j = 0; j < hiddenLayer.size(); j++){
            hiddenLayer[j].calcHiddenGradients(nextLayer);
        }
    }

    // For all Layers from outputs to forst hidden Layer
    // Update connection Weights
    for(unsigned i = m_layers.size() - 1; i > 0; i--){
        Layer &layer = m_layers[i];
        Layer &prevLayer = m_layers[i - 1];

        for(int j = 0; j < layer.size() - 1; j++){
            layer[j].updateInputWeights(prevLayer);
        }

    }
}