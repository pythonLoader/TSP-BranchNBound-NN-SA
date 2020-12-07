cmake_minimum_required(VERSION 3.15)
project(PEA)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PEA
        BruteForce.cpp
        BruteForce.h
        main.cpp
        Matrix.cpp
        Matrix.h
        Solution.cpp
        Solution.h
        BranchAndBound.cpp BranchAndBound.h Dynamic.cpp Dynamic.h Menu.cpp Menu.h)
