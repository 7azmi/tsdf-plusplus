cmake_minimum_required(VERSION 3.5)
project(tsdf_plusplus_tests)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Find PCL (required for common.h)
find_package(PCL QUIET COMPONENTS common)

# Add the include directory for the main project
include_directories(../include)

if(PCL_FOUND)
  include_directories(${PCL_INCLUDE_DIRS})
  message(STATUS "PCL found - can build tests with PCL dependencies")
else()
  message(WARNING "PCL not found - some tests may not compile")
endif()

# Simple test that tests basic types from common.h
add_executable(test_basic test_basic.cc)
target_link_libraries(test_basic ${GTEST_LIBRARIES} pthread)
if(PCL_FOUND)
  target_link_libraries(test_basic ${PCL_LIBRARIES})
endif()

# Enable testing
enable_testing()
add_test(NAME BasicTest COMMAND test_basic)

message(STATUS "Test build system configured successfully!")
message(STATUS "Note: Full tests with ROS dependencies require a catkin workspace")
message(STATUS "Run 'make test' or 'ctest' to run the basic test")
