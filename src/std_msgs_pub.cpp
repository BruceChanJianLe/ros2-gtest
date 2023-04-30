#include "ros2-gtest/std_msgs_pub.hpp"

namespace gtest
{
  Pub2::Pub2(rclcpp::Node::SharedPtr n)
  : n_(n)
  {
    getParams();
    pub_ = n_->create_publisher<std_msgs::msg::Bool>(TOPIC_NAME, 1);
    timer_ = n_->create_wall_timer(
        std::chrono::seconds(rate_),
        [this]()
        {
          this->run();
        }
    );
  }

  Pub2::~Pub2()
  {
  }

  void Pub2::run()
  {
    // Prepare msg
    auto msg = std_msgs::msg::Bool();
    msg.data = data_;

    pub_->publish(msg);

    // Print in terminal
    RCLCPP_INFO_STREAM(n_->get_logger(), "I have spoken " << msg.data << " to Sub2.");
  }

  void Pub2::getParams()
  {
    n_->declare_parameter("rate", rclcpp::ParameterValue(1));
    n_->declare_parameter("data", rclcpp::ParameterValue(true));
    n_->get_parameter("rate", rate_);
    n_->get_parameter("data", data_);
  }
} // namespace gtest