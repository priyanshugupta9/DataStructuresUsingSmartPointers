// GraphEdgeList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <crtdbg.h>
#include <iostream>
#include <algorithm>
using namespace std;

#include "Graph.h"
#include "DisjointSet.h"
#include "DisjointSetUsingArray.h"

void GraphTest()
{
    Graph g(9, 14);
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

    //g.Print();

    //g.Sort();
    //g.Print();
    g.KruskalMst();
}

void GraphTest2()
{
    Graph g(6, 5);
    //g.AddEdge(0, 1, 5);
    g.AddEdge(1, 2, 6);
    g.AddEdge(2, 3, 4);
    g.AddEdge(3, 4, 9);
    g.AddEdge(1, 4, 3);
    g.AddEdge(0, 5, 7);
    g.IsCycle_Undirected_DisjointSet() ? cout << "Cyclic\n" : cout << "Acyclic\n";
}

void PrintDisjointSet(shared_ptr<IDisjointSet> iDisjointSet, int numSets)
{
    cout << "PrintDisjointSet: ";
    for (int i = 0; i < numSets; ++i)
        cout << iDisjointSet->Find(i) << "  ";
    cout << "\n";
}

void DisJointSetTest()
{
    int numSets = 7;
    shared_ptr<IDisjointSet> djs = make_shared<DisjointSet>(numSets);
    for (int i = 0; i < numSets; ++i)
        djs->MakeSet(i);

    PrintDisjointSet(djs, numSets);

    djs->Union(0, 1);
    PrintDisjointSet(djs, numSets);

    djs->Union(1, 2);
    PrintDisjointSet(djs, numSets);

    djs->Union(3, 4);
    PrintDisjointSet(djs, numSets);

    djs->Union(5, 6);
    PrintDisjointSet(djs, numSets);

    djs->Union(4, 5);
    PrintDisjointSet(djs, numSets);

    djs->Union(2, 6);
    PrintDisjointSet(djs, numSets);
}

void GraphTest3()
{
    Graph g(5, 7);
    g.AddEdge(3, 4, 2);
    g.AddEdge(4, 3, 1);
    g.AddEdge(2, 4, 4);
    g.AddEdge(0, 2, 5);
    g.AddEdge(1, 2, -3);
    g.AddEdge(0, 3, 8);
    g.AddEdge(0, 1, 4);
    g.BellmanfordSssp(0);

    Graph g2(4, 4);
    g2.AddEdge(0, 1, 1);
    g2.AddEdge(1, 2, 3);
    g2.AddEdge(2, 3, 2);
    g2.AddEdge(3, 1, -6);
    g2.BellmanfordSssp(0);
}

int main()
{
    {
        DisJointSetTest();
        GraphTest();
        GraphTest2();
        GraphTest3();
    }

    _CrtDumpMemoryLeaks();
    return 0;
}
