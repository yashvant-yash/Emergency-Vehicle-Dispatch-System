# Emergency Vehicle Dispatch System Using Priority Queue

A Data Structures group project for Second Year Computer Engineering.

---

## 1. Problem Statement

In an emergency dispatch system (like an ambulance helpline), calls arrive at different times and with different urgency levels. If a normal First-In, First-Out (FIFO) queue is used, a patient with a life-threatening heart attack calling at 10:05 AM might be forced to wait behind callers with minor injuries who called at 10:01 AM.

To solve this, emergency calls must be organized by **urgency** rather than just arrival time. However, when two patients have the exact same urgency, the one who called first should be attended to first.

---

## 2. Objective

- Develop a console-based Emergency Vehicle Dispatch System in C++.
- Implement a custom **Priority Queue** using a **Binary Min Heap**.
- Process emergency calls based on urgency (Priority 1 is the most urgent).
- Use arrival sequence numbers to maintain FIFO order when priorities are equal.
- Manage vehicle availability (3 vehicles initially) and prevent assigning unavailable vehicles.

---

## 3. Features

1. **Add Emergency Request**: Enter patient name, emergency type, location, and priority (1-4).
2. **Display Pending Requests**: View all waiting emergency requests in priority order.
3. **View Highest Priority Request**: Peek at the next call in line for dispatch without removing it.
4. **Dispatch Emergency Vehicle**: Assign an available ambulance to the most urgent request and reduce available vehicle count.
5. **Check Available Vehicles**: Display the status of all 3 emergency vehicles.
6. **Return Vehicle to Service**: Mark a returned vehicle as available again and prevent duplicate returns.
7. **View Dispatch History**: See all completed and active dispatches.
8. **Exit**: Exit the program safely.

### Priority Levels:
- **1 - Critical**: Immediate danger to life (e.g., Cardiac Arrest, Severe Trauma).
- **2 - High**: Serious conditions requiring urgent care (e.g., Major Fractures, Asthma Attack).
- **3 - Medium**: Moderate injuries (e.g., Lacerations, Concussions).
- **4 - Low**: Non-urgent situations (e.g., Minor Cuts, Mild Sprains).

*Note:* Smaller priority number = higher urgency.

---

## 4. Data Structure Used: Binary Min Heap

We implemented our Priority Queue using a **Binary Min Heap** backed by a standard `std::vector`. We did not use the built-in C++ STL `priority_queue`.

### Why Min Heap?
- In our system, **Priority 1 (Critical)** is more urgent than **Priority 4 (Low)**.
- A **Min Heap** keeps the smallest number (highest urgency) at the root (index 0).
- Checking the top request (`peek`) takes **O(1)** time.
- Adding a request (`insert`) takes **O(log N)** time.
- Removing the top request (`extractMin`) takes **O(log N)** time.

### Array Representation:
A complete binary tree can be stored in a 0-indexed array or vector:
- **Parent of index `i`**: `(i - 1) / 2`
- **Left Child of index `i`**: `2 * i + 1`
- **Right Child of index `i`**: `2 * i + 2`

---

## 5. Working of Priority Queue

### 1. Insertion (`insert` and `heapifyUp`)
- The new request is added to the end of the vector (as the next leaf node).
- `heapifyUp()` compares the new element with its parent. If the new element has higher urgency, it is swapped with its parent. This continues until the heap property is restored.

### 2. Extraction (`extractMin` and `heapifyDown`)
- The most urgent request is at index 0 (root).
- We save the root, then move the last element of the vector into index 0.
- We delete the last element.
- `heapifyDown()` compares the new root with its children and swaps it with the most urgent child. This repeats down the tree until the heap order is restored.

### 3. Tie-Breaking for Equal Priorities
- When two requests have the same priority level, we compare their `arrivalOrder`.
- The request with the smaller `arrivalOrder` (which arrived first) is placed higher in the heap.

---

## 6. Project Files

```text
Emergency-Vehicle-Dispatch-System/
├── Emergency.h          # Structs for EmergencyRequest and EmergencyVehicle
├── PriorityQueue.h      # PriorityQueue class declaration (Min Heap)
├── PriorityQueue.cpp    # Min Heap operations (insert, extractMin, heapifyUp, heapifyDown)
├── DispatchSystem.h     # DispatchSystem class declaration
├── DispatchSystem.cpp   # Fleet tracking, dispatch, and menu functions
├── main.cpp             # Main program loop and menu display
├── README.md            # Project documentation
└── .gitignore           # Git ignore file for compiled binaries
```

---

## 7. Compilation and Execution Instructions

### Using Windows Command Prompt (`cmd.exe`) or PowerShell:

1. Open terminal inside the project folder:
   ```cmd
   cd Emergency-Vehicle-Dispatch-System
   ```

2. Compile the project:
   ```cmd
   g++ -std=c++17 -Wall main.cpp PriorityQueue.cpp DispatchSystem.cpp -o emergency_dispatch.exe
   ```

3. Run the application:
   ```cmd
   .\emergency_dispatch.exe
   ```

---

## 8. Sample Output

### Main Menu
```text
============================================
     EMERGENCY VEHICLE DISPATCH SYSTEM      
============================================
1. Add Emergency Request
2. Display Pending Requests
3. View Highest Priority Request
4. Dispatch Emergency Vehicle
5. Check Available Vehicles
6. Return Vehicle to Service
7. View Dispatch History
8. Exit
============================================
Enter your choice (1-8):
```

### Displaying Pending Requests (Priority Order)
```text
+-----+---------+----------------------+----------------------+----------------------+---------------+----------+
| No. | Req ID  | Patient / Caller     | Emergency Type       | Location             | Priority      | Arrival# |
+-----+---------+----------------------+----------------------+----------------------+---------------+----------+
|   1 |     102 | Jane Smith           | Cardiac Arrest       | Central Market       | 1 - Critical  |        2 |
|   2 |     101 | John Doe             | Severe Asthma        | North Block          | 2 - High      |        1 |
|   3 |     103 | Robert Brown         | Leg Fracture         | Highway 10           | 2 - High      |        3 |
|   4 |     104 | Michael Green        | Minor Ankle Sprain   | Sports Complex       | 4 - Low       |        4 |
+-----+---------+----------------------+----------------------+----------------------+---------------+----------+
Total pending requests: 4
```
*(Notice: Jane Smith with Priority 1 is first. John Doe and Robert Brown both have Priority 2, but John Doe is served first because his Arrival# is 1 while Robert's is 3).*

### Dispatching an Emergency Vehicle
```text
--- Dispatch Emergency Vehicle ---
[Dispatched] Vehicle AMB-101 (ALS Ambulance) sent to:
  Patient       : Jane Smith
  Emergency Type: Cardiac Arrest (Priority 1)
  Location      : Central Market
```

---

## 9. Group Members

| Roll No. | Student Name | Class / Department | Contribution |
| :---: | :--- | :---: | :--- |
| `[Roll No 1]` | `[Student Name 1]` | SE Computer Engineering | Priority Queue & Min Heap implementation |
| `[Roll No 2]` | `[Student Name 2]` | SE Computer Engineering | Dispatch System & Vehicle management |
| `[Roll No 3]` | `[Student Name 3]` | SE Computer Engineering | Console Menu & Input handling |
| `[Roll No 4]` | `[Student Name 4]` | SE Computer Engineering | Testing & Documentation |

---

## 10. Academic Disclaimer

This project is an academic simulation created for the Second Year Computer Engineering Data Structures curriculum. It is intended for educational purposes only to demonstrate how binary heaps and priority queues work in practice.
