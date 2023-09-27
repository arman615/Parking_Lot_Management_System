#ifndef PARKINGSPACE_H
#define PARKINGSPACE_H

#include <string>

class ParkingSpace {
private:
    int spaceNumber;
    std::string size;
    bool available;

public:
    ParkingSpace(int spaceNumber, const std::string& size);
    int getSpaceNumber() const;
    const std::string& getSize() const;
    bool isAvailable() const;
    void occupy();
    void release();
};

#endif
