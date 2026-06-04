#include "RegularUser.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

double RegularUser::calculateBMI() const {
    if (height <= 0.0) return 0.0;
    double heightMeters = height / 100.0;
    return weight / (heightMeters * heightMeters);
}

void RegularUser::displayMenu() {
    std::cout << "\n  ┌──────────────────────────────────────────────────────────┐\n"
              << "  │  📊 Regular User Dashboard: [ username: " << username << " ]          │\n"
              << "  ├──────────────────────────────────────────────────────────┤\n";
    showDashboard();
    std::cout << "  ├──────────────────────────────────────────────────────────┤\n"
              << "  │  [Menu Options]                                          │\n"
              << "  │     1. Add Diet Log (新增今日飲食記錄)                      │\n"
              << "  │     2. Add Workout Log (新增今日運動健身記錄)               │\n"
              << "  │     3. View Historical Logs (檢視歷史健康日誌)              │\n"
              << "  │     4. Delete Log Entry (刪除記錄)                         │\n"
              << "  │     5. Rent Equipment/Locker (租借健身房器材/置物櫃)         │\n"
              << "  │     6. Return Rented Item (歸還健身房器材/置物櫃)            │\n"
              << "  │     7. View My Rental Status (檢視我的租借狀態)             │\n"
              << "  │     8. Send Feedback (發送建議給管理員)                     │\n"
              << "  │     9. Save Changes & Logout (儲存並登出)                  │\n"
              << "  └──────────────────────────────────────────────────────────┘\n";
}

void RegularUser::showDashboard() {
    // Calculate daily calories (assume for today's logs)
    int dietSum = 0;
    int workoutSum = 0; // Absolute value of burned calories
    
    for (const auto& log : logs) {
        int cal = log->getCalories();
        if (cal > 0) {
            dietSum += cal;
        } else {
            workoutSum += (-cal);
        }
    }
    
    int netCalories = dietSum - workoutSum;
    int remaining = calorieTarget - netCalories;
    
    double percent = 0.0;
    if (calorieTarget > 0) {
        percent = (static_cast<double>(netCalories) / calorieTarget) * 100.0;
    }
    if (percent < 0.0) percent = 0.0;
    
    // Draw progress bar (total 16 blocks)
    int totalBlocks = 16;
    int filledBlocks = static_cast<int>((percent / 100.0) * totalBlocks);
    if (filledBlocks > totalBlocks) filledBlocks = totalBlocks;
    if (filledBlocks < 0) filledBlocks = 0;
    
    std::string bar = "";
    for (int i = 0; i < totalBlocks; ++i) {
        if (i < filledBlocks) bar += "█";
        else bar += "░";
    }
    
    double bmi = calculateBMI();
    std::string bmiStatus = "正常";
    if (bmi < 18.5) bmiStatus = "偏輕";
    else if (bmi >= 24.0) bmiStatus = "過重";
    
    std::cout << "  │  [Today's Status]                                        │\n"
              << "  │  BMI: " << std::fixed << std::setprecision(1) << bmi << " (" << bmiStatus << ")    │  Daily Calorie Target: " << calorieTarget << " kcal   │\n"
              << "  │                                                          │\n"
              << "  │  Calories Intake  : " << std::setw(4) << dietSum << " kcal  [" << bar << "] " << std::setw(3) << static_cast<int>(percent) << "%    │\n"
              << "  │  Calories Burned  : " << std::setw(4) << workoutSum << " kcal                            │\n"
              << "  │  Remaining Budget : " << std::setw(4) << remaining << " kcal                            │\n";
}

std::string RegularUser::serialize() const {
    // Format: REGULAR,username,password,weight,height,calorieTarget
    std::stringstream ss;
    ss << "REGULAR," << username << "," << password << "," << weight << "," << height << "," << calorieTarget;
    return ss.str();
}
