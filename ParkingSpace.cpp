#include "ParkingSpace.h"

ParkingSpace::ParkingSpace(int spaceNumber, const std::string& size)
    : spaceNumber(spaceNumber), size(size), available(true) {}

int ParkingSpace::getSpaceNumber() const {
    return spaceNumber;
}

const std::string& ParkingSpace::getSize() const {
    return size;
}

bool ParkingSpace::isAvailable() const {
    return available;
}

void ParkingSpace::occupy() {
    available = false;
}

void ParkingSpace::release() {
    available = true;
}
