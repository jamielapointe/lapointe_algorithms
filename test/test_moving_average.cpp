
#include <gtest/gtest.h>

#include "moving_average.hpp"

using LaPointe::Leet::MovingAverage;

TEST(TestMovingAverage, BasicTest) {
  MovingAverage* movingAverage = new MovingAverage(3);
  double         result{0.0};
  double         expected{0.0};
  result   = movingAverage->next(1);  // return 1.0 = 1 / 1
  expected = 1.0 / 1.0;
  ASSERT_FLOAT_EQ(result, expected);
  result   = movingAverage->next(10);  // return 5.5 = (1 + 10) / 2
  expected = (1. + 10.) / 2.;
  ASSERT_FLOAT_EQ(result, expected);
  result   = movingAverage->next(3);  // return 4.66667 = (1 + 10 + 3) / 3
  expected = (1. + 10. + 3.) / 3.;
  ASSERT_FLOAT_EQ(result, expected);
  result   = movingAverage->next(5);  // return 6.0 = (10 + 3 + 5) / 3
  expected = (10. + 3. + 5.) / 3.;
  ASSERT_FLOAT_EQ(result, expected);

  delete movingAverage;
}
