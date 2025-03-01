#pragma once

#include <utility>

template <typename T>
class Buffer {
   public:
    using pointer = T *;
    using const_pointer = const T *;
    using size_type = std::size_t;

    explicit Buffer(std::size_t capacity)
        : capacity_(capacity),
          data_((capacity_ == 0) ? nullptr
                                 : static_cast<T *>(::operator new(capacity_ * sizeof(T)))) {}

    Buffer(const Buffer &) = delete;
    Buffer &operator=(const Buffer &) = delete;

    Buffer(Buffer &&rhs) noexcept
        : capacity_(std::exchange(rhs.capacity_, 0)),
          size_(std::exchange(rhs.size_, 0)),
          data_(std::exchange(rhs.data_, nullptr)) {}
    Buffer &operator=(Buffer &&rhs) noexcept {
        swap(rhs);
        return *this;
    }

    void swap(Buffer &rhs) noexcept {
        std::swap(size_, rhs.size_);
        std::swap(capacity_, rhs.capacity_);
        std::swap(data_, rhs.data_);
    }

   protected:
    std::size_t capacity_;
    std::size_t size_ = 0;
    T *data_;

    ~Buffer() {
        std::destroy(data_, data_ + size_);
        ::operator delete(data_);
    }
};

template <typename T>
class Array : private Buffer<T> {
   protected:
    using Buffer<T>::data_;
    using Buffer<T>::size_;
    using Buffer<T>::capacity_;

   public:
    using typename Buffer<T>::size_type;
    using typename Buffer<T>::pointer;
    using typename Buffer<T>::const_pointer;
    using Buffer<T>::swap;

    using iterator = pointer;
    using const_iterator = const_pointer;

    template <std::forward_iterator It>
    Array(It first, It last) : Buffer<T>{static_cast<size_type>(std::distance(first, last))} {
        for (; first != last; ++first, ++size_) {
            std::construct_at(data_ + size_, *first);
        }
    }
    Array(size_type count) : Buffer<T>{count} {
        for (; size_ != count; ++size_) std::construct_at(data_ + size_, T{});
    }

    Array(std::initializer_list<T> ilist) : Array(ilist.begin(), ilist.end()) {}

    Array(const Array &rhs) : Buffer<T>(rhs.capacity_) {
        for (; size_ != capacity_; ++size_) std::construct_at(data_ + size_, rhs[size_]);
    }

    Array &operator=(const Array &rhs) {
        Array lhs{rhs};
        swap(lhs);

        return *this;
    }

    Array(Array &&) = default;
    Array &operator=(Array &&) = default;

    const T &operator[](size_type i) const { return data_[i]; }
    T &operator[](size_type i) { return data_[i]; }
    size_type size() const noexcept { return size_; }

    iterator begin() noexcept { return data_; }
    const_iterator begin() const noexcept { return data_; }
    iterator end() noexcept { return data_ + size_; }
    const_iterator end() const noexcept { return data_ + size_; }
};