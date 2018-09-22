#pragma once

#include <memory>
#include "IDisjointSet.h"

class DisjointSetArr : public IDisjointSet
{
public:
    DisjointSetArr(int numSets);

    virtual void MakeSet(int x) override;

    virtual int Find(int x) override;

    virtual void Union(int x, int y) override;

private:
    std::unique_ptr<int[]> m_arr;
};
