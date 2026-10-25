#include "PriorityQueue.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

// Constructor
PriorityQueue::PriorityQueue() {
    // Vector starts empty
}

// Determines which request has higher priority.
// 1. Smaller priority number has higher urgency (1 is most critical, 4 is least).
// 2. If priorities are equal, the earlier call (smaller arrivalOrder) is processed first (FIFO).
bool PriorityQueue::isHigherPriority(const EmergencyRequest& a, const EmergencyRequest& b) const {
    if (a.priority != b.priority) {
        return a.priority < b.priority;
    }
    return a.arrivalOrder < b.arrivalOrder;
}

// heapifyUp moves a newly inserted element up the tree to its valid position.
// Time Complexity: O(log N)
void PriorityQueue::heapifyUp(int index) {
    while (index > 0 && isHigherPriority(heap[index], heap[parent(index)])) {
        std::swap(heap[index], heap[parent(index)]);
        index = parent(index); // Move up to parent's index
    }
}

// heapifyDown moves the root replacement down the tree to restore heap order.
// Time Complexity: O(log N)
void PriorityQueue::heapifyDown(int index) {
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    int n = heap.size();

    // Check if left child has higher priority than current node
    if (left < n && isHigherPriority(heap[left], heap[smallest])) {
        smallest = left;
    }

    // Check if right child has higher priority than current smallest
    if (right < n && isHigherPriority(heap[right], heap[smallest])) {
        smallest = right;
    }

    // If smallest is not the current index, swap and continue sinking down
    if (smallest != index) {
        std::swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

// Inserts a new request into the priority queue.
// 1. Adds to the end of the vector (as the next leaf).
// 2. Bubbles it up to its proper place using heapifyUp().
// Time Complexity: O(log N)
void PriorityQueue::insert(const EmergencyRequest& req) {
    heap.push_back(req);
    heapifyUp(heap.size() - 1);
}

// Removes and returns the highest priority request (root element at index 0).
// 1. Saves root element.
// 2. Copies the last element into the root position.
// 3. Removes the last element.
// 4. Calls heapifyDown(0) to restore the heap property.
// Time Complexity: O(log N)
EmergencyRequest PriorityQueue::extractMin() {
    if (isEmpty()) {
        EmergencyRequest emptyReq = {0, "", "", "", 4, 0, "None", "None"};
        return emptyReq;
    }

    EmergencyRequest root = heap[0];
    heap[0] = heap.back();
    heap.pop_back();

    if (!heap.empty()) {
        heapifyDown(0);
    }

    return root;
}

// Returns the highest priority request without removing it.
// Time Complexity: O(1)
EmergencyRequest PriorityQueue::peek() const {
    if (isEmpty()) {
        EmergencyRequest emptyReq = {0, "", "", "", 4, 0, "None", "None"};
        return emptyReq;
    }
    return heap[0];
}

// Checks if the priority queue is empty
bool PriorityQueue::isEmpty() const {
    return heap.empty();
}

// Returns total number of requests in the priority queue
int PriorityQueue::size() const {
    return heap.size();
}

// Displays all pending requests in true priority order.
// We make a temporary copy and extract elements one by one (like HeapSort)
// so the original queue remains untouched.
void PriorityQueue::display() const {
    if (isEmpty()) {
        std::cout << "\nNo pending emergency requests in the queue.\n";
        return;
    }

    PriorityQueue temp = *this;

    std::cout << "\n+-----+---------+----------------------+----------------------+----------------------+---------------+----------+\n";
    std::cout << "| No. | Req ID  | Patient / Caller     | Emergency Type       | Location             | Priority      | Arrival# |\n";
    std::cout << "+-----+---------+----------------------+----------------------+----------------------+---------------+----------+\n";

    int count = 1;
    while (!temp.isEmpty()) {
        EmergencyRequest r = temp.extractMin();

        std::string prioStr;
        if (r.priority == 1) prioStr = "1 - Critical";
        else if (r.priority == 2) prioStr = "2 - High";
        else if (r.priority == 3) prioStr = "3 - Medium";
        else prioStr = "4 - Low";

        std::cout << "| " << std::setw(3) << count++ << " | "
                  << std::setw(7) << r.id << " | "
                  << std::left << std::setw(20) << r.callerName.substr(0, 20) << " | "
                  << std::left << std::setw(20) << r.emergencyType.substr(0, 20) << " | "
                  << std::left << std::setw(20) << r.location.substr(0, 20) << " | "
                  << std::left << std::setw(13) << prioStr << " | "
                  << std::right << std::setw(8) << r.arrivalOrder << " |\n";
    }
    std::cout << "+-----+---------+----------------------+----------------------+----------------------+---------------+----------+\n";
    std::cout << "Total pending requests: " << (count - 1) << "\n";
}
