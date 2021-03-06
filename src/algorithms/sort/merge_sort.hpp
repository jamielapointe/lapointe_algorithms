///
/// \file
/// \brief Basic Implementation Example of [Merge Sort](https://en.wikipedia.org/wiki/Merge_sort)
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
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <memory>
#include <type_traits>

#include "comparisons.hpp"

namespace LaPointe_Algorithms::algorithms::sort {

template <typename Random_Access_Iterator,
          typename Compare = LaPointe_Algorithms::algorithms::compare::Iterator_Less_Than_Equal_Iterator>
void merge(Random_Access_Iterator begin, Random_Access_Iterator middle, Random_Access_Iterator end,
           Random_Access_Iterator begin_dest, Random_Access_Iterator end_dest,
           Compare comp = LaPointe_Algorithms::algorithms::compare::iterator_less_than_equal_iteraor()) {
  auto i = begin;
  auto j = middle;

  // While there are elements in the left or right runs...
  auto k = begin_dest;
  while (k < end_dest) {
    if (i < middle && (j >= end || comp(i, j))) {
      *k = *i;
      ++i;
    } else {
      *k = *j;
      ++j;
    }
    ++k;
  }
}

template <typename Random_Access_Iterator>
void merge_sort(Random_Access_Iterator begin, Random_Access_Iterator end, Random_Access_Iterator begin_dest,
                Random_Access_Iterator end_dest) {
  auto length = end - begin;
  // base case
  if (length <= 1) return;
  // divide
  auto                   mid_len = length / 2;
  Random_Access_Iterator middle  = begin;
  std::advance(middle, mid_len);
  Random_Access_Iterator middle_dest = begin_dest;
  std::advance(middle_dest, mid_len);
  // and conquer - recursive calls
  merge_sort(begin_dest, middle_dest, begin, middle);
  merge_sort(middle_dest, end_dest, middle, end);
  // merge call
  merge(begin, middle, end, begin_dest, end_dest);
}

template <typename Random_Access_Iterator>
void merge_sort(Random_Access_Iterator begin, Random_Access_Iterator end) {
  auto length = end - begin;
  if (length <= 1) return;
  using T   = typename std::remove_pointer<Random_Access_Iterator>::type;
  auto dest = std::make_unique<T[]>(static_cast<size_t>(length));  // NOLINT - ignore c style array here
  Random_Access_Iterator begin_dest = dest.get();
  Random_Access_Iterator end_dest   = begin_dest;
  std::advance(end_dest, length);
  std::copy(begin, end, begin_dest);
  merge_sort(begin_dest, end_dest, begin, end);
}

}  // namespace LaPointe_Algorithms::algorithms::sort
