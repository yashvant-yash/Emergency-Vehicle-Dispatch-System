#include "DispatchSystem.h"
#include <iostream>
#include <iomanip>
#include <cctype>

// Helper to compare two strings case-insensitively
static bool equalsIgnoreCase(const std::string& a, const std::string& b) {
    if (a.length() != b.length()) return false;
    for (size_t i = 0; i < a.length(); ++i) {
        if (std::tolower(a[i]) != std::tolower(b[i])) {
            return false;
        }
    }
    return true;
}

// Constructor: Initializes ID counters and the fleet of 3 vehicles
DispatchSystem::DispatchSystem() {
    nextId = 101;
    arrivalCounter = 1;
    setupVehicles();
}

// Sets up the initial fleet with exactly 3 vehicles
void DispatchSystem::setupVehicles() {
    vehicles.clear();
    vehicles.push_back({"AMB-101", "ALS Ambulance", true, 0});
    vehicles.push_back({"AMB-102", "BLS Ambulance", true, 0});
    vehicles.push_back({"AMB-103", "Quick Response Unit", true, 0});
}

// Returns the index of the first available vehicle, or -1 if all are busy
int DispatchSystem::findAvailableVehicle() const {
    for (size_t i = 0; i < vehicles.size(); ++i) {
        if (vehicles[i].isAvailable) {
            return i;
        }
    }
    return -1;
}

// Finds a vehicle by its ID (e.g. "AMB-101")
int DispatchSystem::findVehicleById(const std::string& vehicleId) const {
    for (size_t i = 0; i < vehicles.size(); ++i) {
        if (equalsIgnoreCase(vehicles[i].id, vehicleId)) {
            return i;
        }
    }
    return -1;
}

// Feature 1: Add New Emergency Request (Interactive)
void DispatchSystem::addEmergencyRequest() {
    std::string callerName, emergencyType, location;
    int priority = 4;

    std::cout << "\n--- Add Emergency Request ---\n";
    std::cout << "Enter Caller / Patient Name: ";
    std::getline(std::cin, callerName);

    std::cout << "Enter Emergency Type (e.g., Heart Attack, Accident): ";
    std::getline(std::cin, emergencyType);

    std::cout << "Enter Location / Address: ";
    std::getline(std::cin, location);

    std::cout << "\nPriority Levels:\n";
    std::cout << "  1 = Critical (Immediate danger to life)\n";
    std::cout << "  2 = High     (Severe illness or injury)\n";
    std::cout << "  3 = Medium   (Moderate condition)\n";
    std::cout << "  4 = Low      (Non-urgent)\n";

    while (true) {
        std::cout << "Enter Priority (1-4): ";
        if (std::cin >> priority && priority >= 1 && priority <= 4) {
            std::cin.ignore(10000, '\n'); // Clear leftover newline
            break;
        }
        std::cout << "Invalid priority! Please enter a number between 1 and 4.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    addRequest(callerName, emergencyType, location, priority);
}

// Add Request Programmatically
void DispatchSystem::addRequest(const std::string& callerName, const std::string& emergencyType,
                                const std::string& location, int priority) {
    EmergencyRequest req;
    req.id = nextId++;
    req.arrivalOrder = arrivalCounter++;
    req.callerName = callerName;
    req.emergencyType = emergencyType;
    req.location = location;
    req.priority = priority;
    req.status = "Pending";
    req.assignedVehicle = "None";

    // Insert into the Min Heap Priority Queue
    requestQueue.insert(req);

    std::cout << "\n[Success] Emergency Request #" << req.id << " added to Priority Queue.\n";
    std::cout << "Arrival Sequence: #" << req.arrivalOrder << " | Priority: " << req.priority << "\n";
}

// Feature 2: Display All Pending Requests in Priority Order
void DispatchSystem::displayPendingRequests() const {
    std::cout << "\n--- Pending Emergency Requests (Priority Order) ---\n";
    requestQueue.display();
}

// Feature 3: View Highest Priority Request (Peek)
void DispatchSystem::viewHighestPriorityRequest() const {
    std::cout << "\n--- Highest Priority Request ---\n";
    if (requestQueue.isEmpty()) {
        std::cout << "No pending requests in the queue.\n";
        return;
    }

    EmergencyRequest top = requestQueue.peek();
    std::cout << "Request ID      : #" << top.id << "\n";
    std::cout << "Patient Name    : " << top.callerName << "\n";
    std::cout << "Emergency Type  : " << top.emergencyType << "\n";
    std::cout << "Location        : " << top.location << "\n";
    std::cout << "Priority Level  : " << top.priority << " (1 = Critical)\n";
    std::cout << "Arrival Sequence: #" << top.arrivalOrder << "\n";
    std::cout << "Status          : " << top.status << "\n";
}

// Feature 4: Dispatch Emergency Vehicle
void DispatchSystem::dispatchVehicle() {
    std::cout << "\n--- Dispatch Emergency Vehicle ---\n";

    // 1. Check if there are requests waiting
    if (requestQueue.isEmpty()) {
        std::cout << "Cannot dispatch: No pending requests in the queue.\n";
        return;
    }

    // 2. Check if a vehicle is available
    int vehIndex = findAvailableVehicle();
    if (vehIndex == -1) {
        std::cout << "[Alert] All 3 vehicles are currently busy!\n";
        std::cout << "The request remains PENDING in the Priority Queue until a vehicle returns.\n";
        return;
    }

    // 3. Remove the most urgent request from the Min Heap
    EmergencyRequest req = requestQueue.extractMin();

    // 4. Assign the available vehicle
    EmergencyVehicle& veh = vehicles[vehIndex];
    veh.isAvailable = false;
    veh.currentRequestId = req.id;

    // 5. Update request status and log in history
    req.status = "Dispatched";
    req.assignedVehicle = veh.id;
    history.push_back(req);

    std::cout << "[Dispatched] Vehicle " << veh.id << " (" << veh.type << ") sent to:\n";
    std::cout << "  Patient       : " << req.callerName << "\n";
    std::cout << "  Emergency Type: " << req.emergencyType << " (Priority " << req.priority << ")\n";
    std::cout << "  Location      : " << req.location << "\n";
}

// Feature 5: Check Available Vehicles
void DispatchSystem::checkAvailableVehicles() const {
    std::cout << "\n--- Emergency Vehicle Fleet Status ---\n";
    std::cout << "+------------+----------------------+----------------------+------------+\n";
    std::cout << "| Vehicle ID | Type                 | Status               | Active Req |\n";
    std::cout << "+------------+----------------------+----------------------+------------+\n";

    int readyCount = 0;
    for (const auto& v : vehicles) {
        std::string statusStr = v.isAvailable ? "Available" : "On Dispatch";
        std::string reqStr = (v.currentRequestId != 0) ? ("Req #" + std::to_string(v.currentRequestId)) : "-";

        if (v.isAvailable) readyCount++;

        std::cout << "| " << std::left << std::setw(10) << v.id << " | "
                  << std::left << std::setw(20) << v.type << " | "
                  << std::left << std::setw(20) << statusStr << " | "
                  << std::left << std::setw(10) << reqStr << " |\n";
    }
    std::cout << "+------------+----------------------+----------------------+------------+\n";
    std::cout << "Available Vehicles: " << readyCount << " / " << vehicles.size() << "\n";
}

// Feature 6: Return Dispatched Vehicle (Interactive)
void DispatchSystem::returnVehicle() {
    std::cout << "\n--- Return Vehicle to Service ---\n";

    // Show which vehicles are currently dispatched
    bool anyDispatched = false;
    for (const auto& v : vehicles) {
        if (!v.isAvailable) {
            std::cout << "  * " << v.id << " is currently serving Request #" << v.currentRequestId << "\n";
            anyDispatched = true;
        }
    }

    if (!anyDispatched) {
        std::cout << "All vehicles are already at the station (Available).\n";
        return;
    }

    std::string vehId;
    std::cout << "Enter Vehicle ID to return (e.g., AMB-101): ";
    std::getline(std::cin, vehId);

    returnVehicleById(vehId);
}

// Return Vehicle by ID
bool DispatchSystem::returnVehicleById(const std::string& vehicleId) {
    int idx = findVehicleById(vehicleId);
    if (idx == -1) {
        std::cout << "[Error] Vehicle ID '" << vehicleId << "' not found in the fleet.\n";
        return false;
    }

    // Check if the vehicle is already available (prevent duplicate returns)
    if (vehicles[idx].isAvailable) {
        std::cout << "[Warning] Vehicle '" << vehicles[idx].id << "' is already available!\n";
        return false;
    }

    // Return the vehicle to service
    int completedId = vehicles[idx].currentRequestId;
    vehicles[idx].isAvailable = true;
    vehicles[idx].currentRequestId = 0;

    // Update the mission status in history
    for (auto& h : history) {
        if (h.id == completedId) {
            h.status = "Completed";
            break;
        }
    }

    std::cout << "[Success] Vehicle " << vehicles[idx].id << " returned to base station.\n";
    std::cout << "Request #" << completedId << " is now marked as Completed.\n";
    return true;
}

// Feature 7: View Dispatch History
void DispatchSystem::viewDispatchHistory() const {
    std::cout << "\n--- Dispatch Mission History ---\n";
    if (history.empty()) {
        std::cout << "No dispatch records found yet.\n";
        return;
    }

    std::cout << "+---------+----------------------+----------------------+----------+------------+------------+\n";
    std::cout << "| Req ID  | Patient Name         | Emergency Type       | Priority | Vehicle    | Status     |\n";
    std::cout << "+---------+----------------------+----------------------+----------+------------+------------+\n";

    for (const auto& h : history) {
        std::cout << "| " << std::setw(7) << h.id << " | "
                  << std::left << std::setw(20) << h.callerName.substr(0, 20) << " | "
                  << std::left << std::setw(20) << h.emergencyType.substr(0, 20) << " | "
                  << std::setw(8) << h.priority << " | "
                  << std::left << std::setw(10) << h.assignedVehicle << " | "
                  << std::left << std::setw(10) << h.status << " |\n";
    }
    std::cout << "+---------+----------------------+----------------------+----------+------------+------------+\n";
    std::cout << "Total missions logged: " << history.size() << "\n";
}
