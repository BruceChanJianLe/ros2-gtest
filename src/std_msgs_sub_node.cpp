#include <rclcpp/rclcpp.hpp>
#include "ros2-gtest/std_msgs_sub.hpp"

int main(int argc, char const *argv[])
{
  rclcpp::init(argc, argv);

  auto n = std::make_shared<rclcpp::Node>(gtest::SUB_NODE_NAME);
  auto node = gtest::Sub2(n);
  rclcpp::spin(n);

  return 0;
}
