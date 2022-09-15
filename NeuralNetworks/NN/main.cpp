// Simple Neural Network that can learn the AND Function

//#include "include/Matrix.hpp"

#include <iostream>
#include <math.h>

#define NUM_INPUTS 2
#define NUM_HIDDEN_NODES 2
#define NUM_OUTPUTS 1
#define NUM_TRAINING_SETS 4

using std::cout;
using std::endl;

// Initializing Weights Function:
double init_weights(){

    return ((double)rand()) / ((double)RAND_MAX);
}

// Sigmoid Function:
double sigmoid(double x){

    return 1 / (1 + exp(-x));
}

// dSigmoid Function:
double dsigmoid(double x){

    return x * (1 - x);
}

void shuffle(int* array, size_t n){

    if(n > 1){
        for(size_t i = 0; i < n - 1; i++){
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

int main(){

    constexpr double learningRate (0.1);

    double hiddenLayer[NUM_HIDDEN_NODES];
    double outputLayer[NUM_OUTPUTS];

    double hiddenLayerBias[NUM_HIDDEN_NODES];
    double outputLayerBias[NUM_OUTPUTS];

    double hiddenWeights[NUM_INPUTS][NUM_HIDDEN_NODES];
    double outputWeights[NUM_HIDDEN_NODES][NUM_OUTPUTS];

    // Training Data:
    double trainingInputs[NUM_TRAINING_SETS][NUM_INPUTS] = {{0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}};
    double trainingOutputs[NUM_TRAINING_SETS][NUM_OUTPUTS] = {{0.0}, {0.0}, {0.0}, {1.0}};

    // Initializing Weights in first Layer:
    for(int i = 0; i < NUM_INPUTS; i++){
        for(int j = 0; j < NUM_HIDDEN_NODES; j++){
            hiddenWeights[i][j] = init_weights();
        }
    }

    // Initializing Weights in second Layer:
    for(int i = 0; i < NUM_HIDDEN_NODES; i++){
        for(int j = 0; j < NUM_OUTPUTS; j++){
            outputWeights[i][j] = init_weights();
        }
    }

    // Initializing Weights for Output Layer Bias:
    for(int i = 0; i < NUM_OUTPUTS; i++){
        outputLayerBias[i] = init_weights();
    }

    int trainingSetOrder[] = {0, 1, 2, 3};

    int numberOfEpochs = 10000;

    // Train the Neural Network for a numbrer of Epochs:
    for(int epoch = 0; epoch < numberOfEpochs; epoch++){
        shuffle(trainingSetOrder, NUM_TRAINING_SETS);

        for(int x = 0; x < NUM_TRAINING_SETS; x++){
            int i = trainingSetOrder[x];

            // Forward pass:

            // Compute hidden Layer activation:
            for(int j = 0; j < NUM_HIDDEN_NODES; j++){
                double activation = hiddenLayerBias[j];

                for(int k = 0; k < NUM_INPUTS; k++){
                    activation += trainingInputs[i][k] * hiddenWeights[k][j];
                }

                hiddenLayer[j] = sigmoid(activation);
            }

            // Compute output Layer activation:
            for(int j = 0; j < NUM_OUTPUTS; j++){
                double activation = outputLayerBias[j];

                for(int k = 0; k < NUM_HIDDEN_NODES; k++){
                    activation += hiddenLayer[k] * outputWeights[k][j];
                }

                outputLayer[j] = sigmoid(activation);
            }

            cout << "Input: " << trainingInputs[i][0] << " " << trainingInputs[i][1] << "       Output: " << outputLayer[0] << "       Expected Output: " << trainingOutputs[i][0] << endl;

            // Backprop:

            // Compute change in output weights:
            double deltaOutput[NUM_OUTPUTS];

            for(int j = 0; j < NUM_OUTPUTS; j++){
                double error = (trainingOutputs[i][j] - outputLayer[j]);
                deltaOutput[j] = error * dsigmoid(outputLayer[j]);
            }

            // Compute change in hidden weights:
            double deltaHidden[NUM_HIDDEN_NODES];
            
            for(int j = 0; j < NUM_HIDDEN_NODES; j++){
                double error = 0.0;

                for(int k = 0; k < NUM_OUTPUTS; k++){
                    error += deltaOutput[k] * outputWeights[j][k];
                }

                deltaHidden[j] = error * dsigmoid(hiddenLayer[j]);
            }

            // Apply change in output Weights:
            for(int j = 0; j < NUM_OUTPUTS; j++){
                outputLayerBias[j] += deltaOutput[j] * learningRate;

                for(int k = 0; k < NUM_HIDDEN_NODES; k++){
                    outputWeights[k][j] += hiddenLayer[k] * deltaOutput[j] * learningRate;
                }
            }

            // Apply change in hidden Weights:
            for(int j = 0; j < NUM_HIDDEN_NODES; j++){
                hiddenLayerBias[j] += deltaHidden[j] * learningRate;

                for(int k = 0; k < NUM_INPUTS; k++){
                    hiddenWeights[k][j] += trainingInputs[i][k] * deltaHidden[j] * learningRate;
                }
            }
        }
    }

    cout << endl;

    // Print Final Weights after done Training:
    cout << "Final Hidden Weights" << endl;
    for(int j = 0; j < NUM_HIDDEN_NODES; j++){
        for(int k = 0; k < NUM_INPUTS; k++){
            cout << hiddenWeights[k][j] << " | ";
        }
    }
    cout << endl << endl;

    cout << "Final Hidden Biases" << endl;
    for(int j = 0; j < NUM_HIDDEN_NODES; j++){
        cout << hiddenLayerBias[j] << " | ";
    }
    cout << endl << endl;

    cout << "Final Output Weights" << endl;
    for(int j = 0; j < NUM_OUTPUTS; j++){
        for(int k = 0; k < NUM_HIDDEN_NODES; k++){
            cout << outputWeights[k][j] << " | ";
        }
    }
    cout << endl << endl;

    cout << "Final Output Biases" << endl;
    for(int j = 0; j < NUM_OUTPUTS; j++){
        cout << outputLayerBias[j] << " | ";
    }
    cout << endl << endl;

    return 0;
}