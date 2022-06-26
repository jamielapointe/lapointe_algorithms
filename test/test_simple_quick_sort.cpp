#include <gtest/gtest.h>

#include <array>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "pivot.hpp"
#include "simple_quick_sort.hpp"

TEST(TestSimpleQuickSort, OneElement) {
  static constexpr std::size_t   arr_size{1};
  std::array<uint32_t, arr_size> base_array{1};
  uint32_t                       num_comparisons{0};
  static constexpr uint32_t      truth_comparisons{0};
  LaPointe_Algorithms::Data_Structures::Simplified_Quick_Sort::quick_sort(base_array.begin(), base_array.end(),
                                                                          num_comparisons);
  ASSERT_EQ(num_comparisons, truth_comparisons);
}

TEST(TestSimpleQuickSort, TwoElements) {
  static constexpr std::size_t   arr_size{2};
  std::array<uint32_t, arr_size> base_array{1, 3};
  uint32_t                       num_comparisons{0};
  static constexpr uint32_t      truth_comparisons{1};
  LaPointe_Algorithms::Data_Structures::Simplified_Quick_Sort::quick_sort(base_array.begin(), base_array.end(),
                                                                          num_comparisons);
  ASSERT_EQ(num_comparisons, truth_comparisons);
}

TEST(TestSimpleQuickSort, FourElements) {
  static constexpr std::size_t   arr_size{4};
  std::array<uint32_t, arr_size> base_array{1, 3, 2, 4};
  std::array<uint32_t, arr_size> array_simple_quick_sort;
  std::copy(base_array.begin(), base_array.end(), array_simple_quick_sort.begin());
  std::array<uint32_t, arr_size> array_truth_sort{1, 2, 3, 4};
  uint32_t                       num_comparisons{0};
  static constexpr uint32_t      truth_comparisons{4};
  LaPointe_Algorithms::Data_Structures::Simplified_Quick_Sort::quick_sort(
      array_simple_quick_sort.begin(), array_simple_quick_sort.end(), num_comparisons);
  auto did_pass = std::equal(array_truth_sort.begin(), array_truth_sort.end(), array_simple_quick_sort.begin());
  ASSERT_TRUE(did_pass);
  ASSERT_EQ(num_comparisons, truth_comparisons);
}

TEST(TestSimpleQuickSort, FiveElements) {
  static constexpr std::size_t   arr_size{5};
  std::array<uint32_t, arr_size> base_array{6, 1, 4, 7, 3};
  std::array<uint32_t, arr_size> array_simple_quick_sort;
  std::copy(base_array.begin(), base_array.end(), array_simple_quick_sort.begin());
  std::array<uint32_t, arr_size> array_truth_sort{1, 3, 4, 6, 7};
  uint32_t                       num_comparisons{0};
  static constexpr uint32_t      truth_comparisons{6};
  LaPointe_Algorithms::Data_Structures::Simplified_Quick_Sort::quick_sort(
      array_simple_quick_sort.begin(), array_simple_quick_sort.end(), num_comparisons);
  auto did_pass = std::equal(array_truth_sort.begin(), array_truth_sort.end(), array_simple_quick_sort.begin());
  ASSERT_TRUE(did_pass);
  ASSERT_EQ(num_comparisons, truth_comparisons);
}

TEST(TestSimpleQuickSort, RandomElements0) {
  static constexpr std::size_t            arr_size{25};
  std::random_device                      rd;
  std::mt19937_64                         generator(rd());
  std::uniform_int_distribution<uint32_t> distribution(0, arr_size * 2);

  std::array<uint32_t, arr_size>          base_array{0};
  for (std::size_t i = 0; i < arr_size; ++i) {
    auto*    partial_end = base_array.begin() + i + 1;
    uint32_t value;
    do {
      value = distribution(generator);
    } while (std::find(base_array.begin(), partial_end, value) != partial_end);
    base_array[i] = value;
  }
  std::array<uint32_t, arr_size> array_truth_sort{0};
  std::copy(base_array.begin(), base_array.end(), array_truth_sort.data());
  std::sort(array_truth_sort.begin(), array_truth_sort.end());

  std::array<uint32_t, arr_size> array_simple_quick_sort{0};
  std::copy(base_array.begin(), base_array.end(), array_simple_quick_sort.data());

  uint32_t num_comparisons{0};
  LaPointe_Algorithms::Data_Structures::Simplified_Quick_Sort::quick_sort(
      array_simple_quick_sort.begin(), array_simple_quick_sort.end(), num_comparisons);
  auto did_pass = std::equal(array_truth_sort.begin(), array_truth_sort.end(), array_simple_quick_sort.begin());
  ASSERT_TRUE(did_pass);
}

TEST(TestSimpleQuickSort, TestPivots) {
  std::array<uint32_t, 5> odd{10, 8, 13, 6, 4};
  std::array<uint32_t, 6> even{
      8, 2, 4, 5, 7, 1,
  };
  static constexpr uint32_t truth_odd_first{10};
  static constexpr uint32_t truth_odd_median{10};
  static constexpr uint32_t truth_odd_last{4};
  static constexpr uint32_t truth_even_first{8};
  static constexpr uint32_t truth_even_median{4};
  static constexpr uint32_t truth_even_last{1};

  ASSERT_EQ(*LaPointe_Algorithms::Data_Structures::Pivot::pivot_first_element()(odd.begin(), odd.end()),
            truth_odd_first);
  ASSERT_EQ(*LaPointe_Algorithms::Data_Structures::Pivot::pivot_median_of_three_element()(odd.begin(), odd.end()),
            truth_odd_median);
  ASSERT_EQ(*LaPointe_Algorithms::Data_Structures::Pivot::pivot_last_element()(odd.begin(), odd.end()), truth_odd_last);

  ASSERT_EQ(*LaPointe_Algorithms::Data_Structures::Pivot::pivot_first_element()(even.begin(), even.end()),
            truth_even_first);
  ASSERT_EQ(*LaPointe_Algorithms::Data_Structures::Pivot::pivot_median_of_three_element()(even.begin(), even.end()),
            truth_even_median);
  ASSERT_EQ(*LaPointe_Algorithms::Data_Structures::Pivot::pivot_last_element()(even.begin(), even.end()),
            truth_even_last);
}

TEST(TestSimpleQuickSort, CourseraQuizPart1) {
  std::vector<uint32_t> integers;
  std::ifstream         in_file;
  uint32_t              integer;
  in_file.open("data/quick_sort_data.txt");
  while (in_file >> integer) {
    integers.push_back(integer);
  }

  auto* vector_simple_quick_sort = new std::vector<uint32_t>(integers.size());
  auto* vector_truth_sort        = new std::vector<uint32_t>(integers.size());
  std::copy(integers.begin(), integers.end(), vector_simple_quick_sort->begin());
  std::copy(integers.begin(), integers.end(), vector_truth_sort->begin());
  std::sort(vector_truth_sort->begin(), vector_truth_sort->end());

  uint32_t                  num_comparisons{0};
  static constexpr uint32_t truth_comparisons{162085};
  LaPointe_Algorithms::Data_Structures::Simplified_Quick_Sort::quick_sort(
      vector_simple_quick_sort->begin(), vector_simple_quick_sort->end(), num_comparisons,
      LaPointe_Algorithms::Data_Structures::Pivot::pivot_first_element());
  auto did_pass = std::equal(vector_truth_sort->begin(), vector_truth_sort->end(), vector_simple_quick_sort->begin());
  ASSERT_TRUE(did_pass);
  ASSERT_EQ(num_comparisons, truth_comparisons);
}

TEST(TestSimpleQuickSort, CourseraQuizPart2) {
  std::vector<uint32_t> integers;
  std::ifstream         in_file;
  uint32_t              integer;
  in_file.open("data/quick_sort_data.txt");
  while (in_file >> integer) {
    integers.push_back(integer);
  }

  auto* vector_simple_quick_sort = new std::vector<uint32_t>(integers.size());
  auto* vector_truth_sort        = new std::vector<uint32_t>(integers.size());
  std::copy(integers.begin(), integers.end(), vector_simple_quick_sort->begin());
  std::copy(integers.begin(), integers.end(), vector_truth_sort->begin());
  std::sort(vector_truth_sort->begin(), vector_truth_sort->end());

  uint32_t                  num_comparisons{0};
  static constexpr uint32_t truth_comparisons{164123};
  LaPointe_Algorithms::Data_Structures::Simplified_Quick_Sort::quick_sort(
      vector_simple_quick_sort->begin(), vector_simple_quick_sort->end(), num_comparisons,
      LaPointe_Algorithms::Data_Structures::Pivot::pivot_last_element());
  auto did_pass = std::equal(vector_truth_sort->begin(), vector_truth_sort->end(), vector_simple_quick_sort->begin());
  ASSERT_TRUE(did_pass);
  ASSERT_EQ(num_comparisons, truth_comparisons);
}

TEST(TestSimpleQuickSort, CourseraQuizPart3) {
  std::vector<uint32_t> integers;
  std::ifstream         in_file;
  uint32_t              integer;
  in_file.open("data/quick_sort_data.txt");
  while (in_file >> integer) {
    integers.push_back(integer);
  }

  auto* vector_simple_quick_sort = new std::vector<uint32_t>(integers.size());
  auto* vector_truth_sort        = new std::vector<uint32_t>(integers.size());
  std::copy(integers.begin(), integers.end(), vector_simple_quick_sort->begin());
  std::copy(integers.begin(), integers.end(), vector_truth_sort->begin());
  std::sort(vector_truth_sort->begin(), vector_truth_sort->end());

  uint32_t                  num_comparisons{0};
  static constexpr uint32_t truth_comparisons{138382};
  LaPointe_Algorithms::Data_Structures::Simplified_Quick_Sort::quick_sort(
      vector_simple_quick_sort->begin(), vector_simple_quick_sort->end(), num_comparisons,
      LaPointe_Algorithms::Data_Structures::Pivot::pivot_median_of_three_element());
  auto did_pass = std::equal(vector_truth_sort->begin(), vector_truth_sort->end(), vector_simple_quick_sort->begin());
  ASSERT_TRUE(did_pass);
  ASSERT_EQ(num_comparisons, truth_comparisons);
}
