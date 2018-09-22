#include "stdafx.h"
#include "Graph.h"
#include "HeapMap.h"

#include <queue>
#include <iostream>
using namespace std;

Graph::Graph(bool directed, int numVertices)
    : m_directed(directed)
    , m_V(numVertices)
    , m_adjlist(new AdjList[m_V]())
{
}

void Graph::AddEdge(int src, int dest, int weight)
{
    unique_ptr<AdjListNode> newNode = CreateNode(dest, weight);
    newNode->next = move(m_adjlist[src].first);
    m_adjlist[src].first = move(newNode);

    if (!m_directed)
    {
        unique_ptr<AdjListNode> newNode = CreateNode(src, weight);
        newNode->next = move(m_adjlist[dest].first);
        m_adjlist[dest].first = move(newNode);
    }
}

unique_ptr<AdjListNode> Graph::CreateNode(int vertex, int weight)
{
    unique_ptr<AdjListNode> adjListNode = make_unique<AdjListNode>();
    adjListNode->vertex = vertex;
    adjListNode->weight = weight;
    return adjListNode;
}

void Graph::Print()
{
    for (int i = 0; i < m_V; ++i)
    {
        cout << "[" << i << "]: ";
        AdjListNode* node = m_adjlist[i].first.get();
        while (node)
        {
            cout << node->vertex << "[" << node->weight << "]" << "\t";
            node = node->next.get();
        }
        cout << "\n";
    }
}

void Graph::Bfs(int vertex)
{
    cout << "BFS[" << vertex << "]: ";
    unique_ptr<bool[]> visited(new bool[m_V]());

    queue<int> queue;
    queue.push(vertex);
    visited[vertex] = true;

    while (!queue.empty())
    {
        int current = queue.front(); queue.pop();
        cout << current << "  ";

        AdjListNode* node = m_adjlist[current].first.get();
        while (node)
        {
            if (!visited[node->vertex])
            {
                queue.push(node->vertex);
                visited[node->vertex] = true;
            }
            node = node->next.get();
        }
    }
    cout << "\n";
}

void Graph::Dfs(int vertex)
{
    cout << "DFS[" << vertex << "]: ";
    unique_ptr<bool[]> visited(new bool[m_V]());
    DfsUtil(vertex, visited.get());
    cout << "\n";
}

void Graph::DfsUtil(int vertex, bool* visited)
{
    cout << vertex << "  ";
    visited[vertex] = true;

    AdjListNode* current = m_adjlist[vertex].first.get();
    while (current)
    {
        if (!visited[current->vertex])
            DfsUtil(current->vertex, visited);
        current = current->next.get();
    }
}

void Graph::FindAnyPath(int startVertex, int endVertex)
{
    unique_ptr<bool[]> visited(new bool[m_V]());
    stack<int> path;

    if (!DfsUtil_FindAnyPath(startVertex, visited.get(), endVertex, path))
    {
        cout << "Path not found!\n";
        return;
    }

    cout << "Path from end to start: ";
    while (!path.empty())
    {
        cout << path.top() << "  ";
        path.pop();
    }
    cout << "\n";
}

bool Graph::DfsUtil_FindAnyPath(int vertex, bool* visited, const int endVertex, std::stack<int>& path)
{
    path.push(vertex);
    visited[vertex] = true;

    if (vertex == endVertex)
        return true;

    AdjListNode* current = m_adjlist[vertex].first.get();
    while (current)
    {
        if (!visited[current->vertex])
            if (DfsUtil_FindAnyPath(current->vertex, visited, endVertex, path))
                return true;
        current = current->next.get();
    }
    return false;
}

bool Graph::IsBiPartiteUsingDfs()
{
    unique_ptr<int[]> colors(new int[m_V]());
    for (int i = 0; i < m_V; ++i)
        colors[i] = -1;
    colors[0] = 0;
    return DfsUtil_IsBiPartite(0, colors.get());
}

bool Graph::DfsUtil_IsBiPartite(int vertex, int* colors)
{ 
    AdjListNode* node = m_adjlist[vertex].first.get();
    while (node)
    {
        if (colors[node->vertex] == -1)
        {
            colors[node->vertex] = 1 - colors[vertex];
            if (!DfsUtil_IsBiPartite(node->vertex, colors))
                return false;
        }
        else if (colors[node->vertex] == colors[vertex])
        {
            return false;   
        }
        node = node->next.get();
    }

    return true;
}

void Graph::TopologicalSort()
{
    unique_ptr<bool[]> visited(new bool[m_V]());

    stack<int> stack;
    for (int i = 0; i < m_V; ++i)
    {
        if (!visited[i])
            DfsUtil_TopoogicalSort(i, visited.get(), stack);
    }

    cout << "Topological Sort: ";
    while (!stack.empty())
    {
        cout << stack.top() << "  ";
        stack.pop();
    }
    cout << "\n";
}

void Graph::DfsUtil_TopoogicalSort(int vertex, bool* visited, stack<int>& stack)
{
    visited[vertex] = true;

    AdjListNode* current = m_adjlist[vertex].first.get();
    while (current)
    {
        if (!visited[current->vertex])
            DfsUtil_TopoogicalSort(current->vertex, visited, stack);
        current = current->next.get();
    }

    stack.push(vertex);
}

void Graph::PrimMst()
{
    unique_ptr<int[]> weight(new int[m_V]());
    unique_ptr<int[]> parent(new int[m_V]());
    HeapMap hm;

    for (int i = 0; i < m_V; ++i)
    {
        weight[i] = INT32_MAX;
        parent[i] = -1;
        hm.Insert(i, weight[i]);
    }

    int startVertex = 0;
    weight[startVertex] = 0;
    hm.DecreaseKey(startVertex, weight[startVertex]);

    while (!hm.IsEmpty())
    {
        Data data = hm.Minimum(); hm.DeleteMin();

        AdjListNode* node = m_adjlist[data.vertex].first.get();
        while (node)
        {
            if (hm.Contains(node->vertex) && weight[node->vertex] > node->weight)
            {
                parent[node->vertex] = data.vertex;
                weight[node->vertex] = node->weight;
                hm.DecreaseKey(node->vertex, weight[node->vertex]);
            }
            node = node->next.get();
        }
    }

    cout << "Vertex:\t\tParent:\t\tWeight:\n";
    for (int i = 0; i < m_V; ++i)
    {
        cout << i << "\t\t" << parent[i] << "\t\t" << weight[i] << "\n";
    }
}

void Graph::DijkstraMst()
{
    unique_ptr<int[]> distance(new int[m_V]());
    unique_ptr<int[]> parent(new int[m_V]());
    HeapMap hm;

    for (int i = 0; i < m_V; ++i)
    {
        distance[i] = INT32_MAX;
        parent[i] = -1;
        hm.Insert(i, distance[i]);
    }

    int startVertex = 0;
    distance[startVertex] = 0;
    hm.DecreaseKey(startVertex, distance[startVertex]);

    while (!hm.IsEmpty())
    {
        Data data = hm.Minimum(); hm.DeleteMin();

        AdjListNode* node = m_adjlist[data.vertex].first.get();
        while (node)
        {
            if (hm.Contains(node->vertex) && distance[node->vertex] > node->weight + distance[data.vertex])
            {
                parent[node->vertex] = data.vertex;
                distance[node->vertex] = node->weight + distance[data.vertex];
                hm.DecreaseKey(node->vertex, distance[node->vertex]);
            }
            node = node->next.get();
        }
    }

    cout << "Vertex:\t\tParent:\t\tDistance:\n";
    for (int i = 0; i < m_V; ++i)
    {
        cout << i << "\t\t" << parent[i] << "\t\t" << distance[i] << "\n";
    }
}