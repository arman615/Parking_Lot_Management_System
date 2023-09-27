#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string name;
    std::string vehicleSize;

public:
    User(const std::string& name, const std::string& vehicleSize);
    const std::string& getName() const;
    const std::string& getVehicleSize() const;
};

#endif
