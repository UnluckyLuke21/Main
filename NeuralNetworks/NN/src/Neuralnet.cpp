#include "../include/Neuralnet.hpp"

//------------------Node---------------------

Node::Node(double v) : value(v){
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

void Node::setValue(double v){

    if(bias) return;
    else value = v;
}

void Node::biasTrue(){
    bias = true;
}

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

    // Create Bias:

    // Input Layer:
    net[0].push_back(1.0);
    net[0][net[0].size()].biasTrue();

    // Hidden Layers:
    // Loop trough each hidden Layer:
    for(size_t i = 1; i < net.size() - 1; i++){
        net[i].push_back(1.0);
        net[i][net[i].size() - 1].biasTrue();
        cout << "Net[" << i << "][" << net[i].size() - 1 << "] is now a Bias" << endl;
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

void Net::printWeights(){

    cout << "Neural Net Weights:" << endl << endl;

    for(size_t i = 0; i < net.size() - 1; i++){
        cout << "Weights for Layer " << i << endl;
        // Loop for the Nodes in the Layer:
        for(size_t j = 0; j < net[i].size(); j++){
            cout << "Node [" << i << "][" << j <<"]" << endl;
            //Loop for the Weights inside the Node:
            for(size_t k = 0; k < net[i + 1].size(); k++){
                cout << net[i][j].getWeightNo(k) << endl;
            }
        }
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
    cout << endl;
}

void Net::initializeWeights(){

    // Go Trough all Layers:
    for(size_t i = 0; i < net.size() - 1; i++){
        // Go trough the Nodes of the Layer:
        for(size_t j = 0; j < net[i].size(); j++){
            net[i][j].initWeights(net[i + 1].size());
        }
    }
}

double Net::sigmoid(double v){

    return (1 / (1 + pow(M_E, -v))); 
}

void Net::predict(){
    
    double v = 0.0;

    // Loop through the Layers:
    for(size_t i = 1; i < net.size(); i++){ // Start Index by 1 because we dont need to change the Input Node Values
        // Loop trough the Nodes:
        for(size_t j = 0; j < net[i].size(); j++){
            v = 0.0;
            // Calculate Value for the Node:
            // Loop through all Nodes in the Layer behind the current Layer:
            for(size_t k = 0; k < net[i - 1].size(); k++){
                v += net[i - 1][k].getVal() * net[i - 1][k].getWeightNo(j);
            }

            // Pass v into activation Function:

            // Assign the calculated Value to the current Node:
            //cout << "Calculated Value for Node[" << i << "][" << j << "] = " << v << endl;
            v = sigmoid(v);
            net[i][j].setValue(v);
        }

    }
    
}

void Net::setInput(vector<double> input){

    // Set Input into the Value of the Nodes of the Input Layer:
    for(size_t i = 0; i < net[i].size(); i++){
        net[0][i].setValue(input[i]);
    }
}
