#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

struct HeapNode {
    int vertex;
    int dist;
};

class MinHeap {
private:
    vector<HeapNode> heap;

    void heapifyUp(int idx);
    void heapifyDown(int idx);

public:
    MinHeap();
    bool empty() const;
    void push(int vertex, int dist);
    HeapNode pop();
};

#endif

