#include <iostream>
#include <vector>
#include <cassert>
#include <math.h>
#include <string>
#include <fstream>

using std::vector;
using std::cout;
using std::endl;
using std::string;

struct Connection{
    double weight;
    double deltaWeights;
};

class Node;
typedef vector<Node> Layer;

//************************* class Node *****************************

class Node{
public:
    Node(unsigned numOutputs, unsigned myIndex);
    void setOutputVal(double val);
    double getOutpoutVal(void) const;
    void feedForward(Layer &prevLayer);
    void calcOutputGradients(double targetVal);
    void calcHiddenGradients(const Layer &nextLayer);
    void updateInputWeights(Layer &prevLayer);
    vector<Connection> m_outputWeights;

private:
    double learningRate;
    double alpha;
    double activationFunction(double x);
    double activationFunctionDerivative(double x);
    double randomWeight(void);
    double sumDOW(const Layer &nextLayer) const;
    double m_outputVal;
    
    unsigned m_myIndex;
    double m_gradient;
};

//************************* class Net *****************************

class Net{
public:
    Net (const vector<unsigned> &topology);
    void feedForward(const vector<double> &inputVals);
    void backProp(const vector<double> &targetVals);
    void getResults(vector<double> &resultVals) const;
    void store(string path);
    void load(string path);
    void showWeights(void);

private:
    vector<Layer> m_layers;
    double m_error;
    double m_recentAverageError;
    double m_recentAverageSmoothingFactor;
};
