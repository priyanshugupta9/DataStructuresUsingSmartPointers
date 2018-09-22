#include "stdafx.h"
#include "Graph.h"
#include "DisjointSet.h"

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

Graph::Graph(int numVertex, int numEdges)
    : m_V(numVertex)
    , m_E(numEdges)
    , m_edgeList(new Edge[m_E]())
{ }

void Graph::AddEdge(int src, int dest, int wt)
{
    ++m_index;
    m_edgeList[m_index].src = src;
    m_edgeList[m_index].dest = dest;
    m_edgeList[m_index].wt = wt;
}

void Graph::Print()
{
    cout << "Edges:\n";
    for (int i = 0; i < m_E; ++i)
    {
        cout << m_edgeList[i].src << "  " << m_edgeList[i].dest << "  " << m_edgeList[i].wt << "\n";
    }
}

void Graph::Sort()
{
    //std::sort(m_edgeList.get(), m_edgeList.get() + m_E);
    std::sort(m_edgeList.get(), m_edgeList.get() + m_E, [](const Edge& e1, const Edge& e2) {return e1.wt < e2.wt; });
}

void Graph::KruskalMst()
{
    // Sort the edges in asending order of weight
    Sort();

    unique_ptr<IDisjointSet> djs = make_unique<DisjointSet>(m_V);
    for (int i = 0; i < m_V; ++i)
        djs->MakeSet(i);

    vector<Edge*> mst;
    for (int e = 0; e < m_E; ++e)
    {
        if (mst.size() == m_V - 1)
            break;

        if (djs->Find(m_edgeList[e].src) != djs->Find(m_edgeList[e].dest))
        {
            mst.push_back(&m_edgeList[e]);
            djs->Union(m_edgeList[e].src, m_edgeList[e].dest);
        }
    }

    for (Edge* e : mst)
    {
        cout << e->src << "  " << e->dest << "  " << e->wt << "\n";
    }
}

bool Graph::IsCycle_Undirected_DisjointSet()
{
    bool isCyclic = false;

    unique_ptr<IDisjointSet> djs = make_unique<DisjointSet>(m_V);
    for (int i = 0; i < m_V; ++i)
        djs->MakeSet(i);

    for (int e = 0; e < m_E; ++e)
    {
        if (djs->Find(m_edgeList[e].src) != djs->Find(m_edgeList[e].dest))
        {
            djs->Union(m_edgeList[e].src, m_edgeList[e].dest);
        }
        else
        {
            isCyclic = true;
        }
    }

    return isCyclic;
}

void Graph::BellmanfordSssp(int source)
{
    unique_ptr<int[]> parent(new int[m_V]());
    unique_ptr<int[]> distance(new int[m_V]());
    for (int i = 0; i < m_V; ++i)
    {
        parent[i] = -1;
        distance[i] = INT32_MAX;
    }

    // Source
    distance[source] = 0;
    
    for (int v = 0; v < m_V - 1; ++v)
    {
        for (int e = 0; e < m_E; ++e)
        {
            if (distance[m_edgeList[e].src] == INT32_MAX)
                continue;
            if (distance[m_edgeList[e].dest] > distance[m_edgeList[e].src] + m_edgeList[e].wt)
            {
                distance[m_edgeList[e].dest] = distance[m_edgeList[e].src] + m_edgeList[e].wt;
                parent[m_edgeList[e].dest] = m_edgeList[e].src;
            }
        }
    }

    bool negativeWeightCycle = false;
    for (int e = 0; e < m_E; ++e)
    {
        if (distance[m_edgeList[e].src] == INT32_MAX)
            continue;
        if (distance[m_edgeList[e].dest] > distance[m_edgeList[e].src] + m_edgeList[e].wt)
        {
            negativeWeightCycle = true;
        }
    }

    if (!negativeWeightCycle)
    {
        cout << "Vertex:\t\tParent:\t\tDistance:\n";
        for (int i = 0; i < m_V; ++i)
        {
            cout << i << "\t\t" << parent[i] << "\t\t" << distance[i] << "\n";
        }
    }
    else
    {
        cout << "Graph has a negative weight cycle!\n";
    }
}