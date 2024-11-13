#pragma once

#include <cstddef>
#include <utility>

template<typename T>
class Buffer
{
protected:
        int    rows_;
        int    cols_;
        size_t size_;
        T*     data_;

public :
    Buffer ( int n_rows, int n_cols) : rows_(n_rows), cols_(n_cols), size_(n_rows * n_cols)
    {
        data_ = static_cast<T *>( ::operator new ( size_ * sizeof (T) ) );
    }

    Buffer ( const Buffer &buffer ) = delete;
    Buffer& operator= ( Buffer &buffer ) = delete;

    Buffer ( Buffer &&rhs ) noexcept { move (rhs ); }
    Buffer& operator= ( Buffer &&rhs ) noexcept
    {
        move ( rhs );
        return *this;
    }

    ~Buffer () { delete data_; }

protected:
    void move ( Buffer &buffer ) noexcept
    {
        std::swap ( rows_, buffer.rows_ );
        std::swap ( cols_, buffer.cols_ );
        std::swap ( size_, buffer.size_ );
        std::move ( data_, buffer.data_ );
    }

    size_t size () const { return size_; }

};