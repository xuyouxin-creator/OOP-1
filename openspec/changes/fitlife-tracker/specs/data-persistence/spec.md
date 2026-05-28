## ADDED Requirements

### Requirement: Load Data on Startup
系統在開機初始化（Startup）時，必須自動讀取 `users.txt`（使用者帳號資料庫）、`inventory.txt`（器材置物櫃資料庫）與 `rentals.txt`（租借交易資料庫）。系統必須使用標準串流解析這些文字檔案，並在記憶體中還原成對應的角色、日誌與租借物件。

#### Scenario: Successful System Initialization
- **WHEN** 系統啟動，且此三份資料庫檔案存在且格式正確時
- **THEN** 系統成功載入所有資料，重建使用者清單與器材租借歷史，並進入登入主選單

#### Scenario: Startup with Missing Files
- **WHEN** 系統啟動，但發現資料庫檔案不存在時
- **THEN** 系統必須自動建立空白的資料庫檔案，並順利進入主選單，不拋出崩潰異常

### Requirement: Save Data on Exit or Change
系統在使用者正常登出（Logout）、管理者儲存系統或主程式安全退出時，必須將記憶體中最新的使用者資料、日誌紀錄與器材租借明細寫回檔案中。寫入時必須採用安全覆寫機制，以確保下次開啟程式時能載入最新的資料。

#### Scenario: Auto Save on Regular Logout
- **WHEN** 使用者在控制台選擇「儲存並登出」功能
- **THEN** 系統將所有更新寫回 `users.txt`, `inventory.txt`, `rentals.txt` 中，確認完成後才結束該使用者的 Session
