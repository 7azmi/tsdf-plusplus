// Copyright (c) 2020- Margarita Grinvald, Autonomous Systems Lab, ETH Zurich
// Licensed under the MIT License (see LICENSE for details)

#include <gtest/gtest.h>

#include "tsdf_plusplus/core/map.h"

class MapTest : public ::testing::Test {
 protected:
  void SetUp() override {
    config_.voxel_size = 0.1f;
    config_.voxels_per_side = 16u;
  }

  Map::Config config_;
};

TEST_F(MapTest, ConstructorInitializesCorrectly) {
  Map map(config_);
  
  EXPECT_FLOAT_EQ(map.block_size(), config_.voxel_size * config_.voxels_per_side);
  EXPECT_NE(map.getMapLayerPtr(), nullptr);
  EXPECT_NE(map.getHighestObjectIdPtr(), nullptr);
  EXPECT_EQ(*map.getHighestObjectIdPtr(), 0u);
}

TEST_F(MapTest, AllocateObjectVolumeCreatesNewVolume) {
  Map map(config_);
  
  voxblox::Point centroid(1.0f, 2.0f, 3.0f);
  SemanticClass semantic_class = 1u;
  ObjectID object_id = 1u;
  
  ObjectVolume* volume = map.allocateObjectVolumePtrById(centroid, semantic_class, object_id);
  
  ASSERT_NE(volume, nullptr);
  EXPECT_EQ(volume->getSemanticClass(), semantic_class);
}

TEST_F(MapTest, GetObjectVolumeReturnsNullForNonExistentVolume) {
  Map map(config_);
  
  ObjectID non_existent_id = 999u;
  ObjectVolume* volume = map.getObjectVolumePtrById(non_existent_id);
  
  EXPECT_EQ(volume, nullptr);
}

TEST_F(MapTest, GetObjectVolumeReturnsExistingVolume) {
  Map map(config_);
  
  voxblox::Point centroid(1.0f, 2.0f, 3.0f);
  SemanticClass semantic_class = 1u;
  ObjectID object_id = 1u;
  
  ObjectVolume* allocated_volume = map.allocateObjectVolumePtrById(centroid, semantic_class, object_id);
  ObjectVolume* retrieved_volume = map.getObjectVolumePtrById(object_id);
  
  EXPECT_EQ(allocated_volume, retrieved_volume);
}

TEST_F(MapTest, AllocateSameObjectIdReturnsSameVolume) {
  Map map(config_);
  
  voxblox::Point centroid(1.0f, 2.0f, 3.0f);
  SemanticClass semantic_class = 1u;
  ObjectID object_id = 1u;
  
  ObjectVolume* volume1 = map.allocateObjectVolumePtrById(centroid, semantic_class, object_id);
  ObjectVolume* volume2 = map.allocateObjectVolumePtrById(centroid, semantic_class, object_id);
  
  EXPECT_EQ(volume1, volume2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
