#pragma once

#include <cstddef>
#include <utility>

template<typename T>
class Buffer
{
public :
    Buffer () : size_(0), data_(nullptr) {}
    Buffer ( int n_rows, int n_cols) : size_(n_rows * n_cols)
    {
        data_ = static_cast<T *>( ::operator new ( size_ * sizeof (T) ) );
    }

    Buffer ( const Buffer &buffer ) = delete;
    Buffer& operator= ( const Buffer &buffer ) = delete;

    Buffer ( Buffer &&rhs ) : size_ ( rhs.size_), data_ ( std::move ( rhs.data_ )) {}
    Buffer& operator= ( Buffer &&rhs ) noexcept
    {
        size_ = rhs.size_;
        data_ = std::move ( rhs.data_ );
        return *this;
    }

protected:
    size_t size_;
    T*     data_;

    ~Buffer () { delete data_; }

    void copy ( const Buffer &buffer ) noexcept
    {
        size_ = buffer.size_;
        for ( size_t i = 0; i < size_; ++i ) {
            data_[i] = buffer.data_[i];
        }
    }
};