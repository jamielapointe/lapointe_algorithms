#include <cstddef>

template <typename Type, size_t Capacity>
class FixedVector {
 public:
  // ...

 private:
  // ...

  void destroy(Type* first, Type* last) {
    for (; first != last; ++first) {
      first->~Type();
    }
  }

  size_t    size_;
  std::byte raw_[Capacity * sizeof(Type)];
};