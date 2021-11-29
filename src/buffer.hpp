
#include <array>
#include <cstddef>
#include <cstdint>

template <typename type_T, uint32_t capactiy_T> class Buffer
{
public:
    using value_type = type_T;
    using size_type = size_t;
    using reference = value_type &;
    using const_reference = value_type const &;

    size_type size() const noexcept { return size_; }
    size_type max_size() const noexcept { return capacity_; }
    size_type capacity() const noexcept { return capacity_; }

    bool empty() const noexcept { return size() == 0UL; }
    bool full() const noexcept { return size() == capacity(); }

    reference front() { return raw_buffer_[0]; }
    const_reference front() const { return raw_buffer_[0]; }

    reference at(size_type n)
    {
        assert(n < size());
        if (n < size())
            return raw_buffer_[n];
    }
    const_reference at(size_type n) const
    {
        assert(n < size());
        if (n < size())
            return raw_buffer_[n];
    }
    reference operator[](size_type n) { return at(n); }
    const_reference operator[](size_type n) const { return at(n); }

    reference back() { return raw_buffer_[size_ - 1]; }
    const_reference back() const { return raw_buffer_[size_ - 1]; }

    void push_back(const value_type &val)
    {
        assert(!full());
        if (!full())
        {
            raw_buffer_[size()] = val;
            size_++;
        }
    }
    void push_back(value_type &&val)
    {
        assert(!full());
        if (!full())
        {
            raw_buffer_[size()] = val;
            size_++;
        }
    }

    void pop_back()
    {
        if (!empty())
        {
            size_--;
        }
    }

private:
    size_type size_;
    static constexpr size_type capacity_ = capactiy_T;
    std::array<value_type, capacity_> raw_buffer_;
};