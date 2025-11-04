cmake_minimum_required(VERSION 2.8.3)
project(tsdf_plusplus)

find_package(catkin_simple REQUIRED)
catkin_simple(ALL_DEPS_REQUIRED)

cs_add_library(${PROJECT_NAME}
  src/alignment/icp.cc
  src/core/object_volume.cc
  src/core/map.cc
  src/core/segment.cc
  src/integrator/integrator.cc
  src/mesh/color_map.cc
  src/mesh/mesh_integrator.cc
  src/visualizer/visualizer.cc
)

cs_install()
cs_export()

# Testing
if(CATKIN_ENABLE_TESTING)
  find_package(GTest REQUIRED)
  include_directories(${GTEST_INCLUDE_DIRS})

  catkin_add_gtest(test_map
    test/test_map.cc
  )
  target_link_libraries(test_map
    ${PROJECT_NAME}
    ${catkin_LIBRARIES}
    ${GTEST_LIBRARIES}
  )

  catkin_add_gtest(test_object_volume
    test/test_object_volume.cc
  )
  target_link_libraries(test_object_volume
    ${PROJECT_NAME}
    ${catkin_LIBRARIES}
    ${GTEST_LIBRARIES}
  )

  catkin_add_gtest(test_segment
    test/test_segment.cc
  )
  target_link_libraries(test_segment
    ${PROJECT_NAME}
    ${catkin_LIBRARIES}
    ${GTEST_LIBRARIES}
  )
endif()
