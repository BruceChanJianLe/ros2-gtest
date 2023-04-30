#ifndef ROS2_GTEST_STD_MSGS_SUB_HPP
#define ROS2_GTEST_STD_MSGS_SUB_HPP

// STL
#include <memory>

// ROS2
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>

#include "ros2-gtest/constants.hpp"

namespace gtest
{
  class Sub2 
  {
  public:
    using Ptr = std::shared_ptr<Sub2>;
    explicit Sub2(rclcpp::Node::SharedPtr n);
    ~Sub2();
    void subCB(const std_msgs::msg::Bool::SharedPtr msg);
    const bool& getData() const { return data_; };

  private:
    rclcpp::Node::SharedPtr n_;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr sub_;
    bool data_;
  };
} // namespace gtest

#endif /* ROS2_GTEST_STD_MSGS_SUB_HPP */
