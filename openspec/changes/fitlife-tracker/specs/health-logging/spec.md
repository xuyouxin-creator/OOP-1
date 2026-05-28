## ADDED Requirements

### Requirement: Log Diet Entry
系統必須允許一般使用者新增飲食記錄。每次飲食記錄必須包含食物名稱、碳水化合物、蛋白質、脂肪以及攝入的卡路里數值。這些資訊會儲存為 `DietEntry` 物件並關聯至當前使用者。

#### Scenario: Successfully Add Diet Log
- **WHEN** 使用者輸入食物名稱、營養成分與卡路里數值並儲存
- **THEN** 系統將該筆 DietEntry 加入當前使用者的日誌清單，並更新當日卡路里統計

### Requirement: Log Workout Entry
系統必須允許一般使用者新增健身運動記錄。運動記錄必須包含運動名稱、持續時間（分鐘）、運動類型以及消耗的卡路里數值。這些資訊會儲存為 `WorkoutEntry` 物件並關聯至當前使用者。

#### Scenario: Successfully Add Workout Log
- **WHEN** 使用者輸入運動名稱、持續時間與卡路里消耗數值並儲存
- **THEN** 系統將該筆 WorkoutEntry 加入當前使用者的日誌清單，並自當日淨卡路里累計中扣除對應的卡路里

### Requirement: Daily Summary and Progress Bar
系統必須能夠統計使用者當天的淨卡路里（攝入卡路里 - 消耗卡路里），並將其與使用者的每日目標卡路里進行比對，以百分比與動態 ASCII 進度條（如 `[████░░░░]`）的形式呈現在一般使用者控制台上。

#### Scenario: Display Progress Summary
- **WHEN** 一般使用者進入控制台主畫面時
- **THEN** 系統計算當日總攝入、總消耗卡路里，並動態繪製對應比例的 ASCII 進度條與顯示剩餘卡路里額度
