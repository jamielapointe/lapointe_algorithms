///
/// \file
/// \brief Basic Implementation Example of [Insertion Sort](https://en.wikipedia.org/wiki/Insertion_sort)
/// \details
///
/// Build the final sorted array one item at a time
/// Take and item out of the list, find the location it belongs within the sorted list
/// and insert it there
/// repeat until no more items exist in the list
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
          typename Compare = LaPointe_Algorithms::Data_Structures::Compare::Iterator_Greater_Than_Value>
void insertion_sort(Random_Access_Iterator begin, Random_Access_Iterator end,
                    Compare comp = LaPointe_Algorithms::Data_Structures::Compare::iterator_greater_than_value()) {
  Random_Access_Iterator i = begin + 1;
  while (i < end) {
    auto                   x = *i;
    Random_Access_Iterator j = i - 1;
    while (j >= begin && comp(j, x)) {
      *(j + 1) = *j;
      j -= 1;
    }
    *(j + 1) = x;
    i += 1;
  }
}

}  // namespace LaPointe_Algorithms::Data_Structures::Sort
