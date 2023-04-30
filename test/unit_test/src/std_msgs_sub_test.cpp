#include <gtest/gtest.h>
#include "ros2-gtest/std_msgs_sub.hpp"

// Take in argc and argv if you want to get_parameters for node
class RclCppFixture
{
public:
  RclCppFixture(int a, char** v) { rclcpp::init(a, v); }
  RclCppFixture() { rclcpp::init(0, nullptr); }
  ~RclCppFixture() { rclcpp::shutdown(); }
};

struct Sub2TestFixture : public ::testing::Test
{
  Sub2TestFixture() : node_{nullptr}, sub2{nullptr} {}
  virtual ~Sub2TestFixture() = default;

  rclcpp::Node::SharedPtr node_;
  gtest::Sub2::Ptr sub2;
  protected:
    virtual void SetUp() override
    {
      node_ = std::make_shared<rclcpp::Node>("sub2_test_node");
      sub2 = std::make_shared<gtest::Sub2>(node_);
    }

  virtual void TearDown() override
  {
    ;
  }
};

TEST_F(Sub2TestFixture, receiveTrue)
{
  std::this_thread::sleep_for(std::chrono::milliseconds {1000});
  rclcpp::spin_some(node_);
  auto result = sub2->getData();
  ASSERT_TRUE(result);
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  // Initialize ROS2
  RclCppFixture g_rclcppfixture(argc, argv);
  return RUN_ALL_TESTS();
}
