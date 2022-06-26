
#include <gtest/gtest.h>

#include "static_buffer.hpp"

TEST(BufferTest, standardBuffer) {
  static constexpr uint32_t                          buffer_size{5};
  LaPointe_Algorithms::Buffer<uint32_t, buffer_size> buffer;
  buffer.push_back(3);
  buffer.push_back(2);
  buffer.push_back(4);
  ASSERT_EQ(buffer.size(), 3);
}
