#pragma once

#include <vector>
#include <unordered_map>

struct Data
{
    Data() = default;
    Data(int vertex, int weight);

    int vertex;
    int weight;

    bool operator<(const Data& rhs);
    bool operator>(const Data& rhs);
};

class HeapMap
{
public:
    void Insert(int vertex, int weight);
    void Insert(Data data);

    // Can be combined into one
    Data Minimum();
    void DeleteMin();

    bool Contains(int vertex);
    void DecreaseKey(int vertex, int newWeight);

    bool IsEmpty();
    
    // Not required for Prim's and Dijkstra's
    void HeapSort();
    void BuildHeap();

    void Print(const char* str);

    // Local testing
    void Test();

private:
    std::vector<Data> m_arr;
    int m_index = -1;
    std::unordered_map<int, int> m_vertexLocMap;

    int Parent(int loc);
    int Left(int loc);
    int Right(int loc);

    void Heapify(int loc);
};
