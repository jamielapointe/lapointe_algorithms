/// \brief https://leetcode.com/problems/moving-average-from-data-stream/
///
/// Your MovingAverage object will be instantiated and called as such:
/// MovingAverage* obj = new MovingAverage(size);
/// double param_1 = obj->next(val);
///

#include <cstdint>

namespace LaPointe::Leet {

class MovingAverage {
 public:
  MovingAverage(uint32_t capacity)
      : capacity_{capacity},
        data_{new int[capacity_]()},
        current_index_{0},
        size_{0},
        moving_sum_{0},
        moving_average_{0} {
    clear();
  }

  double next(int val) {
    ++current_index_;
    current_index_ %= capacity_;
    int& value = data_[current_index_];
    moving_sum_ += val - value;
    size_           = size_ < capacity_ ? size_ + 1 : capacity_;
    moving_average_ = moving_sum_ / size_;
    value           = val;
    return moving_average_;
  }

  void clear() {
    size_          = 0;
    current_index_ = 0;
    for (uint32_t i = 0; i < capacity_; ++i) {
      data_[i] = 0;
    }
  }

  ~MovingAverage() {
    if (data_ != nullptr) {
      delete[] data_;
      data_ = nullptr;
    }
  }

  bool is_full() const { return size_ == capacity_; }

  bool is_empty() const { return size_ == 0; }

 private:
  uint32_t capacity_;
  int*     data_;
  uint32_t current_index_;
  uint32_t size_;
  double   moving_sum_;
  double   moving_average_;
};

}  // namespace LaPointe::Leet
