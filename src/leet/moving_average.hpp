/// \brief https://leetcode.com/problems/moving-average-from-data-stream/
///
/// Your MovingAverage object will be instantiated and called as such:
/// MovingAverage* obj = new MovingAverage(size);
/// double param_1 = obj->next(val);
///

#include <cstdint>
#include <memory>

namespace LaPointe_Algorithms::leet {

class MovingAverage {
 public:
  explicit MovingAverage(uint32_t capacity)
      : capacity_{capacity},
        data_{new int[capacity_]()},  // NOLINT - allow c style array
        current_index_{0},
        size_{0},
        moving_sum_{0},
        moving_average_{0} {}

  double next(int val) {
    current_index_ = (current_index_ + 1) % capacity_;
    int& value     = data_[current_index_];
    moving_sum_ += val - value;
    size_           = size_ < capacity_ ? size_ + 1 : capacity_;
    moving_average_ = moving_sum_ / size_;
    value           = val;
    return moving_average_;
  }

 private:
  uint32_t               capacity_;
  std::unique_ptr<int[]> data_;  // NOLINT - allow c style array
  uint32_t               current_index_;
  uint32_t               size_;
  double                 moving_sum_;
  double                 moving_average_;
};

}  // namespace LaPointe_Algorithms::leet
