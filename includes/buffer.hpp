#pragma once

#include <cstddef>
#include <utility>

template<typename T>
class Buffer
{
public :
    Buffer ( int n_rows, int n_cols) : size_(n_rows * n_cols)
    {
        data_ = static_cast<T *>( ::operator new ( size_ * sizeof (T) ) );
    }

    Buffer ( const Buffer &buffer ) = delete;
    Buffer& operator= ( const Buffer &buffer ) = delete;

    Buffer ( Buffer &&rhs ) noexcept { move (rhs ); }
    Buffer& operator= ( Buffer &&rhs ) noexcept
    {
        move ( rhs );
        return *this;
    }

protected:
    size_t size_;
    T*     data_;

    ~Buffer () { delete data_; }

    void move ( Buffer &&buffer ) noexcept
    {
        size_ = buffer.size_;
        data_ = std::move ( buffer.data_ );
    }

    void copy ( Buffer &buffer ) noexcept
    {
        size_ = buffer.size_;
        for ( size_t i = 0; i < size_; ++i ) {
            data_[i] = buffer.data_[i];
        }
    }

    size_t size () const { return size_; }

};