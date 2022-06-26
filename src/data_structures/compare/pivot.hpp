

#pragma once

#include <iterator>

namespace LaPointe_Algorithms::Data_Structures::Pivot {

struct Pivot_First_Element {
  template <typename Random_Access_Iterator>
  constexpr Random_Access_Iterator operator()(Random_Access_Iterator begin, Random_Access_Iterator end) const {
    (void)end;  // prevent warning
    return begin;
  }
};
constexpr inline Pivot_First_Element pivot_first_element() { return {}; }

struct Pivot_Last_Element {
  template <typename Random_Access_Iterator>
  constexpr Random_Access_Iterator operator()(Random_Access_Iterator begin, Random_Access_Iterator end) const {
    (void)begin;  // prevent warning
    return end - 1;
  }
};
constexpr inline Pivot_Last_Element pivot_last_element() { return {}; }

struct Pivot_Median_Of_Three_Element {
  template <typename Random_Access_Iterator>
  constexpr Random_Access_Iterator operator()(Random_Access_Iterator begin, Random_Access_Iterator end) const {
    auto length  = end - begin;
    auto mid_len = length / 2;
    if (length % 2 == 0) {
      mid_len -= 1;
    }
    Random_Access_Iterator middle = begin;
    std::advance(middle, mid_len);
    auto first = pivot_first_element()(begin, end);
    auto last  = pivot_last_element()(begin, end);

    auto smallest =
        (*first < *middle && *first < *last) ? first : ((*middle < *first && *middle < *last) ? middle : last);
    auto largest =
        (*first > *middle && *first > *last) ? first : ((*middle > *first && *middle > *last) ? middle : last);
    auto median = (*first != *smallest && *first != *largest)
                      ? first
                      : ((*middle != *smallest && *middle != *largest) ? middle : last);
    return median;
  }
};
constexpr inline Pivot_Median_Of_Three_Element pivot_median_of_three_element() { return {}; }

}  // namespace LaPointe_Algorithms::Data_Structures::Pivot
