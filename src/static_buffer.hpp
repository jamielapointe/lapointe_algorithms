
#pragma once

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace LaPointe_Algorithms {
template <typename type_T, std::size_t capactiy_T>
class Buffer {
 public:
  using value_type      = type_T;
  using size_type       = std::size_t;
  using reference       = value_type &;
  using const_reference = value_type const &;
  using pointer         = value_type *;
  using const_pointer   = value_type const *;
  using buffer_type     = std::array<value_type, capactiy_T>;

  Buffer() : head_{&raw_buffer_[0]}, tail_{&raw_buffer_[0]} {}

  size_type       size() const noexcept { return size_; }
  size_type       max_size() const noexcept { return capacity_; }
  size_type       capacity() const noexcept { return capacity_; }

  bool            empty() const noexcept { return size() == 0UL; }
  bool            full() const noexcept { return size() == capacity(); }

  reference       front() { return raw_buffer_[0]; }
  const_reference front() const { return raw_buffer_[0]; }

  reference       at(size_type n) {
          assert(n < size());
          if (n < size()) {
            return raw_buffer_[n];
    }
          return back();
  }
  const_reference at(size_type n) const {
    assert(n < size());
    if (n < size()) {
      return raw_buffer_[n];
    }
    return back();
  }
  reference       operator[](size_type n) { return at(n); }
  const_reference operator[](size_type n) const { return at(n); }

  reference       back() { return raw_buffer_[size_ - 1]; }
  const_reference back() const { return raw_buffer_[size_ - 1]; }

  void            push_back(const value_type &val) {
               assert(!full());
               if (!full()) {
                 raw_buffer_[size()] = val;
                 size_++;
    }
  }

  void push_back(value_type &&val) {
    assert(!full());
    if (!full()) {
      raw_buffer_[size()] = val;
      size_++;
    }
  }

  void pop_back() {
    if (!empty()) {
      size_--;
    }
  }

 private:
  static constexpr size_type              capacity_{capactiy_T};
  [[__gnu__::__aligned__(8)]] buffer_type raw_buffer_{0};
  size_type                               size_{0};
  pointer                                 head_;
  pointer                                 tail_;
};

}  // namespace LaPointe_Algorithms
