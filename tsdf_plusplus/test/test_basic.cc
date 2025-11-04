// Copyright (c) 2020- Margarita Grinvald, Autonomous Systems Lab, ETH Zurich
// Licensed under the MIT License (see LICENSE for details)

#include <gtest/gtest.h>

// Include the actual header file from the project
#include "tsdf_plusplus/core/common.h"

// Basic tests for TSDF++ type system
TEST(BasicTypesTest, ObjectIDSize) {
  // Verify ObjectID is 16-bit
  EXPECT_EQ(sizeof(ObjectID), 2u);
}

TEST(BasicTypesTest, ConfidenceSize) {
  // Verify Confidence is 16-bit
  EXPECT_EQ(sizeof(Confidence), 2u);
}

TEST(BasicTypesTest, SemanticClassSize) {
  // Verify SemanticClass is 8-bit
  EXPECT_EQ(sizeof(SemanticClass), 1u);
}

TEST(BasicTypesTest, EmptyIDValue) {
  EXPECT_EQ(EmptyID, 0u);
}

TEST(BasicTypesTest, BackgroundIDValue) {
  EXPECT_EQ(BackgroundID, 1u);
}

TEST(BasicTypesTest, BackgroundClassValue) {
  EXPECT_EQ(BackgroundClass, 0u);
}

TEST(BasicTypesTest, ObjectIDRange) {
  // Test that ObjectID can hold expected range
  ObjectID max_id = 65535u;
  EXPECT_EQ(max_id, 65535u);
  
  ObjectID min_id = 0u;
  EXPECT_EQ(min_id, 0u);
}

TEST(BasicTypesTest, SemanticClassRange) {
  // Test that SemanticClass can hold expected range
  SemanticClass max_class = 255u;
  EXPECT_EQ(max_class, 255u);
  
  SemanticClass min_class = 0u;
  EXPECT_EQ(min_class, 0u);
}

TEST(BasicStructTest, ObjectDefaultInitialization) {
  Object obj;
  EXPECT_EQ(obj.object_id, 0u);
  EXPECT_EQ(obj.confidence, 0u);
}

TEST(BasicStructTest, ObjectSetValues) {
  Object obj;
  obj.object_id = 42u;
  obj.confidence = 100u;
  
  EXPECT_EQ(obj.object_id, 42u);
  EXPECT_EQ(obj.confidence, 100u);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout << "Running TSDF++ Basic Tests" << std::endl;
  std::cout << "=====================================" << std::endl;
  int result = RUN_ALL_TESTS();
  std::cout << "=====================================" << std::endl;
  if (result == 0) {
    std::cout << "All basic tests passed!" << std::endl;
  } else {
    std::cout << "Some tests failed." << std::endl;
  }
  return result;
}
