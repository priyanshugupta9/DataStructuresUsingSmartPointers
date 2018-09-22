#include "stdafx.h"
#include "DisjointSetUsingArray.h"

DisjointSetArr::DisjointSetArr(int numSets)
    : m_arr(new int[numSets]())
{ }

void DisjointSetArr::MakeSet(int x)
{
    m_arr[x] = x;
}

int DisjointSetArr::Find(int x)
{
    if (m_arr[x] == x)
        return x;
    
    return Find(m_arr[x]);
}

void DisjointSetArr::Union(int x, int y)
{
    int xSet = Find(x);
    int ySet = Find(y);

    m_arr[xSet] = ySet;
}