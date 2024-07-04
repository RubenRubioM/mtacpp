cmake_minimum_required(VERSION 3.28)

# Set the project name
project(mtacpp)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compiler flags
add_compile_options(-Wall -Wextra -Wpedantic)


# Clang tidy
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "-checks=-*,modernize-*,clang-analyzer-,cppcoreguidelines-,bugprone-")
# Add the main application
add_executable(${PROJECT_NAME} src/main.cpp)

# Add pthread
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)

# Include header files
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Add Catch2 testing
add_subdirectory(external/Catch2)

# These tests can use the Catch2-provided main
add_executable(tests test/test_timer.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

enable_testing()
add_test(NAME MyTests COMMAND tests)

# Setting clang tidy to mta
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
