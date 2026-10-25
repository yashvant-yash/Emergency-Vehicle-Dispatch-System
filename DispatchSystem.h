#ifndef DISPATCH_SYSTEM_H
#define DISPATCH_SYSTEM_H

#include <vector>
#include <string>
#include "Emergency.h"
#include "PriorityQueue.h"

// DispatchSystem manages the overall emergency system:
// - Stores pending emergency calls inside the Priority Queue.
// - Tracks available emergency vehicles.
// - Maintains a history of dispatched calls.
class DispatchSystem {
private:
    PriorityQueue requestQueue;                  // Min Heap Priority Queue for requests
    std::vector<EmergencyVehicle> vehicles;      // Fleet of 3 emergency vehicles
    std::vector<EmergencyRequest> history;       // Log of dispatched/completed missions
    int nextId;                                  // Unique ID counter (101, 102...)
    int arrivalCounter;                          // Arrival sequence counter (1, 2...)

    void setupVehicles();
    int findAvailableVehicle() const;
    int findVehicleById(const std::string& vehicleId) const;

public:
    DispatchSystem();

    // The 7 active features (Feature 8 is Exit in main):
    void addEmergencyRequest();
    void addRequest(const std::string& callerName, const std::string& emergencyType,
                    const std::string& location, int priority);

    void displayPendingRequests() const;
    void viewHighestPriorityRequest() const;
    void dispatchVehicle();
    void checkAvailableVehicles() const;

    void returnVehicle();
    bool returnVehicleById(const std::string& vehicleId);

    void viewDispatchHistory() const;
};

#endif
