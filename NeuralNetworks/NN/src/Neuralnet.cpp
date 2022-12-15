#include "../include/Neuralnet.hpp"

//------------------Node---------------------

Node::Node(double v) : value(v){

    weights.push_back(0.0);
}

double Node::activation(){

    double activation = 0.0;
    
    return activation;
}

void Node::initWeights(int numNextNodes){

    double random = 0;

    for(int i = 0; i < numNextNodes; i++){
        // Push Back a random Value to the Weights:
        random = double((rand() % 10000)) / 10000;
        weights.push_back(random);

        cout << "Add " << random << endl;
    }
}

double Node::getWeightNo(int n){  return weights[n];}

double Node::getVal(){ return value;}

//----------------Net-------------------------

Net::Net(int m_inputNodes, int m_hiddenLayers, int m_NodesInHiddenLayer, int m_outputNodes){

    // Create Input Layer:
    net.push_back(Layer());
    for(int i = 0; i < m_inputNodes; i++){
        net[0].push_back(1.0);
    }

    // Create Hidden Layers:
    for(int i = 1; i < m_hiddenLayers + 1; i++){
        net.push_back(Layer());
        for(int j = 0; j < m_NodesInHiddenLayer; j++){
            net[i].push_back(0.0);
        }
    }

    // Create Outut Layer:
    net.push_back(Layer());
    for(int i = 0; i < m_outputNodes; i++){
        net[m_hiddenLayers + 1].push_back(2.0);
    }
}

void Net::print(){

    cout << "Neural Net:" << endl << endl;

    for(size_t i = 0; i < net.size(); i++){
        for(size_t j = 0; j < net[i].size(); j++){
            cout << net[i][j].getVal() << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Net::fprint(){

    cout << "Neural Net:" << endl << endl;

    for(size_t i = 0; i < net.size(); i++){
        for(size_t j = 0; j < net.size(); j++){
            if(net[j].size() <= i) cout << "  ";
            else cout << net[j][i].getVal() << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Net::initializeWeights(){

    // Go Trough all Layers:
    for(size_t i = 0; i < net.size() - 1; i++){
        for(int j = 0; j < net[i].size(); j++){
            net[i][j].initWeights(net[i + 1].size());
        }
    }
}

double Net::predict(){
    
    // Here is work to do:

}
