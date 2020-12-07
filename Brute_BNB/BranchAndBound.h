#ifndef PEA_BRANCHANDBOUND_H
#define PEA_BRANCHANDBOUND_H


#include <climits>
#include "Matrix.h"
#include "Solution.h"
#include <memory>

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

#endif //PEA_BRANCHANDBOUND_H
