#include<bits/stdc++.h>
using namespace std;

void serial_dfs(vector<vector<int>> arr, vector<int>visited, int start_ver)
{
    int start = start_ver;
    cout<< start <<" " ;
    visited[start] = 1;

    for(int i=0;i<arr.size();i++)
    {
        if(arr[start][i]==1 && visited[i]==0)
        {
            serial_dfs(arr ,  visited , i );
        }
    }
}
void parallel_dfs(vector<vector<int>> arr, vector<int>visited, int start_ver)
{
    int start = start_ver;
    cout<<" "<<start;
    visited[start]= 1;

    #pragma omp parallel for ordered
    for(int i=0;i<arr.size();i++)
    {
    
    #pragma omp ordered
        if(arr[start][i]==1 && visited[i]==0)
        {
            parallel_dfs(arr ,  visited , i);
        }
    }
}

int main()
{
    ifstream obj("dfs_input.txt");
    int n;
    obj >> n;
    vector<vector<int>> arr(n,vector<int>(n,0));

    int u, v;
    while(obj)
    {
        obj >> u >> v;
        arr[u][v] = 1;
        arr[v][u] = 1;
    }

    vector<int> visited(n,0);

   /*int start_ver;
    obj >> start_ver;*/
    int start_ver;
    cout<<"Enter the Starting Vertix:- ";
    cin>> start_ver;

    clock_t start_t,end_t;

    start_t = clock();
    serial_dfs(arr,visited,start_ver);
    end_t = clock();

    cout<< "Time for Serialized Dfs:- " << double(end_t- start_t) << "ms"<<endl;
    
    start_t = clock();
    parallel_dfs(arr,visited,start_ver);
    end_t = clock();

    cout<< "Time for Parallel Dfs:- " << double(end_t- start_t) << "ms"<<endl;

    return 0;
}
