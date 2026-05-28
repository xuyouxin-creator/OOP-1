#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "RentableItem.h"

class Equipment : public RentableItem {
private:
    double weightKg;
    std::string condition;

public:
    Equipment(const std::string& id, const std::string& name, bool avail, double w, const std::string& cond)
        : RentableItem(id, name, avail), weightKg(w), condition(cond) {}

    double getWeightKg() const { return weightKg; }
    std::string getCondition() const { return condition; }

    void displayInfo() const override;
    std::string serialize() const override;
};

#endif // EQUIPMENT_H
