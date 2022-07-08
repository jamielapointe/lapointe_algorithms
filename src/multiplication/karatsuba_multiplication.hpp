///
/// \file
/// \brief Implement the [Karatsuba Multiplication Algorithm](https://en.wikipedia.org/wiki/Karatsuba_algorithm)
/// \details
///
/// Computes a multiplication between two aribitrarily long integer values;
/// The algorithm requires strings of equal lengths, so the
///
/// Time Complexity:
/// - \f$O(n^{\log_2 3}\f$
///

#include <array>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "string_utils.hpp"

// TODO(user): This hole thing can be probably be optimized a lot more

static constexpr long double ten{10.0L};

namespace LaPointe_Algorithms::multiplication::karatsuba {

template <typename Random_Access_Iterator>
std::string add(Random_Access_Iterator begin_x, Random_Access_Iterator end_x, Random_Access_Iterator begin_y,
                Random_Access_Iterator end_y);
std::string add(std::string x, std::string y);

template <typename Random_Access_Iterator>
std::string sub(Random_Access_Iterator begin_x, Random_Access_Iterator end_x, Random_Access_Iterator begin_y,
                Random_Access_Iterator end_y);
std::string sub(std::string x, std::string y);

std::string multiply(std::string x, std::string y);

}  // namespace LaPointe_Algorithms::multiplication::karatsuba

namespace LaPointe_Algorithms::multiplication::karatsuba::Internal {

template <typename T>
bool is_power_of_two(T num) {
  return num != 0 && (num & (num - 1)) == 0;
}

static bool is_larger(std::string const& x, std::string const& y) {
  // assumes the lengths are equal
  for (uint32_t i = 0; i < x.length(); ++i) {
    if (x[i] > y[i]) {
      return true;
    }
    if (x[i] < y[i]) {
      return false;
    }
  }
  return true;
}

static void make_equal_length(std::string& x, std::string& y) {
  auto x_len = x.length();
  auto y_len = y.length();
  if (x_len == y_len) {
    return;
  }
  std::string& upper       = x_len > y_len ? x : y;
  std::string& lower       = x_len > y_len ? y : x;
  auto         length_diff = upper.length() - lower.length();
  lower                    = std::string(length_diff, '0').append(lower);
}

static void make_equal_length_power_of_two(std::string& x, std::string& y) {
  // assumes positive integers only
  make_equal_length(x, y);
  while (!is_power_of_two(x.length())) {
    x.insert(0, "0");
    y.insert(0, "0");
  }
}

static int64_t multiply_single_digits(int64_t x, int64_t y) {
  // converts characters to integer, multiplies them, converts the result back to a string, and returns the string
  // result
  return x * y;
}

template <typename Random_Access_Iterator>
static void add(Random_Access_Iterator begin_x, Random_Access_Iterator end_x, Random_Access_Iterator end_y,
                Random_Access_Iterator end_sum) {
  auto    x     = end_x - 1;
  auto    y     = end_y - 1;
  auto    s     = end_sum - 1;
  int64_t carry = 0;
  while (x >= begin_x) {
    int64_t     y_digit   = static_cast<int64_t>(*y - '0');
    int64_t     x_digit   = static_cast<int64_t>(*x - '0');
    int64_t     value     = x_digit + y_digit + carry;
    std::string tmp_value = std::to_string(value);
    *s                    = *(tmp_value.end() - 1);
    carry                 = tmp_value.length() > 1 ? static_cast<int64_t>(*(tmp_value.begin()) - '0') : 0;
    --x;
    --y;
    --s;
  }
  if (carry > 0) {
    *s = *(std::to_string(carry).c_str());
  }
}

template <typename Random_Access_Iterator>
static void sub(Random_Access_Iterator begin_x, Random_Access_Iterator end_x, Random_Access_Iterator end_y,
                Random_Access_Iterator end_diff) {
  auto                     x     = end_x - 1;
  auto                     y     = end_y - 1;
  auto                     s     = end_diff - 1;
  int64_t                  carry = 0;
  static constexpr int64_t SHIFT_1_DIGIT_10{10};
  while (x >= begin_x) {
    int64_t y_digit = static_cast<int64_t>(*y - '0');
    int64_t x_digit = static_cast<int64_t>(*x - '0');
    int64_t value   = x_digit - y_digit - carry;
    carry           = 0;
    if (value < 0) {
      value += SHIFT_1_DIGIT_10;
      carry = 1;
    }
    std::string tmp_value = std::to_string(value);
    *s                    = *(tmp_value.end() - 1);
    --x;
    --y;
    --s;
  }
  if (carry > 0) {
    *s = *(std::to_string(carry).c_str());
  }
}

template <typename Random_Access_Iterator>
static std::string multiply(Random_Access_Iterator begin_x, Random_Access_Iterator end_x,
                            Random_Access_Iterator begin_y, Random_Access_Iterator end_y) {
  // base case
  if (end_x - begin_x == 1) {
    std::string product = std::to_string(
        multiply_single_digits(static_cast<int64_t>(*begin_x - '0'), static_cast<int64_t>(*begin_y - '0')));
    return product;
  }

  // find the middle for the split
  std::size_t n = static_cast<std::size_t>(end_x - begin_x);
  if (!is_power_of_two(n)) {
    std::cout << "the length of the strings must be a power of two!  n = " << n << std::endl;
    return "";
  }
  std::size_t            half_n   = n / 2;
  Random_Access_Iterator middle_x = begin_x;
  std::advance(middle_x, half_n);
  Random_Access_Iterator middle_y = begin_y;
  std::advance(middle_y, half_n);

  // intermediate results
  auto p = LaPointe_Algorithms::multiplication::karatsuba::add(begin_x, middle_x, middle_x, end_x);
  auto q = LaPointe_Algorithms::multiplication::karatsuba::add(begin_y, middle_y, middle_y, end_y);
  if (q.length() > p.length()) {
    std::swap(p, q);
  }
  make_equal_length_power_of_two(p, q);

  // recursive calls for divide & conquer
  auto        ac    = multiply(begin_x, middle_x, begin_y, middle_y);
  auto        bd    = multiply(middle_x, end_x, middle_y, end_y);
  auto        pq    = multiply(p.begin(), p.end(), q.begin(), q.end());

  // intermediate results
  auto        diff0 = LaPointe_Algorithms::multiplication::karatsuba::sub(pq, ac);
  auto        abcd  = LaPointe_Algorithms::multiplication::karatsuba::sub(diff0, bd);

  std::string acn(ac.length() + n, '0');
  acn.replace(0, ac.length(), ac);

  std::string pqn(abcd.length() + half_n, '0');
  pqn.replace(0, abcd.length(), abcd);

  // collect the results
  auto tmp2    = LaPointe_Algorithms::multiplication::karatsuba::add(acn, pqn);
  auto product = LaPointe_Algorithms::multiplication::karatsuba::add(tmp2, bd);
  return product;
}

}  // namespace LaPointe_Algorithms::multiplication::karatsuba::Internal

namespace LaPointe_Algorithms::multiplication::karatsuba {

std::string add(std::string x, std::string y) {
  Internal::make_equal_length(x, y);
  std::string sum(static_cast<size_t>(x.length() + 1), ' ');
  Internal::add(x.begin(), x.end(), y.end(), sum.end());
  return trim_remove_leading_zeros_copy(sum);
}

template <typename Random_Access_Iterator>
std::string add(Random_Access_Iterator begin_x, Random_Access_Iterator end_x, Random_Access_Iterator begin_y,
                Random_Access_Iterator end_y) {
  std::string x(begin_x, end_x);
  std::string y(begin_y, end_y);
  return add(x, y);
}

std::string sub(std::string x, std::string y) {
  Internal::make_equal_length(x, y);
  bool is_negative = false;
  if (!Internal::is_larger(x, y)) {
    std::swap(x, y);
    is_negative = true;
  }
  std::string sum(static_cast<size_t>(x.length() + 1), ' ');
  Internal::sub(x.begin(), x.end(), y.end(), sum.end());
  sum = trim_remove_leading_zeros_copy(sum);
  if (is_negative) {
    sum.insert(0, "-");
  }
  return sum;
}

template <typename Random_Access_Iterator>
std::string sub(Random_Access_Iterator begin_x, Random_Access_Iterator end_x, Random_Access_Iterator begin_y,
                Random_Access_Iterator end_y) {
  std::string x(begin_x, end_x);
  std::string y(begin_y, end_y);
  return sub(x, y);
}

std::string multiply(std::string x, std::string y) {
  Internal::make_equal_length(x, y);
  return Internal::multiply(x.begin(), x.end(), y.begin(), y.end());
}

}  // namespace LaPointe_Algorithms::multiplication::karatsuba
