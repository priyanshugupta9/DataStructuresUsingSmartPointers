#pragma once

#include "IDisjointSet.h"
#include <memory>

struct Set
{
    int rank;
    int parent;
};

class DisjointSet : public IDisjointSet
{
public:
    DisjointSet(int numSets);

    virtual void MakeSet(int x) override;

    virtual int Find(int x) override;

    virtual void Union(int x, int y) override;

private:
    std::unique_ptr<Set[]> m_arr;
};