# TSDF++ Tests

This directory contains unit tests for the TSDF++ library.

## Test Infrastructure

The test infrastructure uses Google Test (GTest) framework for C++ unit testing.

## Available Tests

### Basic Tests (test_basic.cc)
- Tests fundamental type definitions used in TSDF++
- Validates ObjectID, Confidence, and SemanticClass types
- Verifies constant values (EmptyID, BackgroundID, BackgroundClass)
- Tests Object struct initialization and manipulation

### Full Integration Tests
The following tests require a full ROS catkin workspace with all dependencies:
- **test_map.cc**: Tests for the Map class
- **test_object_volume.cc**: Tests for the ObjectVolume class
- **test_segment.cc**: Tests for the Segment class

## Building and Running Tests

### Standalone Tests (No ROS Required)

The basic tests can be built and run without a full ROS installation:

```bash
cd test
mkdir -p build
cd build
cmake ..
make
```

Run the tests:
```bash
# Run tests directly
./test_basic

# Or use ctest
ctest --verbose
```

### Full Tests with ROS Catkin

To run the full test suite with all ROS dependencies, build within a catkin workspace:

```bash
cd $CATKIN_WS
catkin build tsdf_plusplus --catkin-make-args run_tests
```

Or:
```bash
cd $CATKIN_WS
catkin build tsdf_plusplus
catkin_test_results
```

## Prerequisites

### For Standalone Tests
- CMake 3.5+
- GTest library
- C++14 compatible compiler

Install dependencies on Ubuntu:
```bash
sudo apt-get update
sudo apt-get install cmake build-essential libgtest-dev
```

### For Full ROS Tests
- Complete ROS installation (kinetic/melodic/noetic)
- All TSDF++ dependencies (see main README.md)
- catkin build tools

## Test Coverage

Current test coverage includes:
- ✓ Basic type system validation
- ✓ Object struct functionality
- ○ Map class (requires ROS dependencies)
- ○ ObjectVolume class (requires ROS dependencies)
- ○ Segment class (requires ROS dependencies)

## Adding New Tests

To add new tests:

1. Create a new test file: `test_<feature>.cc`
2. Include GTest headers: `#include <gtest/gtest.h>`
3. Write test cases using `TEST()` or `TEST_F()` macros
4. Add main function with `RUN_ALL_TESTS()`
5. Update CMakeLists.txt to build the new test

Example:
```cpp
#include <gtest/gtest.h>

TEST(MyFeatureTest, BasicFunctionality) {
  // Test code here
  EXPECT_EQ(1 + 1, 2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
```

## Continuous Integration

Tests should be run before committing changes to ensure code quality and prevent regressions.

## License

Tests are provided under the same MIT License as the main TSDF++ project.
