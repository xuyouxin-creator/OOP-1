## 1. Project Infrastructure and CMake Configuration

- [x] 1.1 Create the directory structure: `Users/`, `Logs/`, `Rentals/` and set up empty source files
- [x] 1.2 Write the `CMakeLists.txt` file supporting modular recursive file compilation and install targets
- [x] 1.3 Add a comprehensive `README.md` containing requirements and compilation instructions

## 2. Core Entities and Object-Oriented Hierarchy

- [x] 2.1 Implement `User` base class and derived `RegularUser` and `AdminUser` classes with virtual method stubs
- [x] 2.2 Implement `LogEntry` base class and derived `DietEntry` and `WorkoutEntry` classes for diet/workout tracking
- [x] 2.3 Implement `RentableItem` base class and derived `Locker` and `Equipment` classes for gym inventory
- [x] 2.4 Implement the `RentalRecord` data structure to store individual rental transaction details

## 3. Data Persistence (File I/O)

- [x] 3.1 Implement database text file loading parser in `HealthSystem` for `users.txt` (parsing user credentials and targets)
- [x] 3.2 Implement `inventory.txt` and `rentals.txt` parser in `HealthSystem` to restore items and rental status
- [x] 3.3 Implement the database saving mechanism to safely dump memory structures back to files upon exit

## 4. UI Engine and Session Orchestration

- [x] 4.1 Implement `HealthSystem` login, sign-up, and routing logic
- [x] 4.2 Build `RegularUser` interactive console menu (adding diets, adding workouts, calculating BMI, viewing progress with ASCII progress bar)
- [x] 4.3 Build `AdminUser` console menu (viewing all users, adjusting calorie targets, listing equipment and rental states, adding new assets)
- [x] 4.4 Implement `main.cpp` welcome loops and input validation

## 5. Verification and Compilation Testing

- [x] 5.1 Perform manual login registration and authorization checks in build
- [x] 5.2 Validate file writing and reading durability on system reboot
- [x] 5.3 Verify CMake build success under MSVC / MinGW compiler tools
