#include<bits/stdc++.h>
#define ll long long
#define inf 10000000
using namespace std;

int graph[100][100];
int nodeNo;
int visited[100];

ll bruteForce(int nodesCovered, int currentNode){

	if(nodesCovered == nodeNo)
		return graph[currentNode][0];

	ll minCost = inf+1;
	int minNodeIdx = -1;

	for(int i=0;i<nodeNo;i++){
		if(!visited[i]){
			visited[i] = 1;
			ll tempCost = graph[currentNode][i] + bruteForce(nodesCovered+1, i);
			visited[i] = 0;
			minCost = tempCost<minCost?tempCost:minCost;
		}
	}

	return minCost;
}

int main(){

	for(int i=0;i<100;i++){
		for(int j=0;j<100;j++)
			graph[i][j] = inf;
	}
	for(int i=0;i<100;i++)
		visited[i] = 0;

	//take in the input
	ifstream myfile("data10_vertical.txt");
	string line;

	getline(myfile, line);
	istringstream is(line);
	is>>nodeNo;

	while(!myfile.eof()){
		getline(myfile, line);
		int i,j,cost;
		istringstream is1(line);
		is1>>i>>j>>cost;

		graph[i][j] = cost;
	}
	myfile.close();

	visited[0] = 1;

	chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> elapsedSeconds;
    start = chrono::system_clock::now();
	cout<<"cost: "<<bruteForce(1, 0)<<endl;

	end = chrono::system_clock::now();
	elapsedSeconds = end - start;


	cout<<"time elapsed: "<<elapsedSeconds.count()<<"s"<<endl;
}