#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void DFS(vector<vector <int> >& edges,vector< vector <int> >& sparse_table,vector<int>& visited,vector<int>& depth,int vertex,int parentv)
{
    sparse_table[vertex][0]=parentv;
    visited[vertex]=1;
    depth[vertex]=depth[parentv]+1;
    int neighbours=edges[vertex][0];
    for(int i=1;i<=neighbours;i++)
    {
        int child=edges[vertex][i];
        if(!visited[child])
        {
            DFS(edges,sparse_table,visited,depth,child,vertex);
        }
    }
}

void DFSfinal(vector<vector <int> >& edges,vector<int>& breadcrumbs,vector<int>& visited,int vertex)
{
    visited[vertex]=1;
    int neighbours=edges[vertex][0];
    int initial=breadcrumbs[vertex];
    for(int i=1;i<=neighbours;i++)
    {
        int child=edges[vertex][i];
        if(!visited[child])
        {
            DFSfinal(edges,breadcrumbs,visited,child);
            breadcrumbs[vertex]+=breadcrumbs[child];
        }
    }
}

void make_sparse_table(vector<vector <int> >& edges,vector< vector <int> >& sparse_table,vector<int>& depth,int n)
{
    for(int i=1;i<20;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(sparse_table[j][i-1]!=-1)
            {
                sparse_table[j][i]=sparse_table[sparse_table[j][i-1]][i-1];
            }
        }
    }
}

int lowest_common_ancestor(int a, int b, vector< vector <int> >& sparse_table,vector<int>& depth)
{
    int u = (depth[a]>=depth[b])?a:b;
    int v = (depth[a]>=depth[b])?b:a;
    while(depth[u]!=depth[v])
    {
        int depthdiff=depth[u]-depth[v];
        int climb=floor(log2(depthdiff));
        u=sparse_table[u][climb];
    }
    if(u==v) return u;
    for(int top=19;top>=0;top--)
    {
        if(sparse_table[u][top]!=sparse_table[v][top])
        {
            u=sparse_table[u][top];
            v=sparse_table[v][top];
        }
    }

    return sparse_table[u][0];
}

int main()
{
    int n;
    int k;
    cin>>n>>k;
    vector<int> arr1;
    vector<int> arr2;
    for(int i=0;i<n-1;i++)
    {
        int temp;
        cin>>temp;
        arr1.push_back(temp);
    }
    for(int i=0;i<n-1;i++)
    {
        int temp;
        cin>>temp;
        arr2.push_back(temp);
    }
    //make adjacency list
    vector<vector <int> > edges;
    for(int i=0;i<=n;i++)
    {
        vector<int> temp;
        temp.push_back(0);
        edges.push_back(temp);
    }
    for(int i=0;i<n-1;i++)
    {
        edges[arr1[i]][0]++;
        edges[arr1[i]].push_back(arr2[i]);
        edges[arr2[i]][0]++;
        edges[arr2[i]].push_back(arr1[i]);
    }

    vector<int> visited;
    for(int i=0;i<n+1;i++)
    {
        visited.push_back(0);
    }

    vector<int> depth;
    for(int i=0;i<n+1;i++)
    {
        depth.push_back(0);
    }

    vector< vector <int> > sparse_table;
    for(int i=0;i<n+1;i++)
    {
        vector<int> temp;
        //because of constraints on n, max level <= 20
        for(int j=0;j<20;j++)
        {
            temp.push_back(-1);
        }
        sparse_table.push_back(temp);
    }
    depth[0]=0;
    visited[0]=1;
    DFS(edges,sparse_table,visited,depth,1,0);
    make_sparse_table(edges,sparse_table,depth,n);

    vector<int> breadcrumbs;
    for(int i=0;i<n+1;i++)
    {
        breadcrumbs.push_back(0);
    }

    vector<int> ancestorarray;
    for(int i=0;i<n+1;i++)
    {
        ancestorarray.push_back(0);
        visited[i]=0;
    }

    for(int i=0;i<k;i++)
    {
        int u,v;
        cin>>u>>v;
        int ancestor=lowest_common_ancestor(u,v,sparse_table,depth);
        breadcrumbs[u]++;
        breadcrumbs[v]++;
        breadcrumbs[ancestor]=breadcrumbs[ancestor]-2;
        ancestorarray[ancestor]++;
    }

    DFSfinal(edges,breadcrumbs,visited,1);

    for(int i=1;i<=n;i++)
    {
        cout<<ancestorarray[i]+breadcrumbs[i]<<" ";
    }
}