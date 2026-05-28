#ifndef ADMINUSER_H
#define ADMINUSER_H

#include "User.h"

class AdminUser : public User {
public:
    AdminUser(const std::string& uname, const std::string& pwd)
        : User(uname, pwd, UserRole::ADMIN) {}

    void displayMenu() override;
    void showDashboard() override;
    std::string serialize() const override;
};

#endif // ADMINUSER_H
