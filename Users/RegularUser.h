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
    void setWeight(double w) { weight = w; }
    void setHeight(double h) { height = h; }
    void setCalorieTarget(int cal) { calorieTarget = cal; }
    void setPassword(const std::string& pwd) { password = pwd; }
    
    const std::vector<std::shared_ptr<LogEntry>>& getLogs() const { return logs; }
    void addLog(std::shared_ptr<LogEntry> log) { logs.push_back(log); }
    
    // 刪除指定索引的日誌
    bool deleteLog(int index) {
        if (index >= 0 && index < static_cast<int>(logs.size())) {
            logs.erase(logs.begin() + index);
            return true;
        }
        return false;
    }
    
    // 清除所有日誌
    void clearAllLogs() { logs.clear(); }

    double calculateBMI() const;
    
    void displayMenu() override;
    void showDashboard() override;
    std::string serialize() const override;
};

#endif // REGULARUSER_H
