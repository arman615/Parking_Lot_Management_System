#ifndef PARKINGSESSION_H
#define PARKINGSESSION_H

#include "ParkingSpace.h"
#include "User.h"
#include <string>

class ParkingSession {
private:
    User user;
    ParkingSpace& space;
    std::string startTime;
    std::string endTime;

public:
    ParkingSession(const User& user, ParkingSpace& space, const std::string& startTime);
    void endSession(const std::string& endTime);
    const User& getUser() const;
    const ParkingSpace& getSpace() const;
    const std::string& getStartTime() const;
    const std::string& getEndTime() const;
};

#endif
