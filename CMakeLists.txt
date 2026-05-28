cmake_minimum_required(VERSION 3.15)
project(FitLifeTracker VERSION 1.0.0 LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Runtime output bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Users
    ${CMAKE_CURRENT_SOURCE_DIR}/Logs
    ${CMAKE_CURRENT_SOURCE_DIR}/Rentals
)

# Collect all header and source files
file(GLOB_RECURSE SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

# Build Target
add_executable(FitLifeTracker ${SRC_FILES})

# Install configuration
install(TARGETS FitLifeTracker
    RUNTIME DESTINATION bin
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/
    DESTINATION bin
    OPTIONAL
)
