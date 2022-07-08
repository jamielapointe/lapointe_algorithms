#include <benchmark/benchmark.h>
//#include <pstl/glue_execution_defs.h>

#include <algorithm>
#include <array>
#include <execution>
#include <random>

#include "bubble_sort.hpp"
#include "insertion_sort.hpp"
#include "lapointe_algorithms_config.h"
#include "selection_sort.hpp"

class Sort_Fixture : public benchmark::Fixture {
 public:
  void                  SetUp(const ::benchmark::State& state) final {}

  void                  TearDown(const ::benchmark::State& state) final {}

  std::vector<uint32_t> data_;

  void                  construct_random_set(std::size_t size) {
                     std::random_device                      rd;
                     std::mt19937_64                         generator(rd());
                     std::uniform_int_distribution<uint32_t> distribution;

                     data_.resize(size);
                     for (std::size_t index{0}; index < size; ++index) {
                       data_.push_back(distribution(generator));
    }
  }
};

BENCHMARK_DEFINE_F(Sort_Fixture, StlSort)(benchmark::State& st) {
  for (auto _ : st) {
    (void)_;
    st.PauseTiming();
    construct_random_set(st.range(0));
    st.ResumeTiming();
    std::sort(std::execution::seq, data_.begin(), data_.end());
  }
}

#if defined(TBB_LIBRARY_FOUND)
BENCHMARK_DEFINE_F(Sort_Fixture, StlParSort)(benchmark::State& st) {
  for (auto _ : st) {
    (void)_;
    st.PauseTiming();
    construct_random_set(st.range(0));
    st.ResumeTiming();
    std::sort(std::execution::par, data_.begin(), data_.end());
  }
}

BENCHMARK_DEFINE_F(Sort_Fixture, StlParVecSort)(benchmark::State& st) {
  for (auto _ : st) {
    (void)_;
    st.PauseTiming();
    construct_random_set(st.range(0));
    st.ResumeTiming();
    std::sort(std::execution::par_unseq, data_.begin(), data_.end());
  }
}
#endif

BENCHMARK_DEFINE_F(Sort_Fixture, SelectionSort)(benchmark::State& st) {
  for (auto _ : st) {
    (void)_;
    st.PauseTiming();
    construct_random_set(st.range(0));
    st.ResumeTiming();
    LaPointe_Algorithms::algorithms::sort::selection_sort(data_.begin(), data_.end());
  }
}

BENCHMARK_DEFINE_F(Sort_Fixture, InsertionSort)(benchmark::State& st) {
  for (auto _ : st) {
    (void)_;
    st.PauseTiming();
    construct_random_set(st.range(0));
    st.ResumeTiming();
    LaPointe_Algorithms::algorithms::sort::insertion_sort(data_.begin(), data_.end());
  }
}

BENCHMARK_DEFINE_F(Sort_Fixture, BubbleSort)(benchmark::State& st) {
  for (auto _ : st) {
    (void)_;
    st.PauseTiming();
    construct_random_set(st.range(0));
    st.ResumeTiming();
    LaPointe_Algorithms::algorithms::sort::bubble_sort(data_.begin(), data_.end());
  }
}

static constexpr std::int32_t range_multiplier{2};
static constexpr std::int64_t range_lower{8};
static constexpr std::int64_t range_upper{8 << 8};
BENCHMARK_REGISTER_F(Sort_Fixture, StlSort)  // NOLINT
    ->RangeMultiplier(range_multiplier)
    ->Range(range_lower, range_upper);
#if defined(TBB_LIBRARY_FOUND)
BENCHMARK_REGISTER_F(Sort_Fixture, StlParSort)  // NOLINT
    ->RangeMultiplier(range_multiplier)
    ->Range(range_lower, range_upper);
BENCHMARK_REGISTER_F(Sort_Fixture, StlParVecSort)  // NOLINT
    ->RangeMultiplier(range_multiplier)
    ->Range(range_lower, range_upper);  // NOLINT
#endif
BENCHMARK_REGISTER_F(Sort_Fixture, SelectionSort)  // NOLINT
    ->RangeMultiplier(range_multiplier)
    ->Range(range_lower, range_upper);
BENCHMARK_REGISTER_F(Sort_Fixture, InsertionSort)  // NOLINT
    ->RangeMultiplier(range_multiplier)
    ->Range(range_lower, range_upper);
BENCHMARK_REGISTER_F(Sort_Fixture, BubbleSort)  // NOLINT
    ->RangeMultiplier(range_multiplier)
    ->Range(range_lower, range_upper);

static constexpr std::int64_t large_range_lower{8 << 9};
static constexpr std::int64_t large_range_upper{8 << 25};
BENCHMARK_REGISTER_F(Sort_Fixture, StlSort)  // NOLINT
    ->RangeMultiplier(range_multiplier)
    ->Range(large_range_lower, large_range_upper);
#if defined(TBB_LIBRARY_FOUND)
BENCHMARK_REGISTER_F(Sort_Fixture, StlParSort)  // NOLINT
    ->RangeMultiplier(range_multiplier)
    ->Range(large_range_lower, large_range_upper);
BENCHMARK_REGISTER_F(Sort_Fixture, StlParVecSort)  // NOLINT
    ->RangeMultiplier(range_multiplier)
    ->Range(large_range_lower, large_range_upper);
#endif
