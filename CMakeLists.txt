cmake_minimum_required(VERSION 3.10)

# Project name
project(MatchingEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include nlohmann/json library
include(FetchContent)
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.10.5  # You can use the latest stable version
)

FetchContent_MakeAvailable(nlohmann_json)

# Add the source files
set(SOURCES
    src/matching_engine.cpp
)

# Add the header files
set(HEADERS
    include/matching_engine.h
)

# Add executable
add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADERS})

# Link nlohmann_json library
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Example: You can specify where the main.cpp file is located
# set(SOURCE_DIR src)
# set(MAIN_SOURCE ${SOURCE_DIR}/main.cpp)

# add_executable(${PROJECT_NAME} ${MAIN_SOURCE} ${SOURCES} ${HEADERS})
