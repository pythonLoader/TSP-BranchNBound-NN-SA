#include<bits/stdc++.h>
using namespace std;

// const int num_nodes=5;
// int edge_weight[num_nodes][num_nodes] = {
// 		{-1,1,4,10,5},
// 		{1,-1,2,3,6},
// 		{4,2,-1,8,7},
// 		{10,3,8,-1,9},
// 		{5,8,7,9,-1}
// 	};
int num_nodes;
int edge_weight[4000][4000];

vector<int> path_swap(vector<int> path, int u, int v)
{
    vector<int> new_path = path;
    new_path[u] = path[v];
    new_path[v] = path[u];

    return new_path;
}

int calc_cost(vector<int> path)
{
    int start_node=path[0];
    int init_start_node = start_node;
  	//path.pop();
  	int total_path_weight=0;
  	int next_node;
  	for(int i=0;i<num_nodes-1;i++)
  	{
  		next_node=path[i+1];
  		total_path_weight+=edge_weight[start_node][next_node];
  		//cout  << start_node<<" ";
  		//printf("%d-%d: %d, %d\n",start_node,next_node,edge_weight[start_node][next_node],total_path_weight);
  		start_node=next_node;

  		//path.pop();
  	}
  	total_path_weight+=edge_weight[start_node][init_start_node];
  	//printf("%d-%d: %d, %d\n",start_node,init_start_node,edge_weight[start_node][init_start_node],total_path_weight);
  	//cout<<"-----"<<endl;
  	//cout<<last_node<<endl;
  	//printf("Total Path Cost= %d\n",total_path_weight);
  	return total_path_weight;
}

void printPath(vector<int> path)
{
    for(int i=0; i<path.size(); i++)
    {
        cout<<path[i]<<"->";
    }
    cout<<path[0]<<endl;
}

vector<int> twoOpt(vector<int> path, int cost)
{
    //vector<int> final_path = path;
    //printPath(path);
    //cout<<cost<<endl;
    bool isCalled = false;
    for(int i=0; i<num_nodes-2; i++)
    {
        for(int j=i+2; j<num_nodes; j++)
        {
            vector<int> new_path = path_swap(path, i, j);
            int new_cost = calc_cost(new_path);

            if(new_cost<cost)
            {
                //cout<<cost<<"->"<<new_cost<<endl;
                path = twoOpt(new_path, new_cost);
                isCalled = true;
                break;
            }
        }
        if(isCalled) break;
    }
    return path;
}

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();
    //setting all the edge weights to -1
    memset(edge_weight, -1, sizeof(edge_weight));

    //take input from file
    ifstream myfile("d1655_vertical.txt");
    string line;
    int nodeNo;

    getline(myfile, line);
    istringstream is(line);
    is>>num_nodes;

    while(!myfile.eof()){
      getline(myfile, line);
      int i,j,cost;
      istringstream is1(line);
      is1>>i>>j>>cost;

      //edge_weight[i][j] = cost;
      edge_weight[i-1][j-1] = cost;
      edge_weight[j-1][i-1] = cost;
    }
    myfile.close();


  	int start_node=0;
  	int init_start_node = start_node;
  	int used_nodes[num_nodes];
  	for(int i=0;i<num_nodes;i++)
  	{
  		used_nodes[i]=0;
  	}
  	used_nodes[start_node]=1;
  	vector<int> path;
  	path.push_back(start_node);
  	while(path.size()!=num_nodes)
  	{
  		int min_weight=9999;
  		int temp_start_node=-1;
  		for(int i=0;i<num_nodes;i++)
  		{
  			if(used_nodes[i]!=1)
  			{
  				if(edge_weight[start_node][i]<min_weight && edge_weight[start_node][i]>0)
  				{
  					min_weight=edge_weight[start_node][i];
  					temp_start_node=i;
  				}
  			}
  		}
  		used_nodes[temp_start_node]=1;
  		start_node=temp_start_node;
  		path.push_back(start_node);

  	}
  	//path.push(init_start_node);

  	int final_cost = calc_cost(path);
  	cout << final_cost << endl;

  	vector<int> final_path = twoOpt(path, final_cost);
    final_cost = calc_cost(final_path);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;
    cout<<"Final Path: ";
    printPath(final_path);
    cout<<"Total Final Cost: " << final_cost << endl;
    cout<<"Time in milliseconds: " << time/std::chrono::milliseconds(1) <<endl;
}

