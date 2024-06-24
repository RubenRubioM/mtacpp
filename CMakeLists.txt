cmake_minimum_required(VERSION 3.28)

# Set the project name
project(mtacpp)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compiler flags
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# Add the main application
add_executable(${PROJECT_NAME} src/main.cpp)

# Include header files
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Add Catch2 testing
# Assuming Catch2 is added as a submodule or installed in the system
# If Catch2 is a submodule in `external` directory
# add_subdirectory(external/Catch2)
# include_directories(external/Catch2/single_include)

# Add the test executable
# add_executable(tests test/test_main.cpp)
# target_link_libraries(tests Catch2::Catch2)

# Include header files in tests
# target_include_directories(tests PRIVATE include)

# Enable CTest framework
# enable_testing()
# add_test(NAME MyTests COMMAND tests)
