#ifndef LOCKER_H
#define LOCKER_H

#include "RentableItem.h"

class Locker : public RentableItem {
private:
    int lockerNumber;
    std::string location;

public:
    Locker(const std::string& id, const std::string& name, bool avail, int num, const std::string& loc)
        : RentableItem(id, name, avail), lockerNumber(num), location(loc) {}

    int getLockerNumber() const { return lockerNumber; }
    std::string getLocation() const { return location; }

    void displayInfo() const override;
    std::string serialize() const override;
};

#endif // LOCKER_H
