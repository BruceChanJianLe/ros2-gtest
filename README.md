# ROS2 GTest

This repository demonstrates the implementation of using gtest in ROS2.

The available examples are as follow:
- [x] rclcpp node test 
- [ ] rclcpp lifecycle node test
- [ ] component node test

## Running

For all launch.py tests with color
```bash
# For all launch.py tests with color
GTEST_COLOR=1 colcon test --event-handlers console_direct+ --ctest-args -R "launch.py" --packages-select ros2-gtest
# options: console_cohesion+  console_package_list+  console_stderr-  console_direct+  console_start_end-
# Alternatively, you could use the alias (https://github.com/BruceChanJianLe/dotfiles/blob/6b69476a06e7e2858ecd269b9e8a07e91624d66c/.bash_aliases#L43)
cct ros2-gtest
```

For circular buffer unit test
```bash
GTEST_COLOR=1 colcon test --event-handlers console_direct+ --ctest-args -R "circular_buffer" --packages-select ros2-gtest
```

## References
- https://answers.ros.org/question/402888/passing-parameter-for-launch-testing-in-ros2/
- https://answers.ros.org/question/403008/how-to-provide-parameters-for-test-node-in-launch-testing-using-yaml-file-file/
- https://answers.ros.org/question/360844/ros2-launch_test-gtest-parameters-argument/
- https://github.dev/ros-planning/moveit2/blob/1e1337b46daed0aaa1252b87367c1824f46c9b1a/moveit_ros/moveit_servo/test/unit_test_servo_calcs.cpp
