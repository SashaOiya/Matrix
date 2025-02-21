#pragma once

#include <algorithm>
#include <cstddef>
#include <new>
#include <utility>

template <typename T>
class Buffer {
   public:
    Buffer() : size_(0), data_(nullptr) {}
    explicit Buffer(std::size_t size) : size_(size) {
        data_ = (size_ == 0) ? nullptr : static_cast<T *>(::operator new(size_ * sizeof(T)));
    }

    Buffer(const Buffer &buffer) = delete;
    Buffer &operator=(const Buffer &buffer) = delete;

    Buffer(Buffer &&rhs) noexcept : size_(rhs.size_), data_(std::exchange(rhs.data_, nullptr)) {}
    Buffer &operator=(Buffer &&rhs) noexcept {
        std::swap(size_, rhs.size_);
        std::swap(data_, rhs.data_);
        return *this;
    }

   protected:
    std::size_t size_;
    T *data_;

    ~Buffer() {
        ::operator delete(data_);
    }
};