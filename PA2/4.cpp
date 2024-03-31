#include<iostream>
#include<vector>
#include<cstdlib>

using namespace std;

int allowed(vector< vector <int> >& segments, int s, vector<int>& arr, int n, int k)
{
    int presum[n];
    for(int j=n-1;j>=0;j--)
    {
        if(j==(n-1)) presum[j]=arr[j];
        else
        {
            presum[j]=presum[j+1]+arr[j];
        }
    }
    int currpositive=0;
    for(int j=0;j<s && currpositive<k;j++)
    {
        int left=segments[j][0]-1;
        int right=segments[j][1];
        int sum;
        if(right<=n-1) sum=presum[left]-presum[right];
        else sum=presum[left];
        if(sum>0) currpositive++;
    }
    if(currpositive>=k) return 1;
    else return 0;
}

int findminqueries(vector<int>& arr, int n, vector<int>& queries, int q, vector< vector <int> >& segments, int s, int k)
{
    int low=0;
    int high=q;
    while(low<high)
    {
        vector<int> arr1=arr;
        int mid=(low+high)/2;
        for(int j=0;j<mid;j++)
        {
            arr1[queries[j]-1]=1;
        }
        if(allowed(segments,s,arr1,n,k)) 
        {
            high=mid;
        }
        else 
        {
            low=mid+1;
        }
    }
    if(low>high) return -1;
    else
    {
        vector<int> arr1=arr;
        for(int j=0;j<low;j++)
        {
            arr1[queries[j]-1]=1;
        }
        if(allowed(segments,s,arr1,n,k)) return low;
        else return -1;
    } 
}

int main()
{
    int num;
    cin>>num;
    for(int i=0;i<num;i++)
    {
        int n, s;
        cin>>n>>s;
        vector<int> arr;
        for(int j=0;j<n;j++)
        {
            int temp;
            cin>>temp;
            arr.push_back(temp);
        }
        vector<vector <int> > segments;
        for(int j=0;j<s;j++)
        {
            int l;
            int r;
            cin>>l>>r;
            vector<int> temp;
            temp.push_back(l);
            temp.push_back(r);
            segments.push_back(temp);
        }
        int q,k;
        cin>>q>>k;
        vector<int> que;
        for(int j=0;j<q;j++)
        {
            int temp;
            cin>>temp;
            que.push_back(temp);
        }
        cout<<findminqueries(arr,n,que,q,segments,s,k)<<endl;
    }
}