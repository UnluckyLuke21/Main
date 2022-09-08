#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

class Matrix{

    int rows; // Zeile
    int cols; // Spalte

    vector<vector<double>> matrix;

public:
    Matrix();                       // Default Constructor
    Matrix(int r, int c);           // Base Constructor
    Matrix(const Matrix& other);    // Copy Constructor

    void print();

};