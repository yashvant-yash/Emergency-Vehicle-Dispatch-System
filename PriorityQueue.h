#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include "Emergency.h"

// Priority Queue implemented manually using a Binary Min Heap.
// We use a Min Heap because a smaller priority number represents higher urgency:
// 1 = Critical, 2 = High, 3 = Medium, 4 = Low.
class PriorityQueue {
private:
    std::vector<EmergencyRequest> heap; // Dynamic array representing the binary tree

    // Helper functions for array-based binary heap indexing (0-based)
    int parent(int i) const { return (i - 1) / 2; }
    int leftChild(int i) const { return (2 * i) + 1; }
    int rightChild(int i) const { return (2 * i) + 2; }

    // Compares two requests: returns true if 'a' has higher priority than 'b'
    bool isHigherPriority(const EmergencyRequest& a, const EmergencyRequest& b) const;

    // Moves an element upward until the Min Heap property is restored
    void heapifyUp(int index);

    // Moves an element downward until the Min Heap property is restored
    void heapifyDown(int index);

public:
    PriorityQueue();

    // Core Priority Queue functions
    void insert(const EmergencyRequest& req);
    EmergencyRequest extractMin();
    EmergencyRequest peek() const;
    bool isEmpty() const;
    int size() const;
    void display() const;
};

#endif
