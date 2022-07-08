
#pragma once

namespace LaPointe_Algorithms::algorithms::compare {

// iterator less than iterator
struct Iterator_Less_Than_Iterator {
  template <typename Iterator1, typename Iterator2>
  constexpr bool operator()(Iterator1 val1, Iterator2 val2) const {
    return *val1 < *val2;
  }
};
constexpr inline Iterator_Less_Than_Iterator iterator_less_than_iteraor() { return {}; }

// iterator less than or equal to iterator
struct Iterator_Less_Than_Equal_Iterator {
  template <typename Iterator1, typename Iterator2>
  constexpr bool operator()(Iterator1 val1, Iterator2 val2) const {
    return *val1 <= *val2;
  }
};
constexpr inline Iterator_Less_Than_Equal_Iterator iterator_less_than_equal_iteraor() { return {}; }

// iterator greater than iterator
struct Iterator_Greater_Than_Iterator {
  template <typename Iterator1, typename Iterator2>
  constexpr bool operator()(Iterator1 val1, Iterator2 val2) const {
    return *val1 > *val2;
  }
};
constexpr inline Iterator_Greater_Than_Iterator iterator_greater_than_iteraor() { return {}; }

// iterator less than value
struct Iterator_Less_Than_Value {
  template <typename Iterator, typename Value>
  constexpr bool operator()(Iterator val1, Value const& val2) {
    return *val1 < val2;
  }
};
constexpr inline Iterator_Less_Than_Value iterator_less_than_value() { return {}; }

// iterator greater than value
struct Iterator_Greater_Than_Value {
  template <typename Iterator, typename Value>
  constexpr bool operator()(Iterator val1, Value const& val2) {
    return *val1 > val2;
  }
};
constexpr inline Iterator_Greater_Than_Value iterator_greater_than_value() { return {}; }

}  // namespace LaPointe_Algorithms::algorithms::compare
