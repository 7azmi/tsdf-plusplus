// Copyright (c) 2020- Margarita Grinvald, Autonomous Systems Lab, ETH Zurich
// Licensed under the MIT License (see LICENSE for details)

// NOTE: This test requires a full ROS catkin workspace with voxblox installed.
// It cannot be built standalone. See test/README.md for details.

#include <gtest/gtest.h>

#include "tsdf_plusplus/core/object_volume.h"

class ObjectVolumeTest : public ::testing::Test {
 protected:
  void SetUp() override {
    voxel_size_ = 0.1f;
    voxels_per_side_ = 16u;
    centroid_ = voxblox::Point(1.0f, 2.0f, 3.0f);
    semantic_class_ = 1u;
  }

  float voxel_size_;
  size_t voxels_per_side_;
  voxblox::Point centroid_;
  SemanticClass semantic_class_;
};

TEST_F(ObjectVolumeTest, ConstructorInitializesCorrectly) {
  ObjectVolume volume(voxel_size_, voxels_per_side_, centroid_, semantic_class_);
  
  EXPECT_EQ(volume.getSemanticClass(), semantic_class_);
  EXPECT_NE(volume.getTsdfLayerPtr(), nullptr);
}

TEST_F(ObjectVolumeTest, SetSemanticClassUpdatesValue) {
  ObjectVolume volume(voxel_size_, voxels_per_side_, centroid_, semantic_class_);
  
  SemanticClass new_class = 2u;
  volume.setSemanticClass(new_class);
  
  EXPECT_EQ(volume.getSemanticClass(), new_class);
}

TEST_F(ObjectVolumeTest, AllocateStorageAndGetBlockPtrReturnsValidBlock) {
  ObjectVolume volume(voxel_size_, voxels_per_side_, centroid_, semantic_class_);
  
  voxblox::BlockIndex block_idx(0, 0, 0);
  voxblox::Block<voxblox::TsdfVoxel>::Ptr block = volume.allocateStorageAndGetBlockPtr(block_idx);
  
  ASSERT_NE(block, nullptr);
}

TEST_F(ObjectVolumeTest, UpdateLayerWithStoredBlocksMergesTemporaryBlocks) {
  ObjectVolume volume(voxel_size_, voxels_per_side_, centroid_, semantic_class_);
  
  voxblox::BlockIndex block_idx(0, 0, 0);
  voxblox::Block<voxblox::TsdfVoxel>::Ptr block = volume.allocateStorageAndGetBlockPtr(block_idx);
  
  // This should merge the temporary block into the layer
  volume.updateLayerWithStoredBlocks();
  
  // After merging, the layer should contain the block
  EXPECT_NE(volume.getTsdfLayerPtr(), nullptr);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
