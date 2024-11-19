#pragma once

#include <cstddef>
#include <new>
#include <utility>
#include <algorithm>

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

    Buffer ( Buffer &&rhs ) noexcept : size_ ( rhs.size_), data_ ( std::exchange ( rhs.data_, nullptr )) {}
    Buffer& operator= ( Buffer &&rhs ) noexcept
    {
        std::swap ( size_, rhs.size_);
        std::swap ( data_, rhs.data_);
        return *this;
    }

protected:
    size_t size_;
    T*     data_;

    ~Buffer () { ::operator delete( data_ ); }
};