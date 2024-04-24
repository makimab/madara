#include<iostream>
#include<bits/stdc++.h>
using namespace std;

queue<int > q;

void serial_bfs(vector<vector<int>> arr, vector<int> visited, int start_ver)
{
    int start = start_ver;
    visited[start]= 1;
    q.push(start);

    while(!q.empty())
    {
        int check = q.front();
        cout<<" "<<check;
        q.pop();
        for(int i=0;i<arr.size();i++)
        {
            if(arr[check][i]==1 && visited[i]==0)
            {
                q.push(i);
                visited[i]=1;
            }
        }

    }
}

void parallel_bfs(vector<vector<int>> arr, vector<int> visited, int start_ver)
{
    int start = start_ver;
    visited[start]= 1;
    q.push(start);

    while(!q.empty())
    {
        int check = q.front();
        q.pop();
        cout<<" "<<check;

    #pragma omp parallel for ordered
        for(int i=0;i<arr.size();i++)
        {
    #pragma omp ordered
            if(arr[check][i]==1  && visited[i]==0)
            {
                q.push(i);
                visited[i]=1;
            }
        }
    }


}

int main()
{
    ifstream obj("bfs_input.txt");
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
    serial_bfs(arr,visited,start_ver);
    end_t = clock();

    cout<< "Time for Serialized Bfs:- " << double(end_t- start_t) << "ms"<<endl;
    
    start_t = clock();
    parallel_bfs(arr,visited,start_ver);
    end_t = clock();

    cout<< "Time for Parallel Bfs:- " << double(end_t- start_t) << "ms"<<endl;

    return 0;
}