#include <gtest/gtest.h>

#include <array>
#include <fstream>
#include <iostream>
#include <vector>

#include "count_split_inversions.hpp"

TEST(TestCountSplitInversions, BasicTest00) {  // NOLINT
  static constexpr std::size_t   arr_size{6};
  std::array<uint32_t, arr_size> base_array{1, 3, 5, 2, 4, 6};  // NOLINT ignore magic #
  static constexpr uint32_t      truth_split_inversion_count{3};

  uint32_t count = LaPointe_Algorithms::algorithms::sort::sort_count_inv(base_array.begin(), base_array.end());
  ASSERT_EQ(count, truth_split_inversion_count);
}

TEST(TestCountSplitInversions, CourseraQuiz) {  // NOLINT
  std::vector<uint32_t> integers;
  std::ifstream         in_file;
  uint32_t              integer{0};
  in_file.open("data/IntegerArray.txt");
  while (in_file >> integer) {
    integers.push_back(integer);
  }

  auto* dest_vector = new std::vector<uint32_t>(integers.size());
  std::copy(integers.begin(), integers.end(), dest_vector->begin());

  static constexpr uint32_t truth_split_inversion_count{2407905288};
  uint32_t count = LaPointe_Algorithms::algorithms::sort::sort_count_inv(integers.begin(), integers.end(),
                                                                         dest_vector->begin(), dest_vector->end());
  ASSERT_EQ(count, truth_split_inversion_count);
}
