//
// Created by dawid on 11.11.2019.
//

#ifndef PEA_DYNAMIC_H
#define PEA_DYNAMIC_H

#include "Matrix.h"
#include "Solution.h"
#include <climits>
#include <vector>
#include <math.h>

class Dynamic{
public:
    Dynamic(const Matrix &matrix);

    ~Dynamic();

    pair<vector<int>,int> dynamic(int, int);

private:
    const Matrix& matrix;

    pair<vector<int>, int>** subsets;
};

#endif //PEA_DYNAMIC_H
