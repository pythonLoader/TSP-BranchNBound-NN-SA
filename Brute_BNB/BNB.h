#include <vector>
#include <climits>
#include <memory>
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    Solution()=default;
    explicit Solution(int);

    void addNode(int node, int value);
    void addNode(int node);
    void setValue(int value);
    int nodeValue(int i);
    int pathLength();
    int value();
    void print();
    void pop();
    void printReverse();
    void clear();

private:
    std::vector<int> path{};
    int _value;

};



class BranchAndBound {
public:
    BranchAndBound(const Matrix &matrix);

    void find();

    Solution solution{};


private:
    const Matrix& matrix;

    int final_res = INT_MAX;
    std::unique_ptr<bool> visited;


    void copyToFinal(int *curr_path);
    int firstMin(int i);
    int secondMin(int i);
    void TSPRec(int curr_bound, int curr_weight,
                int level, int curr_path[]);

};

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
