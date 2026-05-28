## ADDED Requirements

### Requirement: Rent Item
系統必須允許一般使用者申請租借狀態為可用的健身房器材或置物櫃。租借時必須輸入物品 ID，系統將自動將該物品狀態設為不可用（false），並產生一筆 `RentalRecord` 記錄租借者與應歸還日期。

#### Scenario: Successful Item Rental
- **WHEN** 使用者輸入一個狀態為可用的物品 ID 進行租借
- **THEN** 系統將該物品之 availability 設為不可用，建立對應的 RentalRecord 存入系統，並向使用者顯示租借成功

#### Scenario: Rental Failed Due to Unavailable Item
- **WHEN** 使用者輸入一個已經被他人租借或不可用的物品 ID 進行租借
- **THEN** 系統阻擋該租借請求，並顯示該物品目前無法租借的錯誤訊息

### Requirement: Return Item
系統必須支援將已租借物品歸還的功能。一般使用者或管理員輸入已租物之 ID 辦理歸還時，系統必須將該物品的 availability 重設為可用（true），並將對應的 `RentalRecord` 歸還狀態更新為已歸還（true）。

#### Scenario: Successful Item Return
- **WHEN** 使用者或管理員輸入租借中的物品 ID 辦理歸還
- **THEN** 系統更新物品狀態為可用，並將其 RentalRecord 設為已歸還狀態

### Requirement: Manage Assets
系統必須允許管理者（Admin）全面監控所有器材與置物櫃。管理者必須能夠查看所有租借紀錄（包含誰租了什麼、租借狀態），並能在系統中新增全新的器材或置物櫃。

#### Scenario: Admin Create New Equipment
- **WHEN** 管理者選擇新增器材，輸入器材名稱、重量與品質狀態
- **THEN** 系統產生一個全新的 Equipment 物件並寫入器材庫存列表，供後續會員進行租借
