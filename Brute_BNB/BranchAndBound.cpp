#include <memory>
#include "BranchAndBound.h"
#include <bits/stdc++.h>


BranchAndBound::BranchAndBound(const Matrix &matrix) : matrix(matrix), solution(matrix.getMatrixSize()+1) {
    visited = std::make_unique<bool>(matrix.getMatrixSize());
}

using namespace std;

void BranchAndBound::copyToFinal(int* curr_path)
{
    solution.clear();
    solution.addNode(curr_path[0], matrix[0][curr_path[0]]);
    for (int i=1; i<matrix.getMatrixSize(); i++)
        solution.addNode(curr_path[i], matrix[curr_path[i-1]][curr_path[i]]);
    solution.addNode(curr_path[0], matrix[curr_path[matrix.getMatrixSize()-1]][curr_path[0]]);
}

int BranchAndBound::firstMin(int i)
{
    int min = INT_MAX;
    for (int k=0; k<matrix.getMatrixSize(); k++)
        if (matrix[i][k]<min && i != k)
            min = matrix[i][k];
    return min;
}

int BranchAndBound::secondMin(int i)
{
    int first = INT_MAX, second = INT_MAX;
    for (int j=0; j<matrix.getMatrixSize(); j++)
    {
        if (i == j)
            continue;

        if (matrix[i][j] <= first)
        {
            second = first;
            first = matrix[i][j];
        }
        else if (matrix[i][j] <= second &&
                 matrix[i][j] != first)
            second = matrix[i][j];
    }
    return second;
}

void BranchAndBound::TSPRec(int curr_bound, int curr_weight,
            int level, int curr_path[])
{

    if (level==matrix.getMatrixSize())
    {
        if (matrix[curr_path[level-1]][curr_path[0]] != 0)
        {
            int curr_res = curr_weight +
                           matrix[curr_path[level-1]][curr_path[0]];

            if (curr_res < final_res)
            {
                copyToFinal(curr_path);
                final_res = curr_res;
            }
        }
        return;
    }
    for (int i=0; i<matrix.getMatrixSize(); i++)
    {
        if (matrix[curr_path[level-1]][i] != 0 &&
            !visited.get()[i])
        {
            int temp = curr_bound;
            curr_weight += matrix[curr_path[level-1]][i];

            if (level==1)
                curr_bound -= ((secondMin(curr_path[level-1]) +
                                secondMin(i))/2);
            else
                curr_bound -= ((firstMin(curr_path[level-1]) +
                                secondMin(i))/2);

            if (curr_bound + curr_weight < final_res)
            {
                curr_path[level] = i;
                visited.get()[i] = true;

                TSPRec(curr_bound, curr_weight, level+1,
                       curr_path);
            }

            curr_weight -= matrix[curr_path[level-1]][i];
            curr_bound = temp;

            memset(visited.get(), false, sizeof(bool)*matrix.getMatrixSize());
            for (int j=0; j<=level-1; j++)
                visited.get()[curr_path[j]] = true;
        }
    }
}

void BranchAndBound::find() {

    int* curr_path = new int(matrix.getMatrixSize()+1);

    int curr_bound = 0;
    memset(curr_path, -1, sizeof(int)*matrix.getMatrixSize()+1);
    memset(visited.get(), 0, sizeof(bool)*matrix.getMatrixSize());

    for (int i=0; i<matrix.getMatrixSize(); i++) {
        curr_bound += (firstMin(i) +
                       secondMin(i));
    }

    curr_bound = (curr_bound&1)? curr_bound/2 + 1 :
                 curr_bound/2;

    visited.get()[0] = true;
    curr_path[0] = 0;

    TSPRec(curr_bound, 0, 1, curr_path);

}

