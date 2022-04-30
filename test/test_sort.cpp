#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <random>

#include "insertion_sort.hpp"
#include "selection_sort.hpp"

TEST(TestSort, testStdArray) {
  std::random_device                      rd;
  std::mt19937_64                         generator(rd());
  std::uniform_int_distribution<uint32_t> distribution;
  static constexpr std::size_t            arr_size{128};

  std::array<uint32_t, arr_size>          base_array{0};
  for (std::size_t i = 0; i < arr_size; ++i) {
    base_array[i] = distribution(generator);
  }

  // truth sort
  std::array<uint32_t, arr_size> array_truth_sort{0};
  std::copy(base_array.begin(), base_array.end(), array_truth_sort.data());
  std::sort(array_truth_sort.begin(), array_truth_sort.end());

  // selection sort
  std::array<uint32_t, arr_size> array_selection_sort{0};
  std::copy(base_array.begin(), base_array.end(), array_selection_sort.data());
  LaPointe_Algorithms::Data_Structures::Sort::selection_sort(array_selection_sort.begin(), array_selection_sort.end());

  // insertion sort
  std::array<uint32_t, arr_size> array_insertion_sort{0};
  std::copy(base_array.begin(), base_array.end(), array_insertion_sort.data());
  LaPointe_Algorithms::Data_Structures::Sort::insertion_sort(array_insertion_sort.begin(), array_insertion_sort.end());

  // validate equality
  ASSERT_TRUE(std::equal(array_truth_sort.begin(), array_truth_sort.end(), array_selection_sort.begin()));
  ASSERT_TRUE(std::equal(array_truth_sort.begin(), array_truth_sort.end(), array_insertion_sort.begin()));
}