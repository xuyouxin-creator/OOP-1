#ifndef DIETENTRY_H
#define DIETENTRY_H

#include "LogEntry.h"

class DietEntry : public LogEntry {
private:
    std::string foodName;
    int carbs;
    int protein;
    int fat;
    int caloriesGained;

public:
    DietEntry(const std::string& d, const std::string& n, const std::string& fName, int c, int p, int f, int cal)
        : LogEntry(d, n), foodName(fName), carbs(c), protein(p), fat(f), caloriesGained(cal) {}

    std::string getFoodName() const { return foodName; }
    int getCarbs() const { return carbs; }
    int getProtein() const { return protein; }
    int getFat() const { return fat; }

    int getCalories() const override { return caloriesGained; }
    void displayDetails() const override;
    std::string serialize() const override;
};

#endif // DIETENTRY_H
