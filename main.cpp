#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "ParkingSpace.h"
#include "User.h"
#include "ParkingSession.h"

void registerParkingSpace(std::vector<ParkingSpace>& parkingSpaces, int spaceNumber, const std::string& size) {
    ParkingSpace newSpace(spaceNumber, size);
    parkingSpaces.push_back(newSpace);
    std::cout << "Parking space registered successfully.\n";
}

void registerUser(std::vector<User>& users, const std::string& name, const std::string& vehicleSize) {
    User newUser(name, vehicleSize);
    users.push_back(newUser);
    std::cout << "User registered successfully.\n";
}

ParkingSpace* findAvailableParkingSpace(std::vector<ParkingSpace>& parkingSpaces, const std::string& vehicleSize) {
    for (ParkingSpace& space : parkingSpaces) {
        if (space.isAvailable() && space.getSize() == vehicleSize) {
            return &space;
        }
    }
    return nullptr;
}

void bookParkingSpace(std::vector<ParkingSpace>& parkingSpaces, std::vector<User>& users,
                      std::vector<ParkingSession>& parkingSessions, const std::string& userName,
                      const std::string& vehicleSize, const std::string& startTime) {
    User* selectedUserPtr = nullptr;
    for (User& user : users) {
        if (user.getName() == userName && user.getVehicleSize() == vehicleSize) {
            selectedUserPtr = &user;
            break;
        }
    }
    if (selectedUserPtr == nullptr) {
        std::cout << "Invalid user selection or vehicle size.\n";
        return;
    }

    ParkingSpace* selectedSpacePtr = findAvailableParkingSpace(parkingSpaces, vehicleSize);
    if (selectedSpacePtr == nullptr) {
        std::cout << "No available parking space for the specified vehicle size.\n";
        return;
    }

    ParkingSession newSession(*selectedUserPtr, *selectedSpacePtr, startTime);
    selectedSpacePtr->occupy();
    parkingSessions.push_back(newSession);

    std::cout << "Parking space booked successfully!\n";
}

double calculateParkingFee(const ParkingSession& parkingSession, double hourlyRate) {
    int startHour = std::stoi(parkingSession.getStartTime().substr(11, 2));
    int endHour = std::stoi(parkingSession.getEndTime().substr(11, 2));
    int duration = endHour - startHour;
    double fee = duration * hourlyRate;
    return fee;
}

void generateReceipt(const ParkingSession& parkingSession, double parkingFee) {
    std::cout << "Receipt\n";
    std::cout << "User: " << parkingSession.getUser().getName() << std::endl;
    std::cout << "Parking Space: " << parkingSession.getSpace().getSpaceNumber() << std::endl;
    std::cout << "Vehicle Size: " << parkingSession.getUser().getVehicleSize() << std::endl;
    std::cout << "Start Time: " << parkingSession.getStartTime() << std::endl;
    std::cout << "End Time: " << parkingSession.getEndTime() << std::endl;
    std::cout << "Parking Fee: $" << parkingFee << std::endl;
    std::cout << "-------------------------\n";
}

void generateParkingReport(const std::vector<ParkingSpace>& parkingSpaces,
                           const std::vector<ParkingSession>& parkingSessions) {
    std::ofstream file("parking_report.txt");
    if (file.is_open()) {
        file << "Parking Report\n";
        file << "Available Spaces: ";
        int availableCompactSpaces = 0;
        int availableRegularSpaces = 0;
        int availableLargeSpaces = 0;
        for (const ParkingSpace& space : parkingSpaces) {
            if (space.isAvailable()) {
                if (space.getSize() == "compact") {
                    availableCompactSpaces++;
                } else if (space.getSize() == "regular") {
                    availableRegularSpaces++;
                } else if (space.getSize() == "large") {
                    availableLargeSpaces++;
                }
            }
        }
        file << "Compact: " << availableCompactSpaces << ", ";
        file << "Regular: " << availableRegularSpaces << ", ";
        file << "Large: " << availableLargeSpaces << "\n";

        file << "Parked Cars: ";
        int parkedCompactCars = 0;
        int parkedRegularCars = 0;
        int parkedLargeCars = 0;
        for (const ParkingSession& session : parkingSessions) {
            const std::string& vehicleSize = session.getUser().getVehicleSize();
            if (vehicleSize == "compact") {
                parkedCompactCars++;
            } else if (vehicleSize == "regular") {
                parkedRegularCars++;
            } else if (vehicleSize == "large") {
                parkedLargeCars++;
            }
        }
        file << "Compact: " << parkedCompactCars << ", ";
        file << "Regular: " << parkedRegularCars << ", ";
        file << "Large: " << parkedLargeCars << "\n";

        file << "-------------------------\n";
        file.close();
        std::cout << "Parking report generated and saved to file successfully.\n";
    } else {
        std::cout << "Unable to generate parking report or save to file.\n";
    }
}


int main() {
    std::vector<ParkingSpace> parkingSpaces;
    std::vector<User> users;
    std::vector<ParkingSession> parkingSessions;

    registerParkingSpace(parkingSpaces, 1, "compact");
    registerParkingSpace(parkingSpaces, 2, "regular");
    registerParkingSpace(parkingSpaces, 3, "large");

    registerUser(users, "Arman", "compact");
    registerUser(users, "Gago", "regular");

    bookParkingSpace(parkingSpaces, users, parkingSessions, "Arman", "compact", "2023-07-15 10:00");
    bookParkingSpace(parkingSpaces, users, parkingSessions, "Gago", "regular", "2023-07-15 12:30");

    const std::string endTime = "2023-07-15 14:30";
    double hourlyRate = 10.0;
    for (ParkingSession& session : parkingSessions) {
        session.endSession(endTime);
        double fee = calculateParkingFee(session, hourlyRate);
        generateReceipt(session, fee);
    }

    generateParkingReport(parkingSpaces, parkingSessions);

    return 0;
}
