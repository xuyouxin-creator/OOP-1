#include "DietEntry.h"
#include <iostream>
#include <sstream>

void DietEntry::displayDetails() const {
    std::cout << "[飲食日誌] 日期: " << date << "\n"
              << "  食物名稱: " << foodName << "\n"
              << "  營養成分: 碳水: " << carbs << "g | 蛋白質: " << protein << "g | 脂肪: " << fat << "g\n"
              << "  熱量攝入: +" << caloriesGained << " kcal\n"
              << "  備註: " << notes << std::endl;
}

std::string DietEntry::serialize() const {
    // Format: DIET,date,notes,foodName,carbs,protein,fat,caloriesGained
    std::stringstream ss;
    ss << "DIET," << date << "," << notes << "," << foodName << "," << carbs << "," << protein << "," << fat << "," << caloriesGained;
    return ss.str();
}
