#ifndef REGULARUSER_H
#define REGULARUSER_H

#include "User.h"
#include "LogEntry.h"
#include <vector>
#include <memory>

class RegularUser : public User {
private:
    double weight;
    double height;
    int calorieTarget;
    std::vector<std::shared_ptr<LogEntry>> logs;

public:
    RegularUser(const std::string& uname, const std::string& pwd, double w, double h, int cal)
        : User(uname, pwd, UserRole::REGULAR), weight(w), height(h), calorieTarget(cal) {}

    double getWeight() const { return weight; }
    double getHeight() const { return height; }
    int getCalorieTarget() const { return calorieTarget; }
    
    const std::vector<std::shared_ptr<LogEntry>>& getLogs() const { return logs; }
    void addLog(std::shared_ptr<LogEntry> log) { logs.push_back(log); }

    double calculateBMI() const;
    
    void displayMenu() override;
    void showDashboard() override;
    std::string serialize() const override;
};

#endif // REGULARUSER_H
