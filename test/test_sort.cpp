#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <random>

#include "bubble_sort.hpp"
#include "insertion_sort.hpp"
#include "merge_sort.hpp"
#include "selection_sort.hpp"
#include "simple_quick_sort.hpp"

// Do a very simple sort that is easy to debug
TEST(TestSort, simpleTest) {
  static constexpr std::size_t   arr_size{4};
  std::array<uint32_t, arr_size> base_array{5, 3, 7, 1};

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

  // bubble sort
  std::array<uint32_t, arr_size> array_bubble_sort{0};
  std::copy(base_array.begin(), base_array.end(), array_bubble_sort.data());
  LaPointe_Algorithms::Data_Structures::Sort::bubble_sort(array_bubble_sort.begin(), array_bubble_sort.end());

  // merge sort
  std::array<uint32_t, arr_size> array_merge_sort{0};
  std::copy(base_array.begin(), base_array.end(), array_merge_sort.data());
  LaPointe_Algorithms::Data_Structures::Sort::merge_sort(array_merge_sort.begin(), array_merge_sort.end());

  // simple quick sort
  std::array<uint32_t, arr_size> array_simple_quick_sort{0};
  std::copy(base_array.begin(), base_array.end(), array_simple_quick_sort.data());
  uint32_t comparison_count{0};
  LaPointe_Algorithms::Data_Structures::Simplified_Quick_Sort::quick_sort(
      array_simple_quick_sort.begin(), array_simple_quick_sort.end(), comparison_count);

  // validate equality
  ASSERT_TRUE(std::equal(array_truth_sort.begin(), array_truth_sort.end(), array_selection_sort.begin()));
  ASSERT_TRUE(std::equal(array_truth_sort.begin(), array_truth_sort.end(), array_insertion_sort.begin()));
  ASSERT_TRUE(std::equal(array_truth_sort.begin(), array_truth_sort.end(), array_bubble_sort.begin()));
  ASSERT_TRUE(std::equal(array_truth_sort.begin(), array_truth_sort.end(), array_merge_sort.begin()));
  ASSERT_TRUE(std::equal(array_truth_sort.begin(), array_truth_sort.end(), array_simple_quick_sort.begin()));
}

// larger array
TEST(TestSort, testStdArray) {
  static constexpr std::size_t            arr_size{128};
  std::random_device                      rd;
  std::mt19937_64                         generator(rd());
  std::uniform_int_distribution<uint32_t> distribution(0, arr_size * 2);

  std::array<uint32_t, arr_size>          base_array{0};
  for (std::size_t i = 0; i < arr_size; ++i) {
    auto    *partial_end = base_array.begin() + i + 1;
    uint32_t value;
    do {
      value = distribution(generator);
    } while (std::find(base_array.begin(), partial_end, value) != partial_end);
    base_array[i] = value;
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

  // bubble sort
  std::array<uint32_t, arr_size> array_bubble_sort{0};
  std::copy(base_array.begin(), base_array.end(), array_bubble_sort.data());
  LaPointe_Algorithms::Data_Structures::Sort::bubble_sort(array_bubble_sort.begin(), array_bubble_sort.end());

  // merge sort
  std::array<uint32_t, arr_size> array_merge_sort{0};
  std::copy(base_array.begin(), base_array.end(), array_merge_sort.data());
  LaPointe_Algorithms::Data_Structures::Sort::merge_sort(array_merge_sort.begin(), array_merge_sort.end());

  // simple quick sort
  std::array<uint32_t, arr_size> array_simple_quick_sort{0};
  std::copy(base_array.begin(), base_array.end(), array_simple_quick_sort.data());
  uint32_t comparison_count{0};
  LaPointe_Algorithms::Data_Structures::Simplified_Quick_Sort::quick_sort(
      array_simple_quick_sort.begin(), array_simple_quick_sort.end(), comparison_count);

  // validate equality
  ASSERT_TRUE(std::equal(array_truth_sort.begin(), array_truth_sort.end(), array_selection_sort.begin()));
  ASSERT_TRUE(std::equal(array_truth_sort.begin(), array_truth_sort.end(), array_insertion_sort.begin()));
  ASSERT_TRUE(std::equal(array_truth_sort.begin(), array_truth_sort.end(), array_bubble_sort.begin()));
  ASSERT_TRUE(std::equal(array_truth_sort.begin(), array_truth_sort.end(), array_merge_sort.begin()));
  ASSERT_TRUE(std::equal(array_truth_sort.begin(), array_truth_sort.end(), array_simple_quick_sort.begin()));
}
