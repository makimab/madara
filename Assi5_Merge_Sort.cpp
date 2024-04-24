#include<bits/stdc++.h>
using namespace std;

void serial_merge(vector<int> &arr, int low, int mid, int high)
{
    vector<int> temp ;
    int left = low;
    int right = mid+1;
    while(left<=mid && right<=high)
    {
        if(arr[left]<=arr[right])
        {
            temp.push_back(arr[left]);
            left++;
        }
        else
        {
            temp.push_back(arr[right]);
            right++;
        }
    }

    while(left<=mid) //left arr madhe elements baki
    {
        temp.push_back(arr[left]);
        left++;
    }

    while(right<=high)
    {
        temp.push_back(arr[right]);
        right++;
    }

    for(int i= low;i<=high;i++)
    {
        arr[i]= temp[i-low];
    }
}

void serial_merge_sort(vector<int> &arr, int low , int high)
{
    if(low>=high) 
    {
       
        return ;
    } 
    int mid = (low+high)/2;
    serial_merge_sort(arr,low,mid);
    serial_merge_sort(arr,mid+1,high);
    serial_merge(arr,low,mid,high);
    
}
void parallel_merge(vector<int> &arr, int low, int mid, int high)
{
    vector<int> temp ;
    int left = low;
    int right = mid+1;
    while(left<=mid && right<=high)
    {
        if(arr[left]<=arr[right])
        {
            temp.push_back(arr[left]);
            left++;
        }
        else
        {
            temp.push_back(arr[right]);
            right++;
        }
    }

    while(left<=mid) //left arr madhe elements baki
    {
        temp.push_back(arr[left]);
        left++;
    }

    while(right<=high)
    {
        temp.push_back(arr[right]);
        right++;
    }

    for(int i= low;i<=high;i++)
    {
        arr[i]= temp[i-low];
    }

}
void parallel_merge_sort(vector<int> &arr, int low, int high)
{
    if(low>=high) 
    {
        return ;
    } 
    int mid = (low+high)/2;
    #pragma omp parallel sections
    {
        #pragma omp section
        parallel_merge_sort(arr,low,mid);

        #pragma omp section
        parallel_merge_sort(arr,mid+1,high);

    }
    
    parallel_merge(arr,low,mid,high);
}

int main()
{
    ifstream obj("merge_sort.txt");
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
    serial_merge_sort(arr,0,n-1);
    end_t = clock();
    cout <<" Serial Merge Sort Sorting with time "<<double(end_t-start_t)<<endl;
    
    start_t = clock();
    parallel_merge_sort(arr,0,n-1);
    end_t = clock();
    cout <<" Parallel Merge Sort Sorting with time "<<double(end_t-start_t)<<endl;

    cout << "After Sorting Array: " << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
    

}