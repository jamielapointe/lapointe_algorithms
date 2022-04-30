#include <benchmark/benchmark.h>

#include <array>
#include <random>

#include "insertion_sort.hpp"
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

BENCHMARK_DEFINE_F(Sort_Fixture, SelectionSort)(benchmark::State& st) {
  for (auto _ : st) {
    st.PauseTiming();
    construct_random_set(st.range(0));
    st.ResumeTiming();
    LaPointe_Algorithms::Data_Structures::Sort::selection_sort(data_.begin(), data_.end());
  }
}

BENCHMARK_DEFINE_F(Sort_Fixture, InsertionSort)(benchmark::State& st) {
  for (auto _ : st) {
    st.PauseTiming();
    construct_random_set(st.range(0));
    st.ResumeTiming();
    LaPointe_Algorithms::Data_Structures::Sort::insertion_sort(data_.begin(), data_.end());
  }
}

static constexpr std::int32_t range_multiplier{2};
static constexpr std::int64_t range_lower{8};
static constexpr std::int64_t range_upper{8 << 8};
BENCHMARK_REGISTER_F(Sort_Fixture, SelectionSort)->RangeMultiplier(range_multiplier)->Range(range_lower, range_upper);
BENCHMARK_REGISTER_F(Sort_Fixture, InsertionSort)->RangeMultiplier(range_multiplier)->Range(range_lower, range_upper);
