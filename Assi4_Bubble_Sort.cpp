#include<iostream>
#include<bits/stdc++.h>

using namespace std;

void serial_bubble_sort(vector<int> arr)
{
    int n= arr.size();
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

    for(int i=0;i<arr.size();i++)
    {
        cout<<" "<<arr[i];
    }
}
void parallel_bubble_sort(vector<int>arr)
{
    int n= arr.size();
    bool swapped;
    for(int i=0;i<n-1;i++)
    {
        swapped = false;
        #pragma omp parallel for shared(arr,swapped)
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = true;
            }
        }

        if(!swapped)
        {
            break;
        }
    }

    for(int i=0;i<arr.size();i++)
    {
        cout<<" "<<arr[i];
    }

}

int main()
{
    ifstream obj("bubble_sort.txt");
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
    serial_bubble_sort(arr);
    end_t = clock();
    cout <<" Serial Bubble Sort Sorting with time "<<double(end_t-start_t)<<endl;
    
    start_t = clock();
    parallel_bubble_sort(arr);
    end_t = clock();
    cout <<" Parallel Bubble Sort Sorting with time "<<double(end_t-start_t)<<endl;

    return 0;
}