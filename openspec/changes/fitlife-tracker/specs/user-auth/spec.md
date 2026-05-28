## ADDED Requirements

### Requirement: User Registration
系統必須允許新使用者註冊帳號。註冊時，使用者必須提供唯一的使用者名稱（Username）、密碼（Password）、體重（Weight）、身高（Height）與每日卡路里目標值。註冊成功後，帳號角色預設為一般使用者（Regular User）。

#### Scenario: Successful Registration
- **WHEN** 使用者選擇註冊功能，輸入不存在的用戶名與其他基本資訊並送出
- **THEN** 系統建立該新使用者物件，提示註冊成功，並允許其登入

#### Scenario: Registration with Existing Username
- **WHEN** 使用者輸入已存在的使用者名稱進行註冊
- **THEN** 系統阻擋該次註冊，顯示錯誤提示，並要求使用者更換使用者名稱

### Requirement: User and Admin Login
系統必須依據輸入的帳號密碼進行身分驗證。登入成功後，系統必須根據該帳號的角色屬性（Regular 或 Admin）引導至對應的控制台介面。

#### Scenario: Regular User Successful Login
- **WHEN** 一般使用者輸入正確的帳密進行登入
- **THEN** 系統驗證成功，並載入該使用者專屬的健康與飲食控制台介面

#### Scenario: Admin User Successful Login
- **WHEN** 管理者輸入正確的帳密進行登入
- **THEN** 系統驗證成功，並載入管理者專屬的健身房行政監控中心介面

#### Scenario: Failed Login with Invalid Credentials
- **WHEN** 使用者輸入錯誤的帳號或密碼進行登入
- **THEN** 系統驗證失敗，顯示錯誤提示，並返回登入選單
