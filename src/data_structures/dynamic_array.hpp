#pragma once

#include <cstddef>
#include <cstdlib>
#include <new>

namespace LaPointe_Algorithms::data_structures {

template <typename type_T>
class Dynamic_Array {
 public:
  using value_type      = type_T;
  using size_type       = size_t;
  using reference       = value_type &;
  using const_reference = value_type const &;
  using pointer         = value_type *;
  using const_pointer   = value_type const *;
  using difference_type = ptrdiff_t;

  Dynamic_Array() {}

  explicit Dynamic_Array(size_type capactiy) : capactiy_{capactiy}, head_{allocate_new_space(capactiy)} {
    if (head_ == nullptr) {
      throw std::bad_array_new_length();
    }
  }

 private:
  static constexpr std::size_t DEFAULT_CAPACITY{8};
  size_type                    capactiy_{DEFAULT_CAPACITY};
  pointer                      head_{nullptr};
  pointer                      tail_{nullptr};
  pointer                      end_of_storage_{nullptr};
  static constexpr double      growth_factor_{2.0};

  pointer                      allocate_new_space(size_type n) {
                         // ensure not constructing an empty type
    static_assert(sizeof(value_type) != 0, "cannot allocate incomplete types");

    // ensure now constucting something too big
    if (n > static_cast<std::size_t>(__PTRDIFF_MAX__) / sizeof(value_type)) {
                           if (n > (static_cast<std::size_t>(-1) / sizeof(value_type))) {
                             throw std::bad_array_new_length();
      }
                           throw std::bad_alloc();
    }

    // ensure proper aligned construction
    if (alignof(value_type) > __STDCPP_DEFAULT_NEW_ALIGNMENT__) {
                           std::align_val_t new_align_val = static_cast<std::align_val_t>(alignof(value_type));
                           return static_cast<pointer>(::operator new(n * sizeof(value_type), new_align_val));
    }

    // default construction
    return static_cast<pointer>(::operator new(n * sizeof(size_type)));
  }
};

}  // namespace LaPointe_Algorithms::data_structures
