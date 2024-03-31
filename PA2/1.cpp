#include<iostream>
#include<cstdlib>
#include<vector>

using namespace std;
//this function is used to merge two sorted arrays and count the number of inversions between them
long long merge(vector<long long>& arr, int low, int high)
{
    int i=low;
    int mid=(low+high)/2;
    int j=mid+1;
    vector<long long> arr2;
    long long count=0;
    while(i<=mid && j<=high)
    {
        if(arr[i]<=arr[j])
        {
            arr2.push_back(arr[i]);
            i++;
        }
        else if(arr[i]>arr[j])
        {
            arr2.push_back(arr[j]);
            j++;
            count=count+(mid-i)+1;
        }
    }
    while(i<=mid)
    {
        arr2.push_back(arr[i]);
        i++;
    }
    while(j<=high)
    {
        arr2.push_back(arr[j]);
        j++;
    }
    int k=0;
    int l=low;
    while(l<=high)
    {
        arr[l]=arr2[k];
        l++;
        k++;
    }
    return count;
}
//this function is used to merge and sort the array
long long countinversions(vector<long long>& arr, int low, int high)
{
    if(low==high) return 0;
    else
    {
        int mid=(low+high)/2;
        long long num1= countinversions(arr, low, mid);
        long long num2= countinversions(arr, mid+1, high);
        long long num3= merge(arr, low, high);
        return num1+num2+num3;
    }
}
//main program
int main()
{
    int num;
    cin>>num;
    for(int i=0;i<num;i++)
    {
        int n;
        cin>>n;
        vector<long long> arr;
        for(int j=0;j<n;j++)
        {
            long long temp;
            cin>>temp;
            arr.push_back(temp);
        }
        cout<<countinversions(arr,0, n-1)<<endl;
    }
}