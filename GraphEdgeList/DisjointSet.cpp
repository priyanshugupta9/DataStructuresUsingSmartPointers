#include "stdafx.h"
#include "DisjointSet.h"

DisjointSet::DisjointSet(int numSets)
    : m_arr(new Set[numSets]())
{ }

void DisjointSet::MakeSet(int x)
{
    m_arr[x].parent = x;
    m_arr[x].rank = 0;
}

int DisjointSet::Find(int x)
{
    if (x != m_arr[x].parent)
        m_arr[x].parent = Find(m_arr[x].parent);

    return m_arr[x].parent;
}

void DisjointSet::Union(int x, int y)
{
    int xSet = Find(x);
    int ySet = Find(y);

    if (m_arr[xSet].rank > m_arr[ySet].rank)
        m_arr[ySet].parent = xSet;
    else if (m_arr[xSet].rank < m_arr[ySet].rank)
        m_arr[xSet].parent = ySet;
    else
    {
        m_arr[xSet].parent = ySet;
        ++m_arr[ySet].rank;
    }
}