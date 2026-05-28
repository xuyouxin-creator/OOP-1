#ifndef USER_H
#define USER_H

#include <string>
#include <memory>

enum class UserRole {
    REGULAR,
    ADMIN
};

class User {
protected:
    std::string username;
    std::string password;
    UserRole role;

public:
    User(const std::string& uname, const std::string& pwd, UserRole r)
        : username(uname), password(pwd), role(r) {}
    
    virtual ~User() = default;

    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    UserRole getRole() const { return role; }

    virtual void displayMenu() = 0;
    virtual void showDashboard() = 0;
    virtual std::string serialize() const = 0;
};

#endif // USER_H
