#pragma once

class IDisjointSet
{
public:
    virtual void MakeSet(int x) = 0;

    virtual int Find(int x) = 0;

    virtual void Union(int x, int y) = 0;

    virtual ~IDisjointSet() = default;
};