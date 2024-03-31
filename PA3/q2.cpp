#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int queue[100000];
int front;
int rear;
int num;

void newqueue()
{
    num=0;
    front=0;
    rear=0;
}

void enqueue(int x)
{
    if(num==100000) return;
    queue[rear]=x;
    rear=(rear+1)%100000;
    num++;
}

int dequeue()
{
    int x=queue[front];
    front=(front+1)%100000;
    num--;
    return x;
}

void mark_cycle(int curr_vertex,int vertex, vector<int>& parent, vector<int>& cycle)
{
    while(curr_vertex!=vertex)
    {
        cycle[curr_vertex]=1;
        cycle[vertex]=1;
        curr_vertex=parent[curr_vertex];
        vertex=parent[vertex];
    }
    cycle[curr_vertex]=1;
}

void mark_cycle1(int curr_vertex,int vertex, vector<int>& parent, vector<int>& cycle)
{
    cycle[curr_vertex]=1;
    curr_vertex=parent[curr_vertex];
    while(curr_vertex!=vertex)
    {
        cycle[curr_vertex]=1;
        cycle[vertex]=1;
        curr_vertex=parent[curr_vertex];
        vertex=parent[vertex];
    }
    cycle[curr_vertex]=1;;
}

void find_cycles(vector<vector <int> >& edges,vector<int>& visited, vector<int>& cycle,vector<int>& parent,vector<int>& distance,int n, int m)
{
    for(int i=1;i<=n;i++)
    {
        if(!visited[i])
        {
            visited[i]=1;
            parent[i]=1;
            distance[i]=1;
            newqueue();
            enqueue(i);
            while(num!=0)
            {
                int vertex=dequeue();
                int neighbours=edges[vertex][0];
                for(int i=1;i<=neighbours;i++)
                {
                    int curr_vertex=edges[vertex][i];
                    if(!visited[curr_vertex])
                    {
                        distance[curr_vertex]=distance[vertex]+1;
                        visited[curr_vertex]=1;
                        parent[curr_vertex]=vertex;
                        enqueue(curr_vertex);
                    }
                    else if(visited[curr_vertex] && parent[vertex]!=curr_vertex)
                    {
                        if(distance[curr_vertex]==distance[vertex]) mark_cycle(curr_vertex,vertex,parent,cycle);
                        else if(distance[curr_vertex]==distance[vertex]+1) mark_cycle1(curr_vertex,vertex,parent,cycle);
                    }
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        cout<<cycle[i]<<" ";
    }
}

int main()
{
    int n;
    int m;
    cin>>n>>m;
    vector<int> arr1;
    vector<int> arr2;
    for(int i=0;i<m;i++)
    {
        int temp;
        cin>>temp;
        arr1.push_back(temp);
    }
    for(int i=0;i<m;i++)
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
    for(int i=0;i<m;i++)
    {
        edges[arr1[i]][0]++;
        edges[arr1[i]].push_back(arr2[i]);
        edges[arr2[i]][0]++;
        edges[arr2[i]].push_back(arr1[i]);
    }
    
    vector<int> visited;
    for(int i=0;i<=n;i++)
    {   
        visited.push_back(0);
    }

    vector<int> cycle;
    for(int i=0;i<=n;i++)
    {
        cycle.push_back(0);
    }

    vector<int> parent;
    for(int i=0;i<=n;i++)
    {
        parent.push_back(0);
    }

    vector<int> distance;
    for(int i=0;i<=n;i++)
    {
        distance.push_back(0);
    }

    find_cycles(edges,visited,cycle,parent,distance,n,m);
}
