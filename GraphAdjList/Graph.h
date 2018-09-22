#pragma once
#include <stack>
#include <memory>

struct AdjListNode
{
    int vertex;
    int weight;
    std::unique_ptr<AdjListNode> next;
};
 
struct AdjList
{
    std::unique_ptr<AdjListNode> first;
};

class Graph
{
public:
    Graph(bool directed, int numVertices);
    
    void AddEdge(int src, int dest, int weight = 0);
    void Print();

    // Breadt first search
    void Bfs(int vertex);

    // Depth first search
    void Dfs(int vertex);

    // Find any path
    void FindAnyPath(int startVertex, int endVertex);

    // Is Bi-Partite Using Dfs
    bool IsBiPartiteUsingDfs();

    // Topological Sort
    void TopologicalSort();

    // Prim's MST
    void PrimMst();

    // Dijkstra's MST
    void DijkstraMst();

private:
    bool m_directed;
    int m_V;
    std::unique_ptr<AdjList[]> m_adjlist;

    std::unique_ptr<AdjListNode> CreateNode(int vertex, int weight);

    // Depth first search util
    void DfsUtil(int vertex, bool* visited);

    // Find Path DFS util
    bool DfsUtil_FindAnyPath(int vertex, bool* visited, const int endVertex, std::stack<int>& path);

    // Is BiPartite DFS util
    bool DfsUtil_IsBiPartite(int vertex, int* colors);

    // Topological sort DFS util
    void DfsUtil_TopoogicalSort(int vertex, bool* visited, std::stack<int>& stack);
};
