#include<iostream>
using namespace std;

int main()
{
    //number of test cases
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        //number of elements in the array
        int num;
        cin>>num;
        long long arr[num];
        //input the array
        for(int j=0;j<num;j++) cin>>arr[j];
        for(int j=num-1;j>=0;j--)
        {
            if(j==num-1) 
            {
                ;
            }
            else
            {
                if(arr[j+1]>0) arr[j]=arr[j]+arr[j+1];
            }
        }
        //the ith index contains the sum of the max subarray beginning at index i
        for(int k=0;k<num;k++) cout<<arr[k]<<" ";
        cout<<endl;
    }
}