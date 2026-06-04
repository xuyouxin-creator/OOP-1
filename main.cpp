#include <iostream>
#include <string>
#include <memory>
#include <iomanip>
#include <limits>
#ifdef _WIN32
#include <windows.h>
#endif
#include "HealthSystem.h"
#include "RegularUser.h"
#include "AdminUser.h"
#include "DietEntry.h"
#include "WorkoutEntry.h"
#include "Locker.h"
#include "Equipment.h"
#include "UIUtils.h"

// Helper function to safely read integer from console
int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(10000, '\n');
            return value;
        } else {
            std::cout << "錯誤：請輸入有效的整數！\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }
}

// Helper function to safely read double from console
double readDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(10000, '\n');
            return value;
        } else {
            std::cout << "錯誤：請輸入有效的浮點數！\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }
}

// Helper to read string
std::string readString(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

// Wait for user to press any key before returning to menu
void waitForContinueInMenu() {
    std::cout << "\n按任意鍵返回菜單...\n";
    std::cin.ignore(10000, '\n');
}

void handleRegularUserLoop(HealthSystem& system) {
    auto regUser = std::dynamic_pointer_cast<RegularUser>(system.getCurrentUser());
    if (!regUser) return;

    std::vector<std::string> regularUserOptions = {
        "新增飲食記錄 (Add Diet Log)",
        "新增運動日誌 (Add Workout Log)",
        "檢視歷史健康日誌 (View Historical Logs)",
        "刪除記錄 (Delete Log Entry)",
        "租借器材/置物櫃 (Rent Equipment/Locker)",
        "歸還器材/置物櫃 (Return Rented Item)",
        "檢視租借紀錄總覽 (View My Rental Status)",
        "發送建議給管理員 (Send Feedback)",
        "儲存並登出 (Save & Logout)"
    };

    while (true) {
        UIUtils::clearScreen();
        regUser->displayMenu();
        int choice = UIUtils::selectMenu(regularUserOptions);
        
        if (choice == -1) {
            std::cout << "\n按任意鍵返回上一步...\n";
            UIUtils::waitForEnter();
            break;
        }
        
        choice++; // Convert 0-based index to 1-based choice

        if (choice == 9) {
            std::cout << "正在儲存資料並登出...\n";
            system.logout();
            std::cout << "登出成功！\n";
            break;
        }

        switch (choice) {
            case 1: { // Add Diet Log
                std::cout << "\n--- 🍎 新增飲食記錄 ---\n";
                std::string date = readString("請輸入日期 (YYYY-MM-DD): ");
                std::string foodName = readString("請輸入食物名稱: ");
                int carbs = readInt("請輸入碳水化合物 (g): ");
                int protein = readInt("請輸入蛋白質 (g): ");
                int fat = readInt("請輸入脂肪 (g): ");
                int calories = readInt("請輸入熱量 (kcal): ");
                std::string notes = readString("請輸入備註: ");
                
                auto diet = std::make_shared<DietEntry>(date, notes, foodName, carbs, protein, fat, calories);
                regUser->addLog(diet);
                system.saveDatabase();
                std::cout << "✓ 飲食記錄新增成功！\n";
                waitForContinueInMenu();
                break;
            }
            case 2: { // Add Workout Log
                std::cout << "\n--- 🏋️ 新增運動日誌 ---\n";
                std::string date = readString("請輸入日期 (YYYY-MM-DD): ");
                std::string exType = readString("請輸入運動種類/項目: ");
                int duration = readInt("請輸入運動持續時間 (分鐘): ");
                int calBurned = readInt("請輸入燃燒熱量 (kcal): ");
                std::string notes = readString("請輸入備註: ");

                auto workout = std::make_shared<WorkoutEntry>(date, notes, exType, duration, calBurned);
                regUser->addLog(workout);
                system.saveDatabase();
                std::cout << "✓ 運動日誌新增成功！\n";
                waitForContinueInMenu();
                break;
            }
            case 3: { // View Historical Logs
                std::cout << "\n--- 📋 檢視歷史健康日誌 ---\n";
                if (regUser->getLogs().empty()) {
                    std::cout << "（目前尚無歷史紀錄）\n";
                } else {
                    for (int i = 0; i < static_cast<int>(regUser->getLogs().size()); ++i) {
                        std::cout << "[" << (i + 1) << "] ";
                        regUser->getLogs()[i]->displayDetails();
                        std::cout << "--------------------------------------\n";
                    }
                }
                waitForContinueInMenu();
                break;
            }
            case 4: { // Delete Log Entry
                std::cout << "\n--- 🗑️ 刪除記錄 ---\n";
                if (regUser->getLogs().empty()) {
                    std::cout << "（目前尚無歷史紀錄可刪除）\n";
                    break;
                }
                
                std::cout << "您的記錄列表：\n";
                for (int i = 0; i < static_cast<int>(regUser->getLogs().size()); ++i) {
                    std::cout << "[" << (i + 1) << "] ";
                    regUser->getLogs()[i]->displayDetails();
                }
                
                int idx = readInt("請輸入要刪除的記錄編號: ");
                if (regUser->deleteLog(idx - 1)) {
                    system.saveDatabase();
                    std::cout << "✓ 記錄已成功刪除！\n";
                } else {
                    std::cout << "✗ 錯誤：無效的編號！\n";
                }
                waitForContinueInMenu();
                break;
            }
            case 5: { // Rent Equipment/Locker
                std::cout << "\n--- 🔑 租借健身房器材/置物櫃 ---\n";
                std::cout << "可用資產列表：\n";
                bool anyAvail = false;
                for (const auto& item : system.getInventory()) {
                    if (item->getAvailability()) {
                        item->displayInfo();
                        anyAvail = true;
                    }
                }
                
                if (!anyAvail) {
                    std::cout << "（目前健身房無任何閒置可租借的器材/置物櫃）\n";
                    break;
                }

                std::string itemId = readString("請輸入要租借物品的 ID: ");
                if (system.rentItem(itemId)) {
                    std::cout << "✓ 租借成功！物品狀態已更新為已租出。\n";
                } else {
                    std::cout << "❌ 租借失敗！找不到該物品，或該物品已被租走。\n";
                }
                waitForContinueInMenu();
                break;
            }
            case 6: { // Return Rented Item
                std::cout << "\n--- 🔄 歸還健身房器材/置物櫃 ---\n";
                std::cout << "您的租借紀錄：\n";
                bool anyRented = false;
                for (const auto& rec : system.getRentals()) {
                    if (rec->username == regUser->getUsername() && !rec->isReturned) {
                        std::cout << "物品 ID: " << rec->itemId 
                                  << " | 租借單號: " << rec->rentalId 
                                  << " | 應還日期: " << rec->dueDate << "\n";
                        anyRented = true;
                    }
                }

                if (!anyRented) {
                    std::cout << "（您目前沒有任何租借中的物品）\n";
                    break;
                }

                std::string itemId = readString("請輸入欲歸還物品的 ID: ");
                if (system.returnItem(itemId)) {
                    std::cout << "✓ 歸還成功！物品狀態已更新為可用。\n";
                } else {
                    std::cout << "❌ 歸還失敗！您並未承租此物品，或輸入的 ID 錯誤。\n";
                }                waitForContinueInMenu();                break;
            }
            case 7: { // View My Rental Status
                std::cout << "\n--- 📋 我的租借紀錄總覽 ---\n";
                bool anyRecord = false;
                for (const auto& rec : system.getRentals()) {
                    if (rec->username == regUser->getUsername()) {
                        std::cout << "單號: " << rec->rentalId 
                                  << " | 物品 ID: " << rec->itemId 
                                  << " | 租借日: " << rec->rentDate 
                                  << " | 應還日: " << rec->dueDate 
                                  << " | 狀態: " << (rec->isReturned ? "已歸還" : "租借中") << "\n";
                        anyRecord = true;
                    }
                }
                
                if (!anyRecord) {
                    std::cout << "（您尚無任何租借歷史交易紀錄）\n";
                }
                waitForContinueInMenu();
                break;
            }
            case 8: { // Send Feedback
                std::cout << "\n--- 📬 發送建議給管理員 ---\n";
                std::string feedback = readString("請輸入您的建議或意見: ");
                system.submitFeedback(feedback);
                break;
            }
            default:
                std::cout << "無效的選擇，請重新輸入！\n";
        }
    }
}

void handleAdminUserLoop(HealthSystem& system) {
    auto adminUser = std::dynamic_pointer_cast<AdminUser>(system.getCurrentUser());
    if (!adminUser) return;

    std::vector<std::string> adminUserOptions = {
        "列出所有使用者 (List All Users)",
        "查看用戶詳細資訊 (View User Details)",
        "修正用戶熱量目標 (Modify Calorie Targets)",
        "檢視租借紀錄總覽 (View Rental Records)",
        "新增器材/置物櫃 (Add New Asset)",
        "刪除器材/置物櫃 (Delete Asset)",
        "註銷用戶帳戶 (Terminate User Account)",
        "查看使用者反饋 (View User Feedback)",
        "查看特定用戶日誌 (View User Logs)",
        "儲存系統並登出 (Save & Logout)"
    };

    while (true) {
        UIUtils::clearScreen();
        adminUser->displayMenu();
        int choice = UIUtils::selectMenu(adminUserOptions);
        
        if (choice == -1) {
            std::cout << "\n按任意鍵返回上一步...\n";
            UIUtils::waitForEnter();
            break;
        }
        
        choice++; // Convert 0-based index to 1-based choice

        if (choice == 10) {
            std::cout << "正在儲存資料並退出管理系統...\n";
            system.logout();
            std::cout << "管理員登出成功！\n";
            break;
        }

        switch (choice) {
            case 1: { // List All Registered Users
                system.listAllUsers();
                break;
            }
            case 2: { // View User Details
                std::cout << "\n--- 👤 查看使用者詳細資訊 ---\n";
                std::string uname = readString("請輸入使用者名稱: ");
                system.viewUserDetails(uname);
                break;
            }
            case 3: { // Modify User Calorie Targets
                std::cout << "\n--- ⚙️ 修正用戶卡路里目標 ---\n";
                std::string uname = readString("請輸入欲修正的用戶名稱: ");
                int newTarget = readInt("請輸入新的每日卡路里目標值: ");
                system.modifyUserTarget(uname, newTarget);
                break;
            }
            case 4: { // View Rental Records Directory
                system.listRentals();
                break;
            }
            case 5: { // Add New Rentable Asset
                std::cout << "\n--- 🛡️ 新增可租借器材/置物櫃 ---\n";
                std::vector<std::string> assetTypeOptions = {
                    "置物櫃 (Locker)",
                    "健身器材 (Equipment)"
                };
                int assetType = UIUtils::selectMenu(assetTypeOptions);
                
                if (assetType == -1) {
                    std::cout << "\n取消新增資產操作。\n";
                    break;
                }
                
                assetType++; // Convert to 1-based
                
                std::string id = readString("請輸入新資產唯一 ID (如 L04 或 E04): ");
                std::string name = readString("請輸入新資產名稱 (如 VIP Locker 04 或 Dumbbell 30kg): ");
                
                if (assetType == 1) {
                    int lockerNum = readInt("請輸入置物櫃編號 (數字): ");
                    std::string loc = readString("請輸入櫃位區域 (如 Locker Area B): ");
                    auto newLocker = std::make_shared<Locker>(id, name, true, lockerNum, loc);
                    system.addInventoryItem(newLocker);
                    std::cout << "✓ 置物櫃資產新增成功！\n";
                } else if (assetType == 2) {
                    double weight = readDouble("請輸入器材重量 (kg): ");
                    std::string cond = readString("請輸入器材耗損狀態 (如 Excellent, Good, Wear): ");
                    auto newEquip = std::make_shared<Equipment>(id, name, true, weight, cond);
                    system.addInventoryItem(newEquip);
                    std::cout << "✓ 健身器材資產新增成功！\n";
                } else {
                    std::cout << "❌ 無效的資產類別，新增終止。\n";
                }
                break;
            }
            case 6: { // Delete Rentable Asset
                std::cout << "\n--- 🗑️ 刪除器材/置物櫃 ---\n";
                std::cout << "目前庫存清單：\n";
                for (const auto& item : system.getInventory()) {
                    std::cout << "ID: " << item->getItemId() << " - " << item->getItemName() << "\n";
                }
                
                std::string itemId = readString("請輸入要刪除的物品 ID: ");
                if (system.deleteInventoryItem(itemId)) {
                    std::cout << "✓ 器材已成功刪除！\n";
                } else {
                    std::cout << "✗ 錯誤：找不到該物品！\n";
                }
                break;
            }
            case 7: { // Delete User Account
                std::cout << "\n--- ⚠️ 註銷/刪除使用者帳戶 ---\n";
                std::string uname = readString("警告：此操作不可逆！\n請輸入欲永久刪除的使用者名稱: ");
                
                if (system.deleteUser(uname)) {
                    std::cout << "✓ 使用者「" << uname << "」帳戶及相關健康日誌已成功從系統抹除。\n";
                } else {
                    std::cout << "❌ 刪除失敗！找不到該帳戶，或該帳戶是管理員。\n";
                }
                break;
            }
            case 8: { // View User Feedback
                std::cout << "\n--- 📬 查看使用者反饋 ---\n";
                int unreadCount = system.getUnreadFeedbackCount();
                if (unreadCount > 0) {
                    std::cout << "📌 您有 " << unreadCount << " 條未讀反饋！\n\n";
                }
                system.displayAllFeedbacks();
                break;
            }
            case 9: { // View All User Logs (History)
                std::cout << "\n--- 📋 查看特定使用者日誌 ---\n";
                std::string uname = readString("請輸入使用者名稱: ");
                system.listUserLogs(uname);
                break;
            }
            default:
                std::cout << "無效的選擇，請重新輸入！\n";
        }
    }
}

int main() {
#ifdef _WIN32
    // Set console output and input codepage to UTF-8 to prevent garbled Big5/CP950 text on Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    // Set console output to system default (supports UTF-8 encoding locally if supported)
    std::cout << "=== 系統啟動中... ===\n";
    HealthSystem system;
    std::cout << "=== 系統資料庫載入完成！ ===\n";

    std::vector<std::string> mainMenuOptions = {
        "帳戶登入 (Sign In)",
        "註冊新會員 (Register New Member)",
        "安全退出系統 (Exit System)"
    };

    while (true) {
        UIUtils::clearScreen();
        std::cout << "\n  ┌──────────────────────────────────────────────────────────┐\n"
                  << "  │               Welcome to FitLife Tracker v1.0            │\n"
                  << "  ├──────────────────────────────────────────────────────────┤\n"
                  << "  │                                                          │\n"
                  << "  │     💪 健身與營養管理系統 - Fitness & Nutrition Tracker  │\n"
                  << "  │                                                          │\n"
                  << "  └──────────────────────────────────────────────────────────┘\n";
        
        int choice = UIUtils::selectMenu(mainMenuOptions);
        
        if (choice == -1) {
            std::cout << "\n💡 提示：在主菜單中，請選擇一個選項或選擇「安全退出系統」\n";
            continue;
        }
        
        choice++; // Convert 0-based index to 1-based choice

        if (choice == 3) {
            std::cout << "正在安全保存資料庫檔案...\n";
            system.saveDatabase();
            std::cout << "謝謝使用 FitLife Tracker，祝您擁有健康的一天！系統已安全結束。\n";
            break;
        }

        switch (choice) {
            case 1: { // Sign In
                std::cout << "\n--- 🔐 帳戶登入 ---\n";
                std::string uname = readString("請輸入使用者名稱: ");
                std::string pwd = readString("請輸入密碼: ");

                if (system.loginUser(uname, pwd)) {
                    std::cout << "✓ 登入驗證成功！\n";
                    if (system.getCurrentUser()->getRole() == UserRole::REGULAR) {
                        handleRegularUserLoop(system);
                    } else if (system.getCurrentUser()->getRole() == UserRole::ADMIN) {
                        handleAdminUserLoop(system);
                    }
                } else {
                    std::cout << "❌ 登入失敗！使用者名稱或密碼錯誤。\n";
                }
                break;
            }
            case 2: { // Register
                std::cout << "\n--- 📝 註冊新會員 ---\n";
                std::string uname = readString("請輸入欲註冊的使用者名稱: ");
                std::string pwd = readString("請輸入欲設定的密碼: ");
                double weight = readDouble("請輸入您的體重 (kg): ");
                double height = readDouble("請輸入您的身高 (cm): ");
                int target = readInt("請輸入您每日目標卡路里值 (kcal): ");

                if (system.registerUser(uname, pwd, weight, height, target)) {
                    std::cout << "✓ 帳號註冊成功！預設角色為一般使用者，請登入。\n";
                } else {
                    std::cout << "❌ 註冊失敗！該使用者名稱已被註冊，請換一個使用者名稱。\n";
                }
                break;
            }
            default:
                std::cout << "無效的選擇，請重新輸入！\n";
        }
    }

    return 0;
}
