/// Simpliefied Merge Sort Algorithm for the Coursera course
/// Divide and Conquer, Sorting and Searching, and Randomized Algorithms from Stanford University

#pragma once
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <type_traits>

#include "comparisons.hpp"
#include "pivot.hpp"

namespace LaPointe_Algorithms::algorithms::sort {

template <typename Random_Access_Iterator>
void swap(Random_Access_Iterator a, Random_Access_Iterator b) {
  auto tmp = *a;
  *a       = *b;
  *b       = tmp;
}

template <typename Random_Access_Iterator,
          typename Compare = LaPointe_Algorithms::algorithms::compare::Iterator_Less_Than_Equal_Iterator>
void partition(Random_Access_Iterator begin, Random_Access_Iterator end, Random_Access_Iterator& part,
               Compare comp = LaPointe_Algorithms::algorithms::compare::iterator_less_than_equal_iteraor()) {
  LaPointe_Algorithms::algorithms::sort::swap(part, begin);
  auto p = begin;
  auto i = begin + 1;
  for (auto j = begin + 1; j < end; ++j) {
    if (comp(j, p)) {
      LaPointe_Algorithms::algorithms::sort::swap(j, i);
      ++i;
    }
  }
  part = i - 1;
  LaPointe_Algorithms::algorithms::sort::swap(p, part);
}

template <typename Random_Access_Iterator,
          typename Pivot = LaPointe_Algorithms::algorithms::compare::Pivot_Median_Of_Three_Element>
void quick_sort(Random_Access_Iterator begin, Random_Access_Iterator end, uint32_t& num_comparisons,
                Pivot pivot = LaPointe_Algorithms::algorithms::compare::pivot_median_of_three_element()) {
  if (end - begin <= 1) return;
  auto p = pivot(begin, end);
  num_comparisons += end - begin - 1;
  partition(begin, end, p);
  quick_sort(begin, p, num_comparisons, pivot);
  quick_sort(p + 1, end, num_comparisons, pivot);
}

}  // namespace LaPointe_Algorithms::algorithms::sort
