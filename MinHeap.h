#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

const double INF = 1e9;

struct HeapNode {
    int vertex;
    double dist;
};

class MinHeap {
private:
    vector<HeapNode> heap;

    void heapifyUp(int idx);
    void heapifyDown(int idx);

public:
    MinHeap();
    bool empty() const;
    void push(int vertex, double dist);
    HeapNode pop();
};

#endif
