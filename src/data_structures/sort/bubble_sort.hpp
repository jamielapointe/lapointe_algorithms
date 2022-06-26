#pragma once

///
/// \file
/// \brief Basic Implementation Example of [Bubble Sort](https://en.wikipedia.org/wiki/Bubble_sort)
/// \details
///
/// A simple comparsion sort where one iterates through the list swapping pairs
/// into the proper order via a comparison operation.  The iteration ends when
/// the list is sorted
///
/// Time Complexity:
/// - Worse-case: \f$O(n^2)\f$ comparisons, \f$O(n^2)\f$ swaps
/// - Best-case: \f$O(n)\f$ comparisons, \f$O(1)\f$ swaps
/// - Average: \f$O(n^2)\f$ comparisons, \f$O(n^2)\f$ swaps
///
/// Space Complexity:
/// - Worse-case: \f$O(n)\f$ total, \f$O(1)\f$ auxiliary
///

#include <cstdint>

#include "comparisons.hpp"

namespace LaPointe_Algorithms::Data_Structures::Sort {

template <typename Random_Access_Iterator,
          typename Compare = LaPointe_Algorithms::Data_Structures::Compare::Iterator_Greater_Than_Iterator>
void bubble_sort(Random_Access_Iterator begin, Random_Access_Iterator end,
                 Compare comp = LaPointe_Algorithms::Data_Structures::Compare::iterator_greater_than_iteraor()) {
  Random_Access_Iterator j = end;
  while (j > begin) {
    Random_Access_Iterator k = begin;
    for (Random_Access_Iterator i = begin + 1; i < j; ++i) {
      if (comp((i - 1), i)) {
        auto tmp = *i;
        *i       = *(i - 1);
        *(i - 1) = tmp;
        k        = i;
      }
    }
    j = k;
  }
}

}  // namespace LaPointe_Algorithms::Data_Structures::Sort
