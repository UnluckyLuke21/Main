#include "../include/Neuralnet.hpp"

//------------------Node---------------------

Node::Node(double v) : value(v){

    weights.push_back(0.0);
}

double Node::activation(){

    double activation = 0.0;
    
    return activation;
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
}

double Net::predict(){
    
    // Here is work to do:

}
