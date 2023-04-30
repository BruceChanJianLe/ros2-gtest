# ROS2 GTest

This repository demonstrates the implementation of using gtest in ROS2.

## Running

```bash
colcon test --event-handlers console_direct+ --packages-select ros2-gtest
# Alternatively, you could use the alias
cct ros2-gtest
```

## References
- https://answers.ros.org/question/402888/passing-parameter-for-launch-testing-in-ros2/
- https://answers.ros.org/question/403008/how-to-provide-parameters-for-test-node-in-launch-testing-using-yaml-file-file/
- https://answers.ros.org/question/360844/ros2-launch_test-gtest-parameters-argument/
- https://github.dev/ros-planning/moveit2/blob/1e1337b46daed0aaa1252b87367c1824f46c9b1a/moveit_ros/moveit_servo/test/unit_test_servo_calcs.cpp