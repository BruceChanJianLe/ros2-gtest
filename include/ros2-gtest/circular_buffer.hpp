#pragma once

#include <optional>
#include <type_traits>
#include <vector>

namespace gtest
{
  template <typename T>
  class CircularBuffer
  {
  public:
    /// \brief Constructor as placeholder
    CircularBuffer()
      : buffer(1), capacity{1}, head{0}, tail{0}, count{0} {}

    /// \brief Constructor for runtime capacity
    explicit CircularBuffer(size_t capacity)
      : buffer(capacity), capacity{capacity}, head{0}, tail{0}, count{0} {}

    /// \brief Constructor for compile time capacity
    template <size_t Capacity>
    explicit CircularBuffer(std::integral_constant<size_t, Capacity>)
      : buffer(Capacity), capacity{Capacity}, head{0}, tail{0}, count{0} {}

    /// \brief Destructor
    virtual ~CircularBuffer() {}

    /*
     * \brief Function to get the current number of elements in the buffer
     * \return size_t size of buffer
     */
    size_t size() const { return count; }

    /*
     * \brief Function to check if the buffer is empty
     * \return bool true if buffer is empty, otherwise false
     */
    bool empty() const { return count == 0; }

    /*
     * \brief Function to check if the buffer is full
     * \return bool true if buffer is full, otherwise false
     */
    bool full() const { return count == capacity; }

    /*
     * \brief Function to add an element at the end of the buffer (tail)
     * \return void
     */
    void push_back(const T& value)
    {
      if (full())
      {
        // Overwrites the oldest element
        buffer[tail] = {value};
        tail = (tail + 1) % capacity;
        head = (head + 1) % capacity; // Moves head to next element in case of overwrites
      }
      else
      {
        buffer[tail] = {value};
        tail = (tail + 1) % capacity;
        ++count;
      }
    }

    /*
     * \brief Function to access an element at a given index
     * \return std::nullopt if element does not exist, otherwise std::optional<T>
     */
    std::optional<T> operator[](size_t index)
    {
      // Sanity check
      if (index >= count) return std::nullopt;
      // MISRA C++ 2008: Prefer to avoid exceptions, handle errors explicitly
      size_t pos = (head + index) % capacity;
      return buffer[pos];
    }

    /*
     * \brief Function to access an element at a given index (const version)
     * \return std::nullopt if element does not exist, otherwise std::optional<T>
     */
    const std::optional<T> operator[](size_t index) const
    {
      // Sanity check
      if (index >= count) return std::nullopt;
      // MISRA C++ 2008: Prefer to avoid exceptions, handle errors explicitly
      size_t pos = (head + index) % capacity;
      return buffer[pos];
    }

  private:
    std::vector<std::optional<T>> buffer;  // Dynamic array to store elements
    size_t capacity;                       // Maximum capacity of the buffer
    size_t head;                           // Index of the first element
    size_t tail;                           // Index where the next element will be inserted
    size_t count;                          // Current number of elements in the buffer
  };
} // gtest
