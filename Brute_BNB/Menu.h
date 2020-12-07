//
// Created by dawid on 11.11.2019.
//

#ifndef PEA_MENU_H
#define PEA_MENU_H

#include "BranchAndBound.h"
#include "BruteForce.h"
#include "Dynamic.h"
#include "Matrix.h"

class Menu{

public:

    void menuMain();


    void menuBranchnndBound(const Matrix &matrix);

    void menuBruteForce(const Matrix &matrix);

    void menuDynamic(const Matrix &matrix);
};

#endif //PEA_MENU_H
