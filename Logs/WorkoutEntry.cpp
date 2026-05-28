#include "WorkoutEntry.h"
#include <iostream>
#include <sstream>

void WorkoutEntry::displayDetails() const {
    std::cout << "[運動日誌] 日期: " << date << "\n"
              << "  運動項目: " << exerciseType << "\n"
              << "  持續時間: " << durationMin << " 分鐘\n"
              << "  熱量消耗: -" << caloriesBurned << " kcal\n"
              << "  備註: " << notes << std::endl;
}

std::string WorkoutEntry::serialize() const {
    // Format: WORKOUT,date,notes,exerciseType,durationMin,caloriesBurned
    std::stringstream ss;
    ss << "WORKOUT," << date << "," << notes << "," << exerciseType << "," << durationMin << "," << caloriesBurned;
    return ss.str();
}
