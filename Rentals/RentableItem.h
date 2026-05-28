#ifndef RENTABLEITEM_H
#define RENTABLEITEM_H

#include <string>

class RentableItem {
protected:
    std::string itemId;
    std::string itemName;
    bool isAvailable;

public:
    RentableItem(const std::string& id, const std::string& name, bool avail)
        : itemId(id), itemName(name), isAvailable(avail) {}
    
    virtual ~RentableItem() = default;

    std::string getItemId() const { return itemId; }
    std::string getItemName() const { return itemName; }
    bool getAvailability() const { return isAvailable; }
    void setAvailability(bool avail) { isAvailable = avail; }

    virtual void displayInfo() const = 0;
    virtual std::string serialize() const = 0;
};

#endif // RENTABLEITEM_H
