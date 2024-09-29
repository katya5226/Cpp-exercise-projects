#include<iostream>
#include<list> 
using namespace std;

class Graph
{
    int V;
    list<int>* adj;
    void DFSUtil(int v, bool visited[]);
public:
    Graph(int V);
    ~Graph();
    void addEdge(int v, int w);
    bool DFS(int v, int node);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

Graph::~Graph() {
    delete[] adj;
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

void Graph::DFSUtil(int v, bool visited[])
{
    visited[v] = true;

    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {
        if (!visited[*i])
            DFSUtil(*i, visited);
    }

}

bool Graph::DFS(int v, int node)
{

    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    DFSUtil(v, visited);
    if (visited[node] == true) return true;
    delete[] visited;
    return false;
}

//int main()
//{
//    Graph g(5);
//    g.addEdge(0, 1);
//    g.addEdge(0, 2);
//    g.addEdge(1, 2);
//    g.addEdge(2, 0);
//    g.addEdge(2, 3);
//    g.addEdge(3, 3);
//    g.addEdge(4, 4);
//
//    cout << g.DFS(2,3);
//
//    return 0;
//}