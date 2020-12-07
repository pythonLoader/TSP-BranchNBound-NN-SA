#include <algorithm>
#include "fstream"
#include<bits/stdc++.h>
using namespace std;

void read_inp(string fileName){
	string matrixName;

    int matrixSize;

    int** matrix;

    int* shortestPath;

	ifstream file;
	cout << fileName << endl;
    file.open("SMALL/"+fileName+".txt", ios::out);
    file >> matrixName;
    file >> matrixSize;
    shortestPath = new int[matrixSize];
    if(file.is_open()){
        matrix = new int*[matrixSize];
        for(int i=0; i<matrixSize; i++) {
            shortestPath[i] = 0;
            matrix[i] = new int[matrixSize];
            for (int j = 0; j < matrixSize; j++)
                file >> matrix[i][j];
        }
    }
    else{
        cout<<"File cannot be open!"<<endl;
    }
    ofstream out_file;
    out_file.open("Data_For_TSP/"+fileName+"_vertical.txt");
    out_file << matrixSize << endl;
    for(int i=0; i<matrixSize;i++){
        for(int j=0; j<matrixSize; j++){
        	if(i == j){
        		continue;
        	}
            out_file<<i << " "<< j << " " << matrix[i][j]<<"\n";
        }
        // cout<<endl;
    }

}

int main(){
	string data_[] = {"data3","data10","data11","data12","data13","data14","data15",
						"data16","data17","data18"};
	for(int i = 0; i < 10; i++){
		read_inp(data_[i]);
	}
	return 0;
}
