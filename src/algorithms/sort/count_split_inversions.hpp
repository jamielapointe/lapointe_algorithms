///
/// \file
/// \brief Count split inversions in an array of integers
/// \details
///
/// A basic sequential implementation of a divide and conquer sorting algorithm
///
/// Time Complexity:
/// - Worse-case: \f$O(n \log n)\f$
/// - Best-case: \f$O(n \log n)\f$
/// - Average: \f$O(n \log n)\f$
///
/// Space Complexity:
/// - Worse-case: \f$O(n)\f$ total, \f$O(n)\f$ auxiliary
///

#pragma once
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <memory>
#include <type_traits>

#include "comparisons.hpp"

namespace LaPointe_Algorithms::algorithms::sort {

template <typename Random_Access_Iterator,
          typename Compare = LaPointe_Algorithms::algorithms::compare::Iterator_Less_Than_Equal_Iterator>
uint32_t merge_count_split_inv(
    Random_Access_Iterator begin, Random_Access_Iterator middle, Random_Access_Iterator end,
    Random_Access_Iterator begin_dest, Random_Access_Iterator end_dest,
    Compare comp = LaPointe_Algorithms::algorithms::compare::iterator_less_than_equal_iteraor());

template <typename Random_Access_Iterator>
uint32_t sort_count_inv(Random_Access_Iterator begin, Random_Access_Iterator end, Random_Access_Iterator begin_dest,
                        Random_Access_Iterator end_dest);

template <typename Random_Access_Iterator>
uint32_t sort_count_inv(Random_Access_Iterator begin, Random_Access_Iterator end);

template <typename Random_Access_Iterator, typename Compare>
uint32_t merge_count_split_inv(Random_Access_Iterator begin, Random_Access_Iterator middle, Random_Access_Iterator end,
                               Random_Access_Iterator begin_dest, Random_Access_Iterator end_dest, Compare comp) {
  auto     i = begin;
  auto     j = middle;
  uint32_t split_inversion_count{0};
  auto     n = end_dest - begin_dest;

  // While there are elements in the left or right runs...
  auto     k = begin_dest;
  while (k < end_dest) {
    if (i < middle && (j >= end || comp(i, j))) {
      *k = *i;
      ++i;
    } else {
      if (*i > *j) {
        split_inversion_count += (n / 2) - (i - begin);
      }
      *k = *j;
      ++j;
    }
    ++k;
  }
  return split_inversion_count;
}

template <typename Random_Access_Iterator>
uint32_t sort_count_inv(Random_Access_Iterator begin, Random_Access_Iterator end, Random_Access_Iterator begin_dest,
                        Random_Access_Iterator end_dest) {
  // base case
  if ((end - begin) <= 1) return 0;

  auto                   length  = end - begin;
  // divide
  auto                   mid_len = length / 2;
  Random_Access_Iterator middle  = begin;
  std::advance(middle, mid_len);
  Random_Access_Iterator middle_dest = begin_dest;
  std::advance(middle_dest, mid_len);
  // recursive calls - conquer
  uint32_t left_count  = sort_count_inv(begin_dest, middle_dest, begin, middle);
  uint32_t right_count = sort_count_inv(middle_dest, end_dest, middle, end);
  // merge_count_split_inv call
  uint32_t split_count = merge_count_split_inv(begin, middle, end, begin_dest, end_dest);
  return left_count + right_count + split_count;
}

template <typename Random_Access_Iterator>
uint32_t sort_count_inv(Random_Access_Iterator begin, Random_Access_Iterator end) {
  std::size_t length = static_cast<std::size_t>(end - begin);
  if (length < 1) return 0;
  using T                           = typename std::remove_pointer<Random_Access_Iterator>::type;
  auto                   dest       = std::make_unique<T[]>(length);  // NOLINT - ignore c style array here
  Random_Access_Iterator begin_dest = dest.get();
  Random_Access_Iterator end_dest   = begin_dest;
  std::advance(end_dest, length);
  std::copy(begin, end, begin_dest);
  uint32_t total_count = sort_count_inv(begin_dest, end_dest, begin, end);
  return total_count;
}

}  // namespace LaPointe_Algorithms::algorithms::sort
