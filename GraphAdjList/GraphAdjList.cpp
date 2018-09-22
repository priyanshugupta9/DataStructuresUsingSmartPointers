// GraphAdjList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <crtdbg.h>
#include <iostream>
using namespace std;

#include "Graph.h"
#include "HeapMap.h"

void GraphTest1()
{
    Graph g(false, 9);
    g.AddEdge(0, 1, 4);
    g.AddEdge(1, 2, 8);
    g.AddEdge(2, 3, 7);
    g.AddEdge(3, 4, 9);
    g.AddEdge(4, 5, 10);
    g.AddEdge(5, 6, 2);
    g.AddEdge(6, 7, 1);
    g.AddEdge(0, 7, 8);
    g.AddEdge(1, 7, 11);
    g.AddEdge(7, 8, 7);
    g.AddEdge(2, 8, 2);
    g.AddEdge(6, 8, 6);
    g.AddEdge(2, 5, 4);
    g.AddEdge(3, 5, 14);
    g.Print();
    g.Bfs(0);
    g.Dfs(0);
    g.FindAnyPath(0, 4);
    g.PrimMst();
    g.DijkstraMst();
}

void GraphTest2()
{
    Graph graph(false, 8);
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(2, 4);
    graph.AddEdge(3, 5);
    graph.AddEdge(5, 6);
    graph.AddEdge(4, 5);
    graph.AddEdge(4, 7);

    graph.IsBiPartiteUsingDfs() ? cout << "BiPartite!\n" : cout << "Not BiPartite.\n";
}

void GraphTest3()
{
    Graph graph(true, 8);
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(2, 4);
    graph.AddEdge(3, 5);
    graph.AddEdge(5, 6);
    graph.AddEdge(4, 5);
    graph.AddEdge(4, 7);

    graph.TopologicalSort();
}

void HeapMapTest()
{
    Data data;

    HeapMap heap;

    data.vertex = 0; data.weight = 23;
    heap.Insert(data);

    data.vertex = 1; data.weight = 43;
    heap.Insert(data);

    data.vertex = 2; data.weight = 26;
    heap.Insert(data);

    data.vertex = 3; data.weight = 10;
    heap.Insert(data);

    data.vertex = 4; data.weight = 21;
    heap.Insert(data);

    data.vertex = 5; data.weight = 13;
    heap.Insert(data);

    data.vertex = 6; data.weight = 31;
    heap.Insert(data);

    data.vertex = 7; data.weight = 16;
    heap.Insert(data);

    data.vertex = 8; data.weight = 12;
    heap.Insert(data);

    data.vertex = 9; data.weight = 8;
    heap.Insert(data);

    data.vertex = 10; data.weight = 29;
    heap.Insert(data);

    data.vertex = 11; data.weight = 11;
    heap.Insert(data);

    data.vertex = 12; data.weight = 19;
    heap.Insert(data);

    data.vertex = 13; data.weight = 17;
    heap.Insert(data);

    heap.Print("Heap: ");
    cout << "Minimum: " << heap.Minimum().weight << "\n\n";
    heap.Test();

    heap.DeleteMin();
    heap.Print("After DeleteMin: ");
    cout << "Minimum: " << heap.Minimum().weight << "\n\n";
    heap.Test();

    heap.DecreaseKey(2, 8);
    heap.Print("After decrease key: ");
    heap.Test();

    heap.DeleteMin();
    heap.DeleteMin();
    heap.DeleteMin();
    heap.DeleteMin();
    heap.DeleteMin();
    heap.DeleteMin();
    heap.DeleteMin();
    heap.DeleteMin();
    heap.DeleteMin();
    heap.DeleteMin();
    heap.DeleteMin();
    heap.DeleteMin();
    heap.Print("One Left:");
    heap.Test();
    
    heap.DeleteMin();
    heap.Print("Heap Empty");
    heap.Test();
    /*heap.HeapSort();
    heap.Print("Heap Sort: ");

    heap.BuildHeap();
    heap.Print("Build Heap: ");
    cout << "Minimum: " << heap.Minimum().weight << "\n\n";*/
}

int main()
{
    {
        GraphTest1();
        //GraphTest2();
        //HeapMapTest();
        //GraphTest3();
    }
    _CrtDumpMemoryLeaks();

    return 0;
}