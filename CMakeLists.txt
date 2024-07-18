cmake_minimum_required(VERSION 3.8)
project(ros2-gtest)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(std_msgs REQUIRED)

# BUILD
set(dependencies
  rclcpp
  rclpy
  rclcpp_lifecycle
  std_msgs
)

add_executable(sub2_node
  src/std_msgs_sub_node.cpp
  src/std_msgs_sub.cpp
)
target_include_directories(sub2_node PUBLIC include)
ament_target_dependencies(sub2_node ${dependencies})

add_executable(pub2_node
  src/std_msgs_pub_node.cpp
  src/std_msgs_pub.cpp
)
target_include_directories(pub2_node PUBLIC include)
ament_target_dependencies(pub2_node ${dependencies})

add_library(${PROJECT_NAME}_lib
  src/std_msgs_pub.cpp
  src/std_msgs_sub.cpp
)
target_include_directories(${PROJECT_NAME}_lib PUBLIC include)
ament_target_dependencies(${PROJECT_NAME}_lib ${dependencies})

# INSTALL
install(TARGETS
  sub2_node
  pub2_node
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  config
  DESTINATION share/${PROJECT_NAME}/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  find_package(ament_cmake_gtest REQUIRED)
  find_package(ros_testing REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)

  add_subdirectory(test)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
