#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>

class Feedback {
private:
    std::string fromUser;
    std::string message;
    std::string timestamp;
    bool isRead;

public:
    Feedback(const std::string& from, const std::string& msg)
        : fromUser(from), message(msg), isRead(false) {
        // 生成時間戳
        auto now = std::time(nullptr);
        auto tm = std::localtime(&now);
        std::ostringstream oss;
        oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
        timestamp = oss.str();
    }

    // 從 CSV 行解析反饋
    Feedback(const std::string& csvLine) {
        std::vector<std::string> parts;
        std::stringstream ss(csvLine);
        std::string item;
        
        // 簡單 CSV 解析 (假設沒有逗號在反饋內容中)
        int count = 0;
        std::string remaining = csvLine;
        size_t pos = 0;
        
        // 提取用戶名
        pos = remaining.find(',');
        if (pos != std::string::npos) {
            fromUser = remaining.substr(0, pos);
            remaining = remaining.substr(pos + 1);
        }
        
        // 提取時間戳
        pos = remaining.find(',');
        if (pos != std::string::npos) {
            timestamp = remaining.substr(0, pos);
            remaining = remaining.substr(pos + 1);
        }
        
        // 提取是否已讀
        pos = remaining.find(',');
        if (pos != std::string::npos) {
            isRead = (remaining.substr(0, pos) == "1");
            message = remaining.substr(pos + 1);
        }
    }

    std::string getFromUser() const { return fromUser; }
    std::string getMessage() const { return message; }
    std::string getTimestamp() const { return timestamp; }
    bool getIsRead() const { return isRead; }
    
    void markAsRead() { isRead = true; }

    // 轉換為 CSV 格式
    std::string serialize() const {
        return fromUser + "," + timestamp + "," + (isRead ? "1" : "0") + "," + message;
    }
};

#endif // FEEDBACK_H
