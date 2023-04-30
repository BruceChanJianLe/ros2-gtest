#include <gtest/gtest.h>
#include "ros2-gtest/std_msgs_pub.hpp"

// Take in argc and argv if you want to get_parameters for node
class RclCppFixture
{
public:
  RclCppFixture(int a, char** v) { rclcpp::init(a, v); }
  RclCppFixture() { rclcpp::init(0, nullptr); }
  ~RclCppFixture() { rclcpp::shutdown(); }
};

struct Pub2TestFixture : public ::testing::Test
{
  Pub2TestFixture() : node_{nullptr}, pub2{nullptr}, data_{false} {}
  virtual ~Pub2TestFixture() = default;

  rclcpp::Node::SharedPtr node_;
  gtest::Pub2::Ptr pub2;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr sub_;
  bool data_;
  std::thread spinner_;

protected:
  virtual void SetUp() override
  {
    node_ = std::make_shared<rclcpp::Node>("pub2_test_node");
    pub2 = std::make_shared<gtest::Pub2>(node_);
    sub_ = node_->create_subscription<std_msgs::msg::Bool>(
        gtest::TOPIC_NAME, 1,
        [this](const std_msgs::msg::Bool::SharedPtr msg)
        {
          RCLCPP_INFO_STREAM(this->node_->get_logger(), "I hear pub2 says " << msg->data << "!");
          this->data_ = msg->data;
        });
      spinner_ = std::thread([this](){ rclcpp::spin(this->node_); });
  }

  virtual void TearDown() override
  {
    ;
  }
};

TEST_F(Pub2TestFixture, publishTrue)
{
  std::this_thread::sleep_for(std::chrono::milliseconds {2000});
  ASSERT_TRUE(data_);
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  // Initialize ROS2
  RclCppFixture g_rclcppfixture(argc, argv);
  return RUN_ALL_TESTS();
}
