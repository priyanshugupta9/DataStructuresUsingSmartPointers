#include "stdafx.h"
#include "HeapMap.h"

#include <crtdbg.h>
#include <iostream>
using namespace std;

Data::Data(int vertex, int weight)
    : vertex(vertex)
    , weight(weight)
{}

bool Data::operator<(const Data& rhs)
{
    return weight < rhs.weight;
}

bool Data::operator>(const Data& rhs)
{
    return weight > rhs.weight;
}

template<typename T>
void MySwap(T& x, T& y)
{
    T temp = x;
    x = y;
    y = temp;
}

void HeapMap::Insert(int vertex, int weight)
{
    Insert(Data(vertex, weight));
}

void HeapMap::Insert(Data data)
{
    m_arr.emplace_back(data);
    ++m_index;
    m_vertexLocMap.insert(make_pair(data.vertex, m_index));

    int loc = m_index;
    int parent = Parent(loc);
    while (parent >= 0 && m_arr[parent] > m_arr[loc])
    {
        MySwap(m_arr[parent], m_arr[loc]);
        m_vertexLocMap[m_arr[parent].vertex] = parent;
        m_vertexLocMap[m_arr[loc].vertex] = loc;

        loc = parent;
        parent = Parent(loc);
    }
}

void HeapMap::Print(const char* str)
{
    cout << str << "\n";
    /*for (auto i : m_arr)
    {
        cout << i.vertex << "\t" << i.weight << "\n";
    }*/
    for (size_t i = 0; i < m_arr.size(); ++i)
    {
        cout << i << "\t" <<  m_arr[i].vertex << "\t" << m_arr[i].weight << "\n";
    }
    cout << "\n";
}

Data HeapMap::Minimum()
{
    Data min;
    if (m_index > -1)
        min = m_arr[0];
    else
        cout << "Error: Empty heap!\n";
    return min;
}

void HeapMap::DeleteMin()
{
    if (m_index > -1)
    {
        Data temp = m_arr[m_index--];
        int erased = m_vertexLocMap.erase(m_arr.front().vertex);
        _ASSERT(erased == 1);
        m_arr.pop_back();

        _ASSERT(m_arr.size() == m_vertexLocMap.size());
        if (m_arr.size() != 0 && m_vertexLocMap.size() != 0)
        {
            m_arr[0] = temp;
            m_vertexLocMap[m_arr[0].vertex] = 0;

            Heapify(0);
        }
    }
    else
        cout << "Error: Empty heap!\n";
}

bool HeapMap::Contains(int vertex)
{
    if (m_vertexLocMap.find(vertex) != m_vertexLocMap.end())
        return true;
    return false;
}

void HeapMap::DecreaseKey(int vertex, int newWeight)
{
    int loc = m_vertexLocMap[vertex];
    m_arr[loc].weight = newWeight;

    int parent = Parent(loc);
    while (parent >= 0 && m_arr[parent] > m_arr[loc])
    {
        MySwap(m_arr[parent], m_arr[loc]);
        m_vertexLocMap[m_arr[parent].vertex] = parent;
        m_vertexLocMap[m_arr[loc].vertex] = loc;

        loc = parent;
        parent = Parent(loc);
    }
}

bool HeapMap::IsEmpty()
{
    _ASSERT(m_arr.size() == m_vertexLocMap.size());
    return (m_arr.size() == 0);
}

void HeapMap::HeapSort()
{
    if (m_index > -1)
    {
        while (m_index > 0)
        {
            MySwap(m_arr[0], m_arr[m_index]);
            m_vertexLocMap[m_arr[0].vertex] = 0;
            m_vertexLocMap[m_arr[m_index].vertex] = m_index;
            
            --m_index;

            Heapify(0);
        }

        m_index = m_arr.size() - 1;
    }
    else
        cout << "Error: Empty heap!\n";
}

void HeapMap::BuildHeap()
{
    for (int i = m_index / 2; i >= 0; --i)
    {
        Heapify(i);
    }
}

void HeapMap::Heapify(int loc)
{
    int minLoc = loc;
    int left = Left(loc);
    int right = Right(loc);

    if (left <= m_index && m_arr[left] < m_arr[minLoc])
        minLoc = left;

    if (right <= m_index && m_arr[right] < m_arr[minLoc])
        minLoc = right;

    if (minLoc != loc)
    {
        MySwap(m_arr[loc], m_arr[minLoc]);
        m_vertexLocMap[m_arr[loc].vertex] = loc;
        m_vertexLocMap[m_arr[minLoc].vertex] = minLoc;

        Heapify(minLoc);
    }
}

int HeapMap::Parent(int loc)
{
    return (loc - 1) >> 1;
}

int HeapMap::Left(int loc)
{
    return (loc << 1) + 1;
}

int HeapMap::Right(int loc)
{
    return (loc << 1) + 2;
}

void HeapMap::Test()
{
    /*int loc = 1;
    cout << "Parent(" << loc << "): " << Parent(loc) << "\n";
    cout << "Left(" << loc << "): " << Left(loc) << "\n";
    cout << "Right(" << loc << "): " << Right(loc) << "\n";*/

    cout << "Size: " << m_vertexLocMap.size() << "\n";
    for (auto vertexLoc : m_vertexLocMap)
    {
        cout << vertexLoc.second << "->" << vertexLoc.first << "\n";
    }
}