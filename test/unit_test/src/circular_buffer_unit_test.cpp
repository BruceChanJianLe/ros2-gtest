#include <gtest/gtest.h>
#include <optional>
#include "ros2-gtest/circular_buffer.hpp"

// Test fixture for CircularBuffer
template <typename T>
class CircularBufferTest : public ::testing::Test {
protected:
    // Create a CircularBuffer with runtime capacity
    gtest::CircularBuffer<T> buffer;
    
    // Create a CircularBuffer with compile-time capacity
    gtest::CircularBuffer<T> buffer_static{std::integral_constant<size_t, 5>{}};

    // Sets up the test fixture
    void SetUp() override {
        // You can initialize common objects or perform setup actions here
    }

    // Tears down the test fixture
    void TearDown() override {
        // Clean up any resources allocated in SetUp()
    }
};

// Test case for push_back and operator[]
TYPED_TEST_SUITE_P(CircularBufferTest);

TYPED_TEST_P(CircularBufferTest, PushBackAndAccess) {
    this->buffer = gtest::CircularBuffer<TypeParam>(2);
    TypeParam val1 = 10;
    TypeParam val2 = 20;

    // Add elements to runtime capacity buffer
    this->buffer.push_back(val1);
    this->buffer.push_back(val2);

    // Check size and elements
    EXPECT_EQ(this->buffer.size(), 2u);
    EXPECT_EQ(*(this->buffer[0]), val1);
    EXPECT_EQ(*(this->buffer[1]), val2);

    // Access out-of-bound index will return std::nullopt,
    // exception safe (MISRA compliance exception handling)
    EXPECT_EQ(this->buffer[2], std::nullopt);
}

REGISTER_TYPED_TEST_SUITE_P(CircularBufferTest,
    PushBackAndAccess
);

// Define types to be tested with this test case
typedef ::testing::Types<int, float, double> MyTypes;
INSTANTIATE_TYPED_TEST_SUITE_P(My, CircularBufferTest, MyTypes);

// Main function for running tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
