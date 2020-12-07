#ifndef PEA_MATRIX_H
#define PEA_MATRIX_H
#include <vector>
#include <string>
#include <iostream>

using namespace::std;

class Matrix{
    string matrixName;

    int matrixSize;

    int** matrix;

    int* shortestPath;


public:
    int* const &operator[] (int) const;

    Matrix(string);

    ~Matrix();

    string getName();

    int getMatrixSize() const;

    void printMatrix();

    int pathValue(int*) const;

};

#endif //PEA_MATRIX_H
