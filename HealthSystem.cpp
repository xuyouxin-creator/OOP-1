#include "HealthSystem.h"
#include "RegularUser.h"
#include "AdminUser.h"
#include "DietEntry.h"
#include "WorkoutEntry.h"
#include "Locker.h"
#include "Equipment.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

HealthSystem::HealthSystem() : currentUser(nullptr) {
    loadDatabase();
}

std::vector<std::string> HealthSystem::split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool HealthSystem::loadDatabase() {
    loadUsers();
    loadInventory();
    loadRentals();
    return true;
}

bool HealthSystem::saveDatabase() {
    saveUsers();
    saveInventory();
    saveRentals();
    return true;
}

void HealthSystem::loadUsers() {
    users.clear();
    std::ifstream file("users.txt");
    
    if (!file.is_open()) {
        // Create default users.txt
        std::ofstream outfile("users.txt");
        outfile << "ADMIN,admin,admin\n";
        outfile << "REGULAR,user,user,70.0,175.0,2000\n";
        outfile.close();
        
        // Add to memory
        users["admin"] = std::make_shared<AdminUser>("admin", "admin");
        auto reg = std::make_shared<RegularUser>("user", "user", 70.0, 175.0, 2000);
        users["user"] = reg;
        loadUserLogs("user", reg);
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() < 3) continue;

        std::string type = tokens[0];
        std::string username = tokens[1];
        std::string password = tokens[2];

        if (type == "ADMIN") {
            users[username] = std::make_shared<AdminUser>(username, password);
        } else if (type == "REGULAR") {
            if (tokens.size() < 6) continue;
            double weight = std::stod(tokens[3]);
            double height = std::stod(tokens[4]);
            int calorieTarget = std::stoi(tokens[5]);
            
            auto reg = std::make_shared<RegularUser>(username, password, weight, height, calorieTarget);
            users[username] = reg;
            loadUserLogs(username, reg);
        }
    }
    file.close();
}

void HealthSystem::loadUserLogs(const std::string& username, const std::shared_ptr<User>& user) {
    auto regUser = std::dynamic_pointer_cast<RegularUser>(user);
    if (!regUser) return;

    std::string filename = "logs_" + username + ".txt";
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        // Create empty logs or preload with demo logs for default user
        if (username == "user") {
            std::ofstream outfile(filename);
            outfile << "DIET,2026-05-28,午餐補充優質蛋白質,煎雞胸肉沙拉,15,35,8,450\n";
            outfile << "WORKOUT,2026-05-28,今日有氧消脂,跑步機慢跑,45,350\n";
            outfile.close();
            
            regUser->addLog(std::make_shared<DietEntry>("2026-05-28", "午餐補充優質蛋白質", "煎雞胸肉沙拉", 15, 35, 8, 450));
            regUser->addLog(std::make_shared<WorkoutEntry>("2026-05-28", "今日有氧消脂", "跑步機慢跑", 45, 350));
        }
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() < 3) continue;

        std::string type = tokens[0];
        std::string date = tokens[1];
        std::string notes = tokens[2];

        if (type == "DIET") {
            if (tokens.size() < 8) continue;
            std::string foodName = tokens[3];
            int carbs = std::stoi(tokens[4]);
            int protein = std::stoi(tokens[5]);
            int fat = std::stoi(tokens[6]);
            int calories = std::stoi(tokens[7]);
            regUser->addLog(std::make_shared<DietEntry>(date, notes, foodName, carbs, protein, fat, calories));
        } else if (type == "WORKOUT") {
            if (tokens.size() < 6) continue;
            std::string exerciseType = tokens[3];
            int duration = std::stoi(tokens[4]);
            int caloriesBurned = std::stoi(tokens[5]);
            regUser->addLog(std::make_shared<WorkoutEntry>(date, notes, exerciseType, duration, caloriesBurned));
        }
    }
    file.close();
}

void HealthSystem::loadInventory() {
    inventory.clear();
    std::ifstream file("inventory.txt");

    if (!file.is_open()) {
        // Create default inventory
        std::ofstream outfile("inventory.txt");
        outfile << "LOCKER,L01,Locker #01,true,101,Locker Area A\n";
        outfile << "LOCKER,L02,Locker #02,true,102,Locker Area A\n";
        outfile << "LOCKER,L03,Locker #03,true,103,Locker Area B\n";
        outfile << "EQUIPMENT,E01,Dumbbell 10kg,true,10.0,Excellent\n";
        outfile << "EQUIPMENT,E02,Dumbbell 20kg,true,20.0,Excellent\n";
        outfile << "EQUIPMENT,E03,Yoga Mat,true,0.0,Wear\n";
        outfile.close();

        inventory.push_back(std::make_shared<Locker>("L01", "Locker #01", true, 101, "Locker Area A"));
        inventory.push_back(std::make_shared<Locker>("L02", "Locker #02", true, 102, "Locker Area A"));
        inventory.push_back(std::make_shared<Locker>("L03", "Locker #03", true, 103, "Locker Area B"));
        inventory.push_back(std::make_shared<Equipment>("E01", "Dumbbell 10kg", true, 10.0, "Excellent"));
        inventory.push_back(std::make_shared<Equipment>("E02", "Dumbbell 20kg", true, 20.0, "Excellent"));
        inventory.push_back(std::make_shared<Equipment>("E03", "Yoga Mat", true, 0.0, "Wear"));
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() < 4) continue;

        std::string type = tokens[0];
        std::string id = tokens[1];
        std::string name = tokens[2];
        bool avail = (tokens[3] == "true");

        if (type == "LOCKER") {
            if (tokens.size() < 6) continue;
            int num = std::stoi(tokens[4]);
            std::string loc = tokens[5];
            inventory.push_back(std::make_shared<Locker>(id, name, avail, num, loc));
        } else if (type == "EQUIPMENT") {
            if (tokens.size() < 6) continue;
            double weight = std::stod(tokens[4]);
            std::string cond = tokens[5];
            inventory.push_back(std::make_shared<Equipment>(id, name, avail, weight, cond));
        }
    }
    file.close();
}

void HealthSystem::loadRentals() {
    rentals.clear();
    std::ifstream file("rentals.txt");
    if (!file.is_open()) return; // Ok if empty

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() < 6) continue;

        std::string rentalId = tokens[0];
        std::string username = tokens[1];
        std::string itemId = tokens[2];
        std::string rentDate = tokens[3];
        std::string dueDate = tokens[4];
        bool returned = (tokens[5] == "true");

        rentals.push_back(std::make_shared<RentalRecord>(rentalId, username, itemId, rentDate, dueDate, returned));
    }
    file.close();
}

void HealthSystem::saveUsers() {
    std::ofstream tempFile("temp_users.txt");
    if (!tempFile.is_open()) return;

    for (const auto& pair : users) {
        tempFile << pair.second->serialize() << "\n";
        saveUserLogs(pair.first, pair.second);
    }
    tempFile.close();
    
    // Atomically replace file
    std::remove("users.txt");
    std::rename("temp_users.txt", "users.txt");
}

void HealthSystem::saveUserLogs(const std::string& username, const std::shared_ptr<User>& user) {
    auto regUser = std::dynamic_pointer_cast<RegularUser>(user);
    if (!regUser) return;

    std::string filename = "logs_" + username + ".txt";
    std::ofstream file(filename);
    if (!file.is_open()) return;

    for (const auto& log : regUser->getLogs()) {
        file << log->serialize() << "\n";
    }
    file.close();
}

void HealthSystem::saveInventory() {
    std::ofstream tempFile("temp_inventory.txt");
    if (!tempFile.is_open()) return;

    for (const auto& item : inventory) {
        tempFile << item->serialize() << "\n";
    }
    tempFile.close();
    
    std::remove("inventory.txt");
    std::rename("temp_inventory.txt", "inventory.txt");
}

void HealthSystem::saveRentals() {
    std::ofstream tempFile("temp_rentals.txt");
    if (!tempFile.is_open()) return;

    for (const auto& record : rentals) {
        tempFile << record->serialize() << "\n";
    }
    tempFile.close();

    std::remove("rentals.txt");
    std::rename("temp_rentals.txt", "rentals.txt");
}

bool HealthSystem::registerUser(const std::string& uname, const std::string& pwd, double w, double h, int cal) {
    if (users.find(uname) != users.end()) {
        return false; // User already exists
    }
    
    auto newUser = std::make_shared<RegularUser>(uname, pwd, w, h, cal);
    users[uname] = newUser;
    saveDatabase();
    return true;
}

bool HealthSystem::loginUser(const std::string& uname, const std::string& pwd) {
    auto it = users.find(uname);
    if (it != users.end() && it->second->getPassword() == pwd) {
        currentUser = it->second;
        return true;
    }
    return false;
}

void HealthSystem::logout() {
    saveDatabase();
    currentUser = nullptr;
}

bool HealthSystem::rentItem(const std::string& itemId) {
    if (!currentUser) return false;
    
    // Find item
    auto itemIt = std::find_if(inventory.begin(), inventory.end(), 
        [&itemId](const std::shared_ptr<RentableItem>& item) {
            return item->getItemId() == itemId;
        });

    if (itemIt == inventory.end() || !(*itemIt)->getAvailability()) {
        return false; // Not found or already rented
    }

    (*itemIt)->setAvailability(false);

    // Create rental record
    int newRecordNum = rentals.size() + 1;
    std::stringstream ss;
    ss << "R" << std::setw(4) << std::setfill('0') << newRecordNum;
    std::string rId = ss.str();

    // Default dates
    std::string rentDate = "2026-05-28";
    std::string dueDate = "2026-06-28";

    auto record = std::make_shared<RentalRecord>(rId, currentUser->getUsername(), itemId, rentDate, dueDate, false);
    rentals.push_back(record);

    saveDatabase();
    return true;
}

bool HealthSystem::returnItem(const std::string& itemId) {
    if (!currentUser) return false;

    // Find rental record of this user that is NOT returned
    auto recIt = std::find_if(rentals.begin(), rentals.end(),
        [this, &itemId](const std::shared_ptr<RentalRecord>& rec) {
            return rec->itemId == itemId && !rec->isReturned && 
                   (currentUser->getRole() == UserRole::ADMIN || rec->username == currentUser->getUsername());
        });

    if (recIt == rentals.end()) {
        return false; // No renting record found for this item
    }

    // Find item
    auto itemIt = std::find_if(inventory.begin(), inventory.end(), 
        [&itemId](const std::shared_ptr<RentableItem>& item) {
            return item->getItemId() == itemId;
        });

    if (itemIt != inventory.end()) {
        (*itemIt)->setAvailability(true);
    }

    (*recIt)->isReturned = true;
    saveDatabase();
    return true;
}

void HealthSystem::addInventoryItem(std::shared_ptr<RentableItem> item) {
    inventory.push_back(item);
    saveDatabase();
}

bool HealthSystem::deleteUser(const std::string& username) {
    auto it = users.find(username);
    if (it == users.end() || it->second->getRole() == UserRole::ADMIN) {
        return false; // Can't delete admin or non-existent user
    }
    
    users.erase(it);
    
    // Delete their log file
    std::string logFilename = "logs_" + username + ".txt";
    std::remove(logFilename.c_str());
    
    saveDatabase();
    return true;
}

void HealthSystem::listAllUsers() const {
    std::cout << "\n================= 使用者目錄 =================\n"
              << std::left << std::setw(15) << "使用者名稱" 
              << std::setw(10) << "身分" 
              << std::setw(10) << "體重(kg)" 
              << std::setw(10) << "身高(cm)" 
              << std::setw(15) << "卡路里目標\n"
              << "----------------------------------------------\n";
    
    for (const auto& pair : users) {
        std::string roleStr = (pair.second->getRole() == UserRole::ADMIN) ? "管理者" : "一般使用者";
        auto reg = std::dynamic_pointer_cast<RegularUser>(pair.second);
        
        if (reg) {
            std::cout << std::left << std::setw(15) << reg->getUsername()
                      << std::setw(10) << roleStr
                      << std::setw(10) << reg->getWeight()
                      << std::setw(10) << reg->getHeight()
                      << std::setw(15) << reg->getCalorieTarget() << "\n";
        } else {
            std::cout << std::left << std::setw(15) << pair.second->getUsername()
                      << std::setw(10) << roleStr
                      << std::setw(10) << "-"
                      << std::setw(10) << "-"
                      << std::setw(15) << "-" << "\n";
        }
    }
    std::cout << "==============================================\n";
}

void HealthSystem::listUserLogs(const std::string& username) const {
    auto it = users.find(username);
    if (it == users.end()) {
        std::cout << "找不到該使用者！" << std::endl;
        return;
    }
    
    auto reg = std::dynamic_pointer_cast<RegularUser>(it->second);
    if (!reg) {
        std::cout << "該帳號為管理者，無健康日誌。" << std::endl;
        return;
    }

    std::cout << "\n====== " << username << " 的歷史健康日誌 ======\n";
    if (reg->getLogs().empty()) {
        std::cout << "（尚無任何飲食與運動紀錄）\n";
    } else {
        for (const auto& log : reg->getLogs()) {
            log->displayDetails();
            std::cout << "-------------------------------------\n";
        }
    }
    std::cout << "======================================\n";
}

void HealthSystem::listRentals() const {
    std::cout << "\n================= 全系統租借歷史紀錄 =================\n"
              << std::left << std::setw(10) << "單號" 
              << std::setw(15) << "租借人" 
              << std::setw(10) << "物品ID" 
              << std::setw(15) << "租借日期" 
              << std::setw(15) << "應還日期" 
              << std::setw(10) << "歸還狀態\n"
              << "------------------------------------------------------\n";
    
    for (const auto& rec : rentals) {
        std::cout << std::left << std::setw(10) << rec->rentalId
                  << std::setw(15) << rec->username
                  << std::setw(10) << rec->itemId
                  << std::setw(15) << rec->rentDate
                  << std::setw(15) << rec->dueDate
                  << std::setw(10) << (rec->isReturned ? "已歸還" : "租借中") << "\n";
    }
    std::cout << "======================================================\n";
}

void HealthSystem::modifyUserTarget(const std::string& username, int newTarget) {
    auto it = users.find(username);
    if (it == users.end()) {
        std::cout << "找不到該使用者！" << std::endl;
        return;
    }

    auto reg = std::dynamic_pointer_cast<RegularUser>(it->second);
    if (!reg) {
        std::cout << "無法修改管理者的卡路里目標。" << std::endl;
        return;
    }

    // Since we need to modify weight, height or calorie target, we can either re-create or provide setter
    // To avoid breaking User/RegularUser structures, we re-register or modify using in-memory replacement:
    auto newReg = std::make_shared<RegularUser>(reg->getUsername(), reg->getPassword(), reg->getWeight(), reg->getHeight(), newTarget);
    // Copy their logs over
    for (const auto& log : reg->getLogs()) {
        newReg->addLog(log);
    }
    users[username] = newReg;
    saveDatabase();
    std::cout << "卡路里目標修改成功！" << std::endl;
}
