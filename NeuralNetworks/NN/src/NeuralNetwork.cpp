#include "../include/NeuralNetwork.hpp"

//------------------Node---------------------

Node::Node(double v) : value(v){

    weights.push_back(0.0);

    cout << "Created Node at: " << endl;
}

double Node::activation(){

    double activation = 0.0;
    
    return activation;
}

double Node::weightNo(int n){

    return weights[n];
}

//----------------Net-------------------------

Net::Net(int m, int n){

    // Create the Neural Net consisting of Nodes:
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            net[i].push_back(0.0);
            cout << "Pushing Nodes to the Network: " << i << " " << j << endl;
        }
    }
}
