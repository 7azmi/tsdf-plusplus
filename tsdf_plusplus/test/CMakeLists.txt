cmake_minimum_required(VERSION 3.5)
project(tsdf_plusplus_tests)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the include directory for the main project
include_directories(../include)

# For this standalone test, we'll create a minimal test that doesn't depend on heavy dependencies
# This is just to demonstrate test infrastructure

# Simple test that tests basic C++ functionality
add_executable(test_basic test_basic.cc)
target_link_libraries(test_basic ${GTEST_LIBRARIES} pthread)

# Enable testing
enable_testing()
add_test(NAME BasicTest COMMAND test_basic)

message(STATUS "Test build system configured successfully!")
message(STATUS "Note: Full tests with ROS dependencies require a catkin workspace")
message(STATUS "Run 'make test' or 'ctest' to run the basic test")
