# 📊 FitLife Tracker - 健身與飲食租借綜合管理系統

一個使用現代 C++17 編寫的終端機健康日誌與健身房設備租借系統。支援使用者與管理者雙重權限機制，並具備完整的檔案資料庫持久化功能。

---

## 🛠️ 系統需求與準備工作 (Windows)

在編譯本專案之前，請確保您的 Windows 系統已安裝以下工具：

1. **C++ 編譯器** (支援 C++17 以上)
   * 建議安裝 **Visual Studio 2019 / 2022** (勾選「使用 C++ 的桌面開發」)
   * 或使用 **MinGW-w64** (例如經由 MSYS2 或 w64devkit 安裝)
2. **CMake** (v3.15 或更新版本)
   * [CMake 官方下載連結](https://cmake.org/download/) (請確保在安裝時勾選 "Add CMake to the system PATH")

---

## 🚀 編譯與建置步驟 (Build Steps)

我們建議使用「非侵入式建置 (Out-of-source Build)」，將編譯產生的暫存檔與原始碼完全分離。

打開 Windows Powershell 或命令提示字元 (cmd)，進入專案根目錄並依序執行以下指令：

### 1. 建立並進入建置資料夾
```bash
mkdir build
cd build
```

### 2. 進行專案設定 (Configure)
根據您使用的編譯器，選擇以下**其中一種**指令進行設定：

* **選項 A：使用 Visual Studio (MSVC) 編譯器 (預設且推薦)**
  ```bash
  cmake ..
  ```
* **選項 B：使用 MinGW (GCC) 編譯器**
  ```bash
  cmake -G "MinGW Makefiles" ..
  ```

### 3. 開始編譯 (Build)
使用 CMake 統一的編譯命令，它會自動呼叫對應的編譯器進行編譯：
```bash
cmake --build . --config Release
```
*編譯完成後，執行檔將會產生在 `build/bin/Release/FitLifeTracker.exe` (MSVC) 或 `build/bin/FitLifeTracker.exe` (MinGW)。*

---

## 📦 安裝與部署步驟 (Install & Deployment)

為了讓程式與其所需的資料庫檔案（`users.txt` 等）處於同一個目錄並能正常運作，我們可以使用 CMake 的安裝功能，將它們部署到一個乾淨的獨立資料夾中。

在 `build` 目錄下執行以下指令：

```bash
# 將專案安裝至 build/dist 資料夾中
cmake --install . --prefix ./dist
```

### 📂 安裝後的目錄結構
安裝完成後，`build/dist/` 目錄將會是您的**發布版本**，結構如下：
```text
dist/
└── bin/
    ├── FitLifeTracker.exe    # 主執行檔
    ├── users.txt             # 使用者資料庫
    ├── inventory.txt         # 器材清單資料庫
    └── rentals.txt           # 租借紀錄資料庫
```

---

## 🏃 執行程式 (Run)

請切換進入安裝後的 `bin` 目錄下執行程式，以確保資料庫檔案能正確被讀取與寫入：

```bash
cd dist/bin
.\FitLifeTracker.exe
```
