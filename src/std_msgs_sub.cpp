#include "ros2-gtest/std_msgs_sub.hpp"

namespace gtest
{
  Sub2::Sub2(rclcpp::Node::SharedPtr n)
  : n_(n)
  {
    sub_ = n_->create_subscription<std_msgs::msg::Bool>(TOPIC_NAME, 1,
                                                        [this](const std_msgs::msg::Bool::SharedPtr msg)
                                                        { this->subCB(msg); });
  }

  Sub2::~Sub2()
  {
  }

  void Sub2::subCB(const std_msgs::msg::Bool::SharedPtr msg)
  {
    RCLCPP_INFO_STREAM(n_->get_logger(), "I hear pub2 says " << msg->data << "!");
    data_ = msg->data;
  }
} // namespace gtest