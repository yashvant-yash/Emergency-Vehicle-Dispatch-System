#include <iostream>
#include <string>
#include "DispatchSystem.h"

// Prints the main menu options
void displayMenu() {
    std::cout << "\n============================================\n";
    std::cout << "     EMERGENCY VEHICLE DISPATCH SYSTEM      \n";
    std::cout << "============================================\n";
    std::cout << "1. Add Emergency Request\n";
    std::cout << "2. Display Pending Requests\n";
    std::cout << "3. View Highest Priority Request\n";
    std::cout << "4. Dispatch Emergency Vehicle\n";
    std::cout << "5. Check Available Vehicles\n";
    std::cout << "6. Return Vehicle to Service\n";
    std::cout << "7. View Dispatch History\n";
    std::cout << "8. Exit\n";
    std::cout << "============================================\n";
    std::cout << "Enter your choice (1-8): " << std::flush;
}

int main() {
    DispatchSystem system;
    int choice = 0;

    while (true) {
        displayMenu();

        // Read choice and handle invalid (non-numeric) input safely
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                break;
            }
            std::cout << "\nInvalid input! Please enter a number between 1 and 8.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        // Clear the newline left in the input buffer
        std::cin.ignore(10000, '\n');

        switch (choice) {
            case 1:
                system.addEmergencyRequest();
                break;
            case 2:
                system.displayPendingRequests();
                break;
            case 3:
                system.viewHighestPriorityRequest();
                break;
            case 4:
                system.dispatchVehicle();
                break;
            case 5:
                system.checkAvailableVehicles();
                break;
            case 6:
                system.returnVehicle();
                break;
            case 7:
                system.viewDispatchHistory();
                break;
            case 8:
                std::cout << "\nThank you for using the Emergency Dispatch System. Exiting...\n\n";
                return 0;
            default:
                std::cout << "\nInvalid choice! Please select an option from 1 to 8.\n";
                break;
        }
    }

    return 0;
}
