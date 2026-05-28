#include "Locker.h"
#include <iostream>
#include <sstream>

void Locker::displayInfo() const {
    std::cout << "[置物櫃] ID: " << itemId 
              << " | 名稱: " << itemName 
              << " | 櫃號: " << lockerNumber 
              << " | 位置: " << location 
              << " | 狀態: " << (isAvailable ? "● 可租借" : "○ 已出租") << std::endl;
}

std::string Locker::serialize() const {
    // Format: LOCKER,id,name,isAvailable,lockerNumber,location
    std::stringstream ss;
    ss << "LOCKER," << itemId << "," << itemName << "," << (isAvailable ? "true" : "false")
       << "," << lockerNumber << "," << location;
    return ss.str();
}
