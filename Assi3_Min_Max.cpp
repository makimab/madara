#include <bits/stdc++.h>
using namespace std;

int serial_minimum(vector<int> arr)
{
    int min_value = INT_MAX;
    for(int i=0;i<arr.size();i++)
    {
        if(arr[i]<min_value)
        {
            min_value = arr[i];
        }
    }
    return min_value;

}

int parallel_minimum(vector<int> arr)
{
    int min_value = INT_MAX;
    #pragma omp parallel for reduction(min:min_value)
     for(int i=0;i<arr.size();i++)
    {
        if(arr[i]<min_value)
        {
            min_value = arr[i];
        }
    }
    return min_value;

}

int serial_maximum(vector<int> arr)
{
    int max_value = INT_MIN;
    for(int i=0;i<arr.size();i++)
    {
        if(arr[i]>max_value)
        {
            max_value = arr[i];
        }
    }
    return max_value;
}

int parallel_maximum(vector<int> arr)
{
    int max_value = INT_MIN;
    
    #pragma omp paralell for reduction(max:max_value);
    for(int i=0;i<arr.size();i++)
    {
        if(arr[i]>max_value)
        {
            max_value = arr[i];
        }
    }
    return max_value;
}

int parallel_sum(vector<int>arr)
{
    int sum=0;
    #pragma omp parallel for reduction(+:sum);
    for(int i=0;i<arr.size();i++)
    {
        sum = sum + arr[i];
    }
    return sum;
}

int parallel_avg(vector<int>arr)
{
    int sum=0;
    #pragma omp parallel for reduction(+:sum);
    for(int i=0;i<arr.size();i++)
    {
        sum = sum + arr[i];
    }
    return sum/arr.size();
}
int main()
{
    ifstream obj("min_max_input_file.txt");
    int n;
    obj >> n ;

    vector<int> arr;
    int var;
        for(int i=0;i<n;i++)
        {   
            obj >> var;
            arr.push_back(var);
        }

    clock_t start_t, end_t;

    start_t = clock();
    int parallel_mini_value = parallel_minimum(arr);
    end_t = clock();
    cout <<" Parallel Minimum Value "<<parallel_mini_value<<" with time "<<double(end_t-start_t)<<endl;

    start_t = clock();
    int serial_mini_value = serial_minimum(arr);
    end_t = clock();
    cout <<" Serial Minimum Value "<< serial_mini_value<<" with time "<<double(end_t -start_t);

    start_t = clock();
    int parallel_max_value = parallel_maximum(arr);
    end_t = clock();
    cout <<" Parallel Maximum Value "<<parallel_max_value<<" with time "<<double(end_t-start_t)<<endl;

    start_t = clock();
    int serial_max_value = serial_maximum(arr);
    end_t = clock();
    cout <<" Serial Maximum Value "<<serial_max_value<<" with time "<<double(end_t-start_t)<<endl;


    start_t = clock();
    int sumation = parallel_sum(arr);
    end_t = clock();
    cout <<" Parallel additon "<<sumation <<" with time "<<double(end_t-start_t)<<endl;

    start_t = clock();
    int average = parallel_avg(arr);
    end_t = clock();
    cout <<" Parallel Average "<<average <<" with time "<<double(end_t-start_t)<<endl;

    return 0;
}