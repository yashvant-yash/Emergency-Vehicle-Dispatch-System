#ifndef EMERGENCY_H
#define EMERGENCY_H

#include <string>

// Structure to store information about an emergency call
struct EmergencyRequest {
    int id;                      // Unique ID for the request (101, 102, etc.)
    std::string callerName;      // Name of caller or patient
    std::string emergencyType;   // E.g., "Cardiac Arrest", "Road Accident"
    std::string location;        // Patient location or address
    int priority;                // 1 = Critical, 2 = High, 3 = Medium, 4 = Low
    int arrivalOrder;            // Order in which the call arrived (used for FIFO tie-breaker)
    std::string status;          // "Pending", "Dispatched", or "Completed"
    std::string assignedVehicle; // ID of dispatched vehicle (e.g., "AMB-101")
};

// Structure to store information about an emergency vehicle
struct EmergencyVehicle {
    std::string id;              // Vehicle ID (e.g., "AMB-101")
    std::string type;            // E.g., "Ambulance 1"
    bool isAvailable;            // true if ready at base, false if out on a call
    int currentRequestId;        // Request ID currently assigned to this vehicle (0 if none)
};

#endif
