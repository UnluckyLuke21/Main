#include "Matrix.hpp"

// Default Constructor:
Matrix::Matrix() : rows(0), cols(0){

matrix.push_back(vector<double>(0));
}

// Base Constructor:
Matrix::Matrix(int r, int c) : rows(r), cols(c){

    for(size_t i = 0; i < (size_t)cols; i++){

        // Spalten erstellen:
        matrix.push_back(vector<double>());

        for(size_t j = 0; j < (size_t)rows; j++){

            // Zeilen erstellen:
            matrix[i].push_back(0.0);
        }
    }
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), matrix(other.matrix){}

void Matrix::print(){

    for(size_t i = 0; i < (size_t)this->rows; i++){
        for(size_t j = 0; j < (size_t)this->cols; j++){

            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
}