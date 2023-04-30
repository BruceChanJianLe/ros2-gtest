#ifndef ROS2_GTEST_STD_MSGS_PUB_HPP
#define ROS2_GTEST_STD_MSGS_PUB_HPP

// STL
#include <memory>

// ROS2
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>

#include "ros2-gtest/constants.hpp"

namespace gtest
{
  class Pub2
  {
  public:
    using Ptr = std::shared_ptr<Pub2>;
    explicit Pub2(rclcpp::Node::SharedPtr n);
    ~Pub2();
    void run();

  private:
    rclcpp::Node::SharedPtr n_;
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr pub_;
    rclcpp::TimerBase::SharedPtr timer_;

    // Variables
    int  rate_;
    bool data_;

    void getParams();
  };

} // namespace gtest

#endif /* ROS2_GTEST_STD_MSGS_PUB_HPP */
