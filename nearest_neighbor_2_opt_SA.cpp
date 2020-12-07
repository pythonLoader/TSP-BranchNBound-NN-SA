#include<bits/stdc++.h>
#include <algorithm>
using namespace std;

int num_nodes;
int edge_weight[1000][1000];
typedef vector<int> candidate;

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
  		// printf("%d-%d: %d, %d\n",start_node,next_node,edge_weight[start_node][next_node],total_path_weight);
  		start_node=next_node;

  		//path.pop();
  	}
  	total_path_weight+=edge_weight[start_node][init_start_node];
  	// printf("%d-%d: %d, %d\n",start_node,init_start_node,edge_weight[start_node][init_start_node],total_path_weight);
  	//cout<<last_node<<endl;
  	//printf("Total Path Cost= %d\n",total_path_weight);
  	return total_path_weight;
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


void printPath(vector<int> path)
{
    for(int i=0; i<path.size(); i++)
    {
        cout<<path[i]<<"->";
    }
    cout<<path[0]<<endl;
}

candidate nn_2_opt(int option,int &cst){

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
    // cout << final_cost << endl;

    
    if(option == 1){
      //Compute greedy only
      cst = final_cost;
      return path;
    }
    else if(option == 2){
      //Compute 2-opt over greedy

      vector<int> final_path = twoOpt(path, final_cost);
      final_cost = calc_cost(final_path);
      // printPath(final_path);
      cst = final_cost;
      // cout<<"Total Final Cost: " << final_cost << endl;
      return final_path;
    }
    
    
}

class SimulatedAnnealing {
public:
    candidate best,current;
    double minTour_Cost,current_Cost,candidate_cost;
    double Temp = sqrt(num_nodes);
    double Stopping_Temp = 0.01;
    double maxIter = 5000;
    double expP,p,deltaE;

    SimulatedAnnealing() {
      minTour_Cost = 0.0;
    } 
    candidate generate_Rand_tour(candidate C){
        int l,a,b,temp;
        l = C.size();
        a = rand()%l;
        b = rand()%l;
        temp = C[a];
        C[a] = C[b];
        C[b] = temp;
        return C;
    }
    double randProb()
    {
        double p = (rand() / (RAND_MAX + 1.0));
        return p;
    }
    bool accept(candidate C, double T){
      this->candidate_cost = calc_cost(C);
      deltaE = candidate_cost - this->current_Cost;
      if(deltaE < 0.0){
        // printf("From here %d, %d\n",candidate_cost,current_Cost);
        return true;
      }
      else{
        deltaE /= T;
        expP = randProb();
        p = exp(-1*abs(deltaE));
        if(expP < p){
          return true;
        }
        else{
          return false;
        }
      }

    }
    void SA_sim(int &cst){
      
      // int cst= -1;
      this->current = nn_2_opt(2,cst);
      this->best = this->current;
      this->minTour_Cost = calc_cost(current);
      this->current_Cost = this->minTour_Cost;
      
      // double p,expP,deltaE;
      bool decision;
      double T= this->Temp;
      int iter = 0;
      for(T = Temp,iter=0; Temp > Stopping_Temp && iter < maxIter; T*=0.5,iter++){
        // cout << T << endl;
        for(int j = 0; j < 10; j++){
            candidate C = generate_Rand_tour(current);
            decision = accept(C,T);
            if(decision){
              // cout << "here" << " ";
              
              this->current = C;

              this->current_Cost = this->candidate_cost;
              // printf("%d, %d",candidate_cost,minTour_Cost);
              if(candidate_cost <= minTour_Cost){
                // cout << "here" << " ";
                this->best = C;
                this->minTour_Cost = this->candidate_cost;
              }
            }
            
        }
      }
      // cout << minTour_Cost << endl;
      // printPath(best);
      cst = minTour_Cost;


    }

};

int main()
{
    //setting all the edge weights to -1
    memset(edge_weight, -1, sizeof(edge_weight));
    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> elapsedSeconds;
    //take input from file
    string data_[] = {"data3","data10","data11","data12","data13","data14","data15",
            "data16","data17","data18","burma14","berlin52","eil76","ch130","a280",
            "d657"};
    // string data_[] = {"d1655","d2103"};

    ofstream out_file;
    out_file.open("Comparisons_of_Algorithm.txt");
    out_file << "Comparison of TSP Nearest-Neighbor, 2-opt First and SimulatedAnnealing" << endl;
    out_file <<endl;
    out_file << endl;
    int len = sizeof(data_)/sizeof(data_[0]);
    for(int k = 0; k < len; k++){
      cout << "Working on->" << data_[k] << endl;
      string inp_file = "Data_For_TSP/"+data_[k]+"_vertical.txt";
      out_file <<"Working with the dataset => " << data_[k] << endl;
      // string inp_file = "data.txt";
      ifstream myfile(inp_file);
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

        edge_weight[i][j] = cost;
      }
      myfile.close();
      
      int cst= -1;
      
      start = chrono::system_clock::now();

      nn_2_opt(1,cst);
      cout << "NN COST->" << cst << endl;
      end = chrono::system_clock::now();
      elapsedSeconds = end - start;

      // cout << "time in seconds->" << elapsedSeconds.count() << "s" <<endl;
      out_file << "Nearest-Neighbor: Final_Cost= " << cst << ",Time required= " << elapsedSeconds.count() << "s" <<endl;

      start = chrono::system_clock::now();

      nn_2_opt(2,cst);
      cout << "NN 2-opt COST->" << cst << endl;
      end = chrono::system_clock::now();
      elapsedSeconds = end - start;

      // cout << "time in seconds->" << elapsedSeconds.count() << "s" <<endl;
      out_file << "Nearest-Neighbor with 2-opt: Final_Cost= " << cst << ",Time required= " << elapsedSeconds.count() << "s" <<endl;
      

      start = chrono::system_clock::now();
      SimulatedAnnealing SA;
      SA.SA_sim(cst);
      end = chrono::system_clock::now();
      elapsedSeconds = end - start;

      // cout << "time in seconds->" << elapsedSeconds.count() << "s" <<endl;
      out_file << "SimulatedAnnealing: Final_Cost= " << cst << ",Time required= " << elapsedSeconds.count() << "s" <<endl;
      
      out_file <<endl;
      out_file <<endl;


    }
    
    // nn_2_opt(1);

    

   
}

