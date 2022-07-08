
#include <gtest/gtest.h>

#include <memory>

#include "moving_average.hpp"

using LaPointe_Algorithms::leet::MovingAverage;

TEST(TestMovingAverage, BasicTest) {  // NOLINT
  auto   movingAverage = std::make_unique<MovingAverage>(3);
  double result{0.0};
  double expected{0.0};
  result   = movingAverage->next(1);  // return 1.0 = 1 / 1
  expected = 1.0 / 1.0;
  ASSERT_FLOAT_EQ(result, expected);
  result   = movingAverage->next(10);  // NOLINT - magic # - return 5.5 = (1 + 10) / 2
  expected = (1. + 10.) / 2.;          // NOLINT - magic #
  ASSERT_FLOAT_EQ(result, expected);
  result   = movingAverage->next(3);  // NOLINT - magic # -  return 4.66667 = (1 + 10 + 3) / 3
  expected = (1. + 10. + 3.) / 3.;    // NOLINT - magic #
  ASSERT_FLOAT_EQ(result, expected);
  result   = movingAverage->next(5);  // NOLINT - magic # - return 6.0 = (10 + 3 + 5) / 3
  expected = (10. + 3. + 5.) / 3.;    // NOLINT - magic #
  ASSERT_FLOAT_EQ(result, expected);
}
