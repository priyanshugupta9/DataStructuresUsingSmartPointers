#pragma once

#include <memory>

struct Edge
{
    int src;
    int dest;
    int wt;

    /*bool operator<(const Edge& rhs)
    {
        return wt < rhs.wt;
    }*/
};

class Graph
{
public:
    Graph(int numVertex, int numEdges);

    void AddEdge(int src, int des, int wt);
    void Print();
    void Sort();
    void KruskalMst();
    bool IsCycle_Undirected_DisjointSet();
    void BellmanfordSssp(int source);

private:
    int m_V;
    int m_E;
    std::unique_ptr<Edge[]> m_edgeList;
    int m_index = -1;
};