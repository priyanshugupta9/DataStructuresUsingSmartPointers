// LinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <crtdbg.h>
#include <iostream>
using namespace std;

#include <memory>

struct Node
{
    int data;
    unique_ptr<Node> next;
};

class LinkedList
{
public:
    LinkedList();
    LinkedList(int number);

    int GetNumber();
    void Print();

private:
    unique_ptr<Node> first;

    unique_ptr<Node> CreateNode(int data);
};

LinkedList::LinkedList()
{ }

LinkedList::LinkedList(int number)
{
    while (number > 0)
    {
        int digit = number % 10;
        unique_ptr<Node> node = CreateNode(digit);
        node->next = move(first);
        first = move(node);
        number /= 10;
    }
}

unique_ptr<Node> LinkedList::CreateNode(int data)
{
    unique_ptr<Node> node = make_unique<Node>();
    node->data = data;
    return node;
}

void LinkedList::Print()
{
    Node* current = first.get();
    while (current)
    {
        cout << current->data;
        current = current->next.get();
        if (current)
            cout << "->";
    }
    cout << "\n";
}

int LinkedList::GetNumber()
{
    int number = 0;

    Node* node = first.get();
    while (node)
    {
        number = number * 10 + node->data;
        node = node->next.get();
    }

    return number;
}

int main()
{
    {
        LinkedList ll1(145);
        LinkedList ll2(6789);
        ll1.Print();
        ll2.Print();
        cout << ll1.GetNumber() << "\n";
        cout << ll2.GetNumber() << "\n";
    }
    _CrtDumpMemoryLeaks();

    return 0;
}
