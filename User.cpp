#include "User.h"

User::User(const std::string& name, const std::string& vehicleSize)
    : name(name), vehicleSize(vehicleSize) {}

const std::string& User::getName() const {
    return name;
}

const std::string& User::getVehicleSize() const {
    return vehicleSize;
}
