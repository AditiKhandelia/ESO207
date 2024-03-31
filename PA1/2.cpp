#include<iostream>
using namespace std;
//implementation of merge sort
void merge(long long arr[],int left,int n1,int n2)
{
    long long arr1[n1];
    long long arr2[n2];
    for (int i=0;i<n1+n2;i++) 
    {
        if(i<n1) arr1[i]=arr[left+i];
        else arr2[i-n1]=arr[left+i];
    }
    int i=0;
    int j=0;
    int k=left;
    while (i!=n1 && j!=n2) 
    {
        if (arr1[i] <= arr2[j]) 
        {
            arr[k]=arr1[i];
            i++;
            k++;
        } 
        else 
        {
            arr[k]=arr2[j];
            j++;
            k++;
        }
    }
    while(i<n1) 
    {
        arr[k]=arr1[i];
        i++;
        k++;
    }
    while(j<n2) 
    {
        arr[k]=arr2[j];
        j++;
        k++;
    }
}

void mergesort(long long a[], int left,int right)
{
    if(left==right) return;
    else
    {
        int mid=(left+right)/2;
        mergesort(a,left,mid);
        mergesort(a,mid+1,right);
        merge(a,left,mid-left+1,right-mid);
    }
}
//function to check if any height is allowed i.e. doesn't exceed the cost
int allowed(long long arr[],int num, long long k,long long mid)
{
    int i=num-1;
    long long curr_cost=0;
    while(curr_cost<=k && i>=0)
    {
        curr_cost+=((arr[i]*(arr[i]+1))/2 - (mid*(mid+1))/2);
        i--;
    }
    if(curr_cost>k) i++;
    if(i==-1 || arr[i]<=mid) return 1;
    else return 0;
}
//function definign and checking the range of heights allowed
//if a given height is allowed, check if a lower height is allowed to minimize max height
//otherwise check if a greater height is required
long long calculateheight(long long arr[],long long min,long long max,long long k,int num)
{
    if(min==max) return max;
    else
    {
        long long mid=(min+max)/2;
        if(allowed(arr,num,k,mid)) return calculateheight(arr,min,mid,k,num);
        else return calculateheight(arr,mid+1,max,k,num);
    }
}
int main()
{
    //input no of test cases
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {  
        //num is the number of buildings and k the maximum allowed cost
        int num;
        long long k;
        cin>>num;
        cin>>k;
        long long arr[num];
        for(int i=0;i<num;i++)
        {
            cin>>arr[i];
        }
        mergesort(arr,0,num-1);
        cout<<calculateheight(arr,0,arr[num-1],k,num)<<endl;
    }
}