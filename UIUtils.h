#ifndef UIUTILS_H
#define UIUTILS_H

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#endif

class UIUtils {
public:
    // 清屏
    static void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    // 設置光標位置 (Windows 特定)
    static void setCursorPosition(int x, int y) {
#ifdef _WIN32
        COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#endif
    }

    // 改變文字色彩 (簡化版, Windows)
    static void setTextColor(int color) {
#ifdef _WIN32
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#endif
    }

    // 重置文字色彩
    static void resetTextColor() {
#ifdef _WIN32
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 白色
#endif
    }

    // 菜單選擇 - 上下鍵選擇選項
    // 返回選中的選項索引 (0-based)，按 ESC 返回 -1
    static int selectMenu(const std::vector<std::string>& options) {
        int selected = 0;
        int maxOptions = static_cast<int>(options.size());

        while (true) {
            clearScreen();
            std::cout << "┌─ 請使用 ↑↓ 鍵選擇，按 Enter 確認，ESC 返回 ─┐\n\n";

            // 顯示選項，當前選項反白
            for (int i = 0; i < maxOptions; ++i) {
                if (i == selected) {
                    // 反白顯示
#ifdef _WIN32
                    setTextColor(15 | (1 << 4)); // 白字，黑底背景
#endif
                    std::cout << "  ► " << options[i] << " ◄\n";
                    resetTextColor();
                } else {
                    std::cout << "    " << options[i] << "\n";
                }
            }

            std::cout << "\n└─ W/↑ 上  S/↓ 下  Enter 確認  ESC 返回 ─┘\n";

            // 讀取按鍵
            int key = getKeyInput();

            // 處理上下移動
            if (key == 'W' || key == 'w' || key == 72) { // 72 = 上方向鍵
                selected = (selected - 1 + maxOptions) % maxOptions;
            } else if (key == 'S' || key == 's' || key == 80) { // 80 = 下方向鍵
                selected = (selected + 1) % maxOptions;
            } else if (key == 13) { // 13 = Enter
                return selected;
            } else if (key == 27) { // 27 = ESC
                return -1; // 返回 -1 表示用戶想要返回上一步
            }
        }
    }

    // 獲取按鍵輸入
    static int getKeyInput() {
#ifdef _WIN32
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
        INPUT_RECORD inRec;
        DWORD numRead = 0;

        while (true) {
            ReadConsoleInput(hStdin, &inRec, 1, &numRead);
            if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown) {
                // 檢查特殊鍵（虛擬鍵碼）
                if (inRec.Event.KeyEvent.wVirtualKeyCode == VK_UP) {
                    return 72; // 上鍵
                } else if (inRec.Event.KeyEvent.wVirtualKeyCode == VK_DOWN) {
                    return 80; // 下鍵
                } else if (inRec.Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {
                    return 13; // Enter
                } else if (inRec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
                    return 27; // ESC
                }
                // 檢查普通ASCII字符 (W, S, etc)
                else if (inRec.Event.KeyEvent.uChar.AsciiChar != 0) {
                    return (int)inRec.Event.KeyEvent.uChar.AsciiChar;
                }
            }
        }
#else
        // Linux/Mac 簡化版
        int ch = std::cin.get();
        return ch;
#endif
    }
    // 顯示提示信息
    static void showTip(const std::string& message) {
        std::cout << "\n💡 提示: " << message << "\n";
    }

    // 顯示成功信息
    static void showSuccess(const std::string& message) {
        std::cout << "\n✓ " << message << "\n";
    }

    // 顯示錯誤信息
    static void showError(const std::string& message) {
        std::cout << "\n✗ 錯誤: " << message << "\n";
    }

    // 等待用戶按 Enter
    static void waitForEnter() {
        std::cout << "\n按 Enter 繼續...\n";
        std::cin.ignore(1000, '\n');
    }
};

#endif // UIUTILS_H
