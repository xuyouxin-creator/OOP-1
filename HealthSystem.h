#ifndef HEALTHSYSTEM_H
#define HEALTHSYSTEM_H

#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include "User.h"
#include "RentableItem.h"
#include "RentalRecord.h"
#include "Feedback.h"

class HealthSystem {
private:
    std::unordered_map<std::string, std::shared_ptr<User>> users;
    std::vector<std::shared_ptr<RentableItem>> inventory;
    std::vector<std::shared_ptr<RentalRecord>> rentals;
    std::vector<Feedback> feedbacks;
    std::shared_ptr<User> currentUser;

    // Helper functions for CSV parsing
    std::vector<std::string> split(const std::string& s, char delimiter);
    void loadUsers();
    void loadInventory();
    void loadRentals();
    void loadFeedbacks();
    void loadUserLogs(const std::string& username, const std::shared_ptr<User>& user);

    void saveUsers();
    void saveInventory();
    void saveRentals();
    void saveFeedbacks();
    void saveUserLogs(const std::string& username, const std::shared_ptr<User>& user);

public:
    HealthSystem();
    ~HealthSystem() { saveDatabase(); }

    bool loadDatabase();
    bool saveDatabase();

    bool registerUser(const std::string& uname, const std::string& pwd, double w, double h, int cal);
    bool loginUser(const std::string& uname, const std::string& pwd);
    void logout();

    std::shared_ptr<User> getCurrentUser() const { return currentUser; }
    
    // Rental features
    const std::vector<std::shared_ptr<RentableItem>>& getInventory() const { return inventory; }
    const std::vector<std::shared_ptr<RentalRecord>>& getRentals() const { return rentals; }
    bool rentItem(const std::string& itemId);
    bool returnItem(const std::string& itemId);
    void addInventoryItem(std::shared_ptr<RentableItem> item);
    bool deleteInventoryItem(const std::string& itemId);
    bool deleteUser(const std::string& username);

    // List helpers for admin
    void listAllUsers() const;
    void listUserLogs(const std::string& username) const;
    void listRentals() const;
    void modifyUserTarget(const std::string& username, int newTarget);
    void viewUserDetails(const std::string& username) const;
    
    // Feedback features
    void submitFeedback(const std::string& message);
    const std::vector<Feedback>& getAllFeedbacks() const { return feedbacks; }
    void displayAllFeedbacks();
    void markFeedbackAsRead(int index);
    int getUnreadFeedbackCount() const;
};

#endif // HEALTHSYSTEM_H
