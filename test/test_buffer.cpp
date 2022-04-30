
#include "static_buffer.hpp"

#include <gtest/gtest.h>

TEST(BufferTest, standardBuffer) {
  LaPointe_Algorithms::Buffer<uint32_t, 5> buffer;
  buffer.push_back(3);
  buffer.push_back(2);
  buffer.push_back(4);
  ASSERT_EQ(buffer.size(), 3);
}
