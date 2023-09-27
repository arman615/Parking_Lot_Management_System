#include "ParkingSession.h"

ParkingSession::ParkingSession(const User& user, ParkingSpace& space, const std::string& startTime)
    : user(user), space(space), startTime(startTime) {}

void ParkingSession::endSession(const std::string& endTime) {
    this->endTime = endTime;
    space.release();
}

const User& ParkingSession::getUser() const {
    return user;
}

const ParkingSpace& ParkingSession::getSpace() const {
    return space;
}

const std::string& ParkingSession::getStartTime() const {
    return startTime;
}

const std::string& ParkingSession::getEndTime() const {
    return endTime;
}
