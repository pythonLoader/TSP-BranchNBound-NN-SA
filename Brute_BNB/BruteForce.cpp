#include "BruteForce.h"
#include "Solution.h"

BruteForce::BruteForce(const Matrix &matrix) : matrix(matrix), solution(matrix.getMatrixSize()+1) {

}

void BruteForce::bruteForceSwap(int* arr,int begin){
    if(begin==matrix.getMatrixSize()-1) {
        int temp = matrix.pathValue(arr);
        if(temp < solution.value()) {
            solution.clear();
            solution.setValue(temp);
            for(int i=0;i<matrix.getMatrixSize();i++)
               solution.addNode(arr[i]);
        }
    }
    else{
        for(int i=begin; i<matrix.getMatrixSize();i++){
            std::swap(arr[begin],arr[i]);

            bruteForceSwap(arr,begin+1);

            std::swap(arr[begin], arr[i]);
        }
    }
}

