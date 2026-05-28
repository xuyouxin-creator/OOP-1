#include "AdminUser.h"
#include <iostream>
#include <sstream>

void AdminUser::displayMenu() {
    std::cout << "\n  ┌──────────────────────────────────────────────────────────┐\n"
              << "  │  🛡️ Admin Management Control Center                      │\n"
              << "  ├──────────────────────────────────────────────────────────┤\n";
    showDashboard();
    std::cout << "  ├──────────────────────────────────────────────────────────┤\n"
              << "  │  [Administrative Actions]                                │\n"
              << "  │     1. List All Registered Users (列出所有使用者)         │\n"
              << "  │     2. Modify User Calorie Targets (修正用戶熱量目標)        │\n"
              << "  │     3. View Rental Records Directory (檢視租借紀錄總覽)      │\n"
              << "  │     4. Add New Rentable Asset (新增可租借器材/置物櫃)       │\n"
              << "  │     5. Terminate/Delete User Account (註銷使用者帳戶)       │\n"
              << "  │     6. Save System State & Logout (儲存系統並登出)          │\n"
              << "  └──────────────────────────────────────────────────────────┘\n";
}

void AdminUser::showDashboard() {
    std::cout << "  │  [System Status Overview]                                │\n"
              << "  │  Role: System Administrator (系統管理員)                  │\n"
              << "  │  管理權限: 全面系統配置、器材名冊修訂、使用者註銷權力      │\n";
}

std::string AdminUser::serialize() const {
    // Format: ADMIN,username,password
    std::stringstream ss;
    ss << "ADMIN," << username << "," << password;
    return ss.str();
}
