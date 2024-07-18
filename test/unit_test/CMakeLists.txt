# Common variables
set(TEST_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(SRC_DIR  ${CMAKE_CURRENT_SOURCE_DIR})
set(PKG_NAME ${PROJECT_NAME})

# std_msgs_sub_test
set(TEST_FILES
  src/std_msgs_sub_test.cpp
)
ament_add_gtest(std_msgs_sub_test ${TEST_FILES})
target_include_directories(std_msgs_sub_test PUBLIC ../../include)
target_link_libraries(std_msgs_sub_test ${PROJECT_NAME}_lib)

add_ros_test(launch/std_msgs_sub_test.launch.py ARGS
  "TEST_DIR:=${TEST_DIR}"
  "SRC_DIR:=${SRC_DIR}"
  "PKG_NAME:=${PKG_NAME}"
)

# std_msgs_pub_test
set(TEST_FILES
  src/std_msgs_pub_test.cpp
)
ament_add_gtest(std_msgs_pub_test ${TEST_FILES})
target_include_directories(std_msgs_pub_test PUBLIC ../../include)
target_link_libraries(std_msgs_pub_test ${PROJECT_NAME}_lib)

add_ros_test(launch/std_msgs_pub_test.launch.py ARGS
  "TEST_DIR:=${TEST_DIR}"
  "SRC_DIR:=${SRC_DIR}"
  "PKG_NAME:=${PKG_NAME}"
)

# circular buffer unit test
set(TEST_FILES
  ./src/circular_buffer_unit_test.cpp
)
ament_add_gtest(circular_buffer_unit_test ${TEST_FILES})
target_include_directories(circular_buffer_unit_test PUBLIC ../../include)
