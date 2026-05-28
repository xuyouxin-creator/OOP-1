## Why

現有系統缺乏一個結構清晰、模組化且易於擴充的健康與健身管理平台。本專案旨在運用 C++17 物件導向程式設計（OOP）與 CMake 建置工具，開發一個高質量的終端機「FitLife 綜合健身與租借管理系統」，滿足現代 C++ 應用程式開發標準，並做為教學與期末專案的範本。

## What Changes

本專案將引入全新的系統架構，全部採用模組化設計：
- **使用者與管理者機制**：支援 Regular User（一般會員）與 Admin User（系統管理員）雙重角色，並各自擁有專屬的互動式終端機控制台（Console Dashboard）。
- **健身與飲食日誌記錄**：支援登錄每日飲食（卡路里、碳水化合物、蛋白質、脂肪）與運動健身紀錄（運動類型、時間、消耗卡路里），並使用多型（Polymorphism）架構進行管理。
- **器材與置物櫃租借管理**：新增健身房器材與置物櫃租借功能，追蹤租借狀態與逾期資訊。
- **檔案資料庫持久化**：使用文字檔案（如 `users.txt`, `inventory.txt`, `rentals.txt`）實作持久化功能，在程式啟動與關閉時自動載入與儲存資料。
- **專案檔案拆分與 CMake 建置**：所有類別的 `.h` 與 `.cpp` 檔案完全獨立拆分，並透過 `CMakeLists.txt` 管理多目錄編譯，提供完整的安裝與部署流程。

## Capabilities

### New Capabilities
- `user-auth`: 處理使用者與管理者的註冊、登入與權限管理功能。
- `health-logging`: 紀錄與統計每日飲食攝入與健身消耗卡路里，並動態產生每日健康進度條。
- `gym-rentals`: 管理健身器材與置物櫃的租借與歸還紀錄。
- `data-persistence`: 實作檔案讀取與寫入，確保使用者、日誌與租借紀錄在程式重啟後依然存在。

### Modified Capabilities
<!-- 無既存功能 -->

## Impact

本變更將建立全新的 C++ 專案目錄結構與相關文字檔案：
- **原始碼目錄**：`main.cpp`, `HealthSystem.h/.cpp`, `Users/`, `Logs/`, `Rentals/`。
- **建置與文檔**：`CMakeLists.txt`, `README.md`。
- **持久化資料庫檔案**：`users.txt`, `inventory.txt`, `rentals.txt`。
- **其他影響**：無既存代碼受影響，此為全新建構的專案。
