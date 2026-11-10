#include "MinHeap.h"

MinHeap::MinHeap() {}

void MinHeap::heapifyUp(int idx) {
    while (idx > 0) {
        int p = (idx - 1) / 2;
        if (heap[idx].dist < heap[p].dist) {
            swap(heap[idx], heap[p]);
            idx = p;
        } else {
            break;
        }
    }
}

void MinHeap::heapifyDown(int idx) {
    int n = heap.size();
    while (true) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < n && heap[left].dist < heap[smallest].dist)
            smallest = left;
        if (right < n && heap[right].dist < heap[smallest].dist)
            smallest = right;

        if (smallest != idx) {
            swap(heap[idx], heap[smallest]);
            idx = smallest;
        } else {
            break;
        }
    }
}

bool MinHeap::empty() const {
    return heap.empty();
}

void MinHeap::push(int vertex, double dist) {
    heap.push_back({vertex, dist});
    heapifyUp(heap.size() - 1);
}

HeapNode MinHeap::pop() {
    if (heap.empty()) return {-1, INF};
    HeapNode top = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty()) {
        heapifyDown(0);
    }
    return top;
}
