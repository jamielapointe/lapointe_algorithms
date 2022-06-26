///
/// \file
/// \brief Basic Implementation Example of [Selection Sort](https://en.wikipedia.org/wiki/Selection_sort)
/// \details
///
/// Place an insertion pointer at the begining of the array.
/// Scan through the input array, select the minimum value.
/// If the input array is not point at the minimum value, then swap the value at the insertion point with
/// the selected minimum value.
/// If the input array is the minimum value, then do nothing.
/// Move the input array to the next item in the array.
/// Continue until the input array is passed the last value in the array
///
/// Time Complexity:
///
/// - Worse-case: \f$O(n^2)\f$ comparisons, \f$O(n)\f$ swaps
/// - Best-case: \f$O(n^2)\f$ comparisons, \f$O(n)\f$ swaps
/// - Average: \f$O(n^2)\f$ comparisons, \f$O(n)\f$ swaps
///
/// Space Complexity:
/// - Worse-case: \f$O(1)\f$ auxiliary
///

#include <algorithm>
#include <cstdint>

#include "comparisons.hpp"

namespace LaPointe_Algorithms::Data_Structures::Sort {

template <typename Random_Access_Iterator,
          typename Compare = LaPointe_Algorithms::Data_Structures::Compare::Iterator_Less_Than_Iterator>
void selection_sort(Random_Access_Iterator begin, Random_Access_Iterator end,
                    Compare comp = LaPointe_Algorithms::Data_Structures::Compare::iterator_less_than_iteraor()) {
  while (begin != end) {
    Random_Access_Iterator min_j = begin;
    Random_Access_Iterator j     = begin;
    while (j != end) {
      if (comp(j, min_j)) {
        min_j = j;
      }
      j += 1;
    }
    if (min_j != begin) {
      auto tmp = *begin;
      *begin   = *min_j;
      *min_j   = tmp;
    }
    begin += 1;
  }
}

}  // namespace LaPointe_Algorithms::Data_Structures::Sort
