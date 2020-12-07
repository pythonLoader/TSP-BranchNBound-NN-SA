//
// Created by dawid on 11.11.2019.
//

#include "Menu.h"
#include <chrono>
void Menu::menuMain() {
    string fileName;
    int option;
    cout << "Input File: ";
    cin>>fileName;
    Matrix matrix(fileName);
    do {
        cout << "1. Print Matrix" << endl;
        cout<< "2. Brute Force menu" <<endl;
        // cout<< "3. Dynamic menu" <<endl;
        cout<< "4. Branch and Bound menu" <<endl;
        cout<< "5. Exit" <<endl;
        cout<<"Option: ";
        cin>>option;
        switch (option) {
            case 1:
                matrix.printMatrix();
                cout<<endl;
                break;
            case 2:
                menuBruteForce(matrix);
                break;
            case 3:
                menuDynamic(matrix);
                break;
            case 4:
                menuBranchnndBound(matrix);
                break;
            case 5:
                break;
            default:
                cout<<"Please choose a valid option"<<endl;
                break;
        }
    }while(option!=5);
}

void Menu::menuBruteForce(const Matrix &matrix) {
    BruteForce bf{matrix};
    int* permuteArr = new int[matrix.getMatrixSize()];
    for(int i=0; i<matrix.getMatrixSize();i++)
        permuteArr[i] = i;
    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> elapsedSeconds;
    int option1, option2;
    do {
        cout << "Menu" << endl;
        cout << "1. Execute Brute Force" << endl;
        cout << "2. Exit" << endl;
        cout<<"Option: "<<endl;
        cin>>option1;
        switch (option1) {
            case 1:
                start = chrono::system_clock::now();
                bf.bruteForceSwap(permuteArr, 1);
                end = chrono::system_clock::now();
                elapsedSeconds = end - start;
                cout<<"Time to execute algorithm BF: "<<elapsedSeconds.count()<<"s"<<endl;
                do {
                    cout << "1. Show cost" << endl;
                    cout << "2. Show Path" << endl;
                    cout << "3. Exit" << endl;
                    cout<<"Option: "<<endl;
                    cin>>option2;
                    switch (option2) {
                        case 1:
                            cout<<bf.solution.value()<<endl;
                            cout<<endl;
                            break;
                        case 2:
                            bf.solution.print();
                            cout<<endl;
                            break;
                        case 3:
                            bf.solution.clear();
                            break;
                        default:
                            cout << "Please choose a valid option" << endl;
                            break;
                    }
                }while (option2!=3);
                break;
            case 2:
                break;
            default:
                cout << "Please choose a valid option" << endl;
                break;
        }
    }while (option1!=2);
}

void Menu::menuDynamic(const Matrix &matrix) {
    Dynamic dynamic{matrix};
    int bitmask = 1, curr = 0;
    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> elapsedSeconds;
    pair<vector<int>, int> minPair;
    int option1, option2;
    do {
        cout << "Menu" << endl;
        cout << "1. Execute algorithm DP" << endl;
        cout << "2. Exit" << endl;
        cout<<"Option: "<<endl;
        cin>>option1;
        switch (option1) {
            case 1:
                start = chrono::system_clock::now();
                minPair = dynamic.dynamic(bitmask, curr);
                end = chrono::system_clock::now();
                elapsedSeconds = end - start;
                cout<<"Time to execute algorithm DP: "<<elapsedSeconds.count()<<"s"<<endl;
                do {
                    cout << "1. Show cost" << endl;
                    cout << "2. Show Path" << endl;
                    cout << "3. Exit" << endl;
                    cout<<"Option: "<<endl;
                    cin>>option2;
                    switch (option2) {
                        case 1:
                            cout<<minPair.second;
                            cout<<endl;
                            break;
                        case 2:
                            for(int i=minPair.first.size()-1; i>=0; i--)
                                cout<<minPair.first[i]<<" ";
                            cout<<endl;
                            break;
                        case 3:
                            break;
                        default:
                            cout << "Please choose a valid option" << endl;
                            break;
                    }
                }while (option2!=3);
                    break;
                    case 2:
                        break;
                    default:
                        cout << "Please choose a valid option" << endl;
                    break;

        }
    }while (option1!=2);
}

void Menu::menuBranchnndBound(const Matrix& matrix){
    BranchAndBound bnb{matrix};
    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> elapsedSeconds;
    int option1, option2;
    do {
        cout << "Menu" << endl;
        cout << "1. Execute algorithm Branch and Bound" << endl;
        cout << "2. Exit" << endl;
        cout<<"Option: "<<endl;
        cin>>option1;
        switch (option1) {
            case 1:
                start = chrono::system_clock::now();
                bnb.find();
                end = chrono::system_clock::now();
                elapsedSeconds = end - start;
                cout << "Time to run -> "<< elapsedSeconds.count() <<"s" << endl; 
                do {
                    cout << "1. Show cost" << endl;
                    cout << "2. Show Path" << endl;
                    cout << "3. Exit" << endl;
                    cout<<"Option: "<<endl;
                    cin>>option2;
                    switch (option2) {
                        case 1:
                            cout<<bnb.solution.value()+1<<endl;
                            cout<<endl;
                            break;
                        case 2:
                            bnb.solution.pop();
                            bnb.solution.print();
                            cout<<endl;
                            break;
                        case 3:
                            break;
                        default:
                            cout << "Please choose a valid option" << endl;
                            break;
                    }
                }while (option2!=3);
                    break;
                    case 2:
                        break;
                    default:
                        cout << "Please choose a valid option" << endl;
                    break;
        }
    }while (option1!=2);
}