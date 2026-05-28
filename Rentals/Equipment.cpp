#include "Equipment.h"
#include <iostream>
#include <sstream>

void Equipment::displayInfo() const {
    std::cout << "[器材] ID: " << itemId 
              << " | 名稱: " << itemName 
              << " | 重量: " << weightKg << " kg"
              << " | 損耗狀態: " << condition 
              << " | 狀態: " << (isAvailable ? "● 可租借" : "○ 已出租") << std::endl;
}

std::string Equipment::serialize() const {
    // Format: EQUIPMENT,id,name,isAvailable,weightKg,condition
    std::stringstream ss;
    ss << "EQUIPMENT," << itemId << "," << itemName << "," << (isAvailable ? "true" : "false")
       << "," << weightKg << "," << condition;
    return ss.str();
}
