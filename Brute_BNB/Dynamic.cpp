#include "Dynamic.h"

using namespace std;

Dynamic::Dynamic(const Matrix &matrix) : matrix(matrix){
    int colNumber = pow(2,matrix.getMatrixSize())-1;
    subsets = new pair<vector<int>, int>*[colNumber];
    for(int i=0; i<colNumber; i++) {
        subsets[i] = new pair<vector<int>, int>[matrix.getMatrixSize()];
        for(int j=0;j<matrix.getMatrixSize();j++)
            subsets[i][j].second = -1;
    }
}

Dynamic::~Dynamic(){
    delete [] subsets;
}

pair<vector<int>, int> Dynamic::dynamic(int bitmask, int curr) {

    vector<int> path;

    if(subsets[bitmask-1][curr].second!=-1) {
        return subsets[bitmask - 1][curr];
    }

    if(bitmask == (1 << matrix.getMatrixSize()) -1) {
        path.push_back(curr);
        return make_pair(path, matrix[curr][0]);
    }

    int min = INT_MAX;

    for(int i=0; i<matrix.getMatrixSize(); i++){

        int res = bitmask & (1 << i);

        if(res == 0){

            int nBitmask = bitmask | (1 << i);

            pair<vector<int>, int> nPair = dynamic(nBitmask, i);

            int nMin = matrix[curr][i] + nPair.second;

            vector<int> nPath(nPair.first);

            nPath.push_back(curr);

            if(nMin < min) {
                min = nMin;
                path = nPath;
            }
        }
    }

    subsets[bitmask-1][curr].second = min;

    subsets[bitmask-1][curr].first = path;

    return make_pair(path, min);
}