#include<iostream>
#include<vector>

using namespace std;

void maxtreeheight(vector<int>& arr, vector<int>& arr2, int left , int right, int height)
{
    if(left==right)
    {
        arr2[left]=height;
    }
    else
    {
        int max=arr[left];
        int maxindex=left;
        for(int i=left;i<=right;i++)
        {
            if(arr[i]>max)
            {
                max=arr[i];
                maxindex=i;
            }
        }
        if(maxindex>left && maxindex<right)
        {
            maxtreeheight(arr, arr2, left, maxindex-1, height+1);
            arr2[maxindex]=height;
            maxtreeheight(arr, arr2, maxindex+1, right, height+1);
        }
        else if(maxindex==left)
        {
            arr2[left]=height;
            maxtreeheight(arr, arr2, maxindex+1, right, height+1);
        }
        else if(maxindex==right)
        {
            arr2[right]=height;
            maxtreeheight(arr, arr2, left, maxindex-1, height+1);
        }
    }
}

int main()
{
    int num;
    cin>>num;
    for(int i=0;i<num;i++)
    {
        int n;
        cin>>n;
        vector<int> arr;
        for(int j=0;j<n;j++)
        {
            int temp;
            cin>>temp;
            arr.push_back(temp);
        }
        vector<int> arr2;
        for(int j=0;j<n;j++) arr2.push_back(0);
        maxtreeheight(arr, arr2, 0, n-1, 0);
        for(int j=0;j<n;j++)
        {
            cout<<arr2[j]<<" ";
        }
    }
}