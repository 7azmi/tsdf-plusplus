// Copyright (c) 2020- Margarita Grinvald, Autonomous Systems Lab, ETH Zurich
// Licensed under the MIT License (see LICENSE for details)

// NOTE: This test requires a full ROS catkin workspace with voxblox and PCL installed.
// It cannot be built standalone. See test/README.md for details.

#include <gtest/gtest.h>

#include "tsdf_plusplus/core/segment.h"

class SegmentTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create a simple point cloud for testing
    pointcloud_.points.resize(5);
    for (size_t i = 0; i < pointcloud_.points.size(); ++i) {
      pointcloud_.points[i].x = static_cast<float>(i);
      pointcloud_.points[i].y = static_cast<float>(i) * 2.0f;
      pointcloud_.points[i].z = static_cast<float>(i) * 3.0f;
      pointcloud_.points[i].r = 255;
      pointcloud_.points[i].g = 128;
      pointcloud_.points[i].b = 64;
      pointcloud_.points[i].a = 255;
      pointcloud_.points[i].semantic_class = 1u;
    }
    
    // Create an identity transformation
    T_G_C_.setIdentity();
  }

  pcl::PointCloud<InputPointType> pointcloud_;
  voxblox::Transformation T_G_C_;
};

TEST_F(SegmentTest, ConstructorConvertsPointcloud) {
  Segment segment(pointcloud_, T_G_C_);
  
  // Check that points were converted
  EXPECT_EQ(segment.points_C_.size(), pointcloud_.points.size());
  EXPECT_EQ(segment.colors_.size(), pointcloud_.points.size());
  EXPECT_EQ(segment.semantic_class_, pointcloud_.points[0].semantic_class);
}

TEST_F(SegmentTest, SegmentStoresTransformation) {
  Segment segment(pointcloud_, T_G_C_);
  
  EXPECT_TRUE(segment.T_G_C_.getTransformationMatrix().isApprox(T_G_C_.getTransformationMatrix()));
}

TEST_F(SegmentTest, SegmentFiltersNonFinitePoints) {
  // Add a non-finite point
  InputPointType nan_point;
  nan_point.x = std::numeric_limits<float>::quiet_NaN();
  nan_point.y = 1.0f;
  nan_point.z = 1.0f;
  nan_point.semantic_class = 1u;
  pointcloud_.points.push_back(nan_point);
  
  Segment segment(pointcloud_, T_G_C_);
  
  // The NaN point should be filtered out
  EXPECT_EQ(segment.points_C_.size(), 5u);
  EXPECT_LT(segment.points_C_.size(), pointcloud_.points.size());
}

TEST_F(SegmentTest, ColorsAreStoredCorrectly) {
  Segment segment(pointcloud_, T_G_C_);
  
  // Check that colors were stored
  ASSERT_GT(segment.colors_.size(), 0u);
  EXPECT_EQ(segment.colors_[0].r, pointcloud_.points[0].r);
  EXPECT_EQ(segment.colors_[0].g, pointcloud_.points[0].g);
  EXPECT_EQ(segment.colors_[0].b, pointcloud_.points[0].b);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
