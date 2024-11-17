#pragma once

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <utility>

#include "buffer.hpp"

template<typename T>
class Matrix final: private Buffer<T> {
    const double epsilon = 1.0e-9;
    using Buffer<T>::size_;
    using Buffer<T>::data_;
    size_t rows_;
    size_t cols_;

    template <typename  U> // *U
    struct Proxy_Row {
        T *row;
        U& operator[] ( int j ) noexcept { return row[j]; }
    };

public:
    Matrix () : rows_(0), cols_(0), Buffer<T>() {}

    Matrix ( size_t n_rows, size_t n_cols ) : rows_(n_rows), cols_(n_cols), Buffer<T> ( n_rows, n_cols ) {}

    Matrix ( int n_rows, int n_cols, std::initializer_list<T> l ) : rows_(n_rows), cols_(n_cols), Buffer<T> ( n_rows, n_cols ) {
        int i = 0;
        for ( auto& val : l ) {
            data_[i] = val;
            ++i;
        }
    }

    Matrix ( const Matrix& rhs ) : rows_(rhs.rows_), cols_(rhs.cols_), Buffer<T> ( rhs.rows_, rhs.cols_ )
    {
        for ( size_t i = 0; i < size_; ++i ) {
            data_[i] = rhs.data_[i];
        }
    }

    Matrix& operator= ( const Matrix &rhs )
    {
        Matrix lhs {rhs};
        cols_ = rhs.cols_;
        rows_ = rhs.rows_;
        size_ = rhs.size_;
        data_ = std::exchange ( lhs.data_, nullptr );

        return *this;
    }

    Matrix ( Matrix &&rhs ) noexcept : rows_(rhs.rows_), cols_(rhs.cols_), Buffer<T> ( rhs.rows_, rhs.cols_ )
                                     { data_ = std::exchange ( rhs.data_, nullptr ); }

    Matrix& operator= ( Matrix &&rhs ) noexcept
    {
        rows_ = rhs.rows_;
        cols_ = rhs.cols_;
        size_ = rhs.size_;
        data_ = std::exchange ( rhs.data_, nullptr );
        return *this;
    }

//=========================================================================================================
    int n_cols () const noexcept { return cols_; }

    int n_rows () const noexcept { return rows_; }

    size_t size () const { return size_; }

    T* data() const noexcept { return data_; }

    // Вычисление определителя методом Гаусса
    double determinant() const
    {
        if ( rows_ != cols_ ) {
            //throw invalid_argument("Determinant is only defined for square matrices");
            return 0; // error
        }

        Matrix<double> triangular_matrix = *this;
        double det = 1.0;

        for ( size_t col = 0; col < rows_; col++ ) {
            // Ищем ведущую строку (pivotRow) для текущего столбца
            int pivot_row = col;
            for ( size_t row = col + 1; row < rows_; ++row ) {
                if ( std::abs ( triangular_matrix[row][col] ) > std::abs ( triangular_matrix[pivot_row][col] ) ) {
                    pivot_row = row;
                }
            }

            // Если ведущий элемент равен нулю, определитель матрицы равен нулю
            if ( std::fabs ( triangular_matrix[pivot_row][col] ) < epsilon ) {
                return 0.0;
            }

            // Меняем местами текущую строку и ведущую строку, если они разные
            if ( col != pivot_row ) {
                triangular_matrix.swap_rows( col, pivot_row );
                det *= -1;
            }

            det *= triangular_matrix[col][col];

            // Обнуляем элементы ниже ведущего элемента в текущем столбце
            for ( size_t row = col + 1; row < rows_; ++row ) {
                double elimination_factor = triangular_matrix[row][col] / triangular_matrix[col][col];
                for ( size_t j = col; j < cols_; ++j ) {
                    triangular_matrix[row][j] -= elimination_factor * triangular_matrix[col][j];
                }
            }
        }

        return det;
    }

    Matrix& negate () &
    {
        for ( size_t i = 0; i < size_; ++i ) {
            data_[i] *= -1;
        }
        return *this;
    }

    T trace() const
    {
        T result = 0;
        for ( size_t i = 0; i < rows_; ++i ) {
            result += data_[i * cols_ + i];
        }
        return result;
    }

    bool equal ( const Matrix& other ) const
    {
        if ( rows_ != other.rows_ || cols_ != other.cols_ || size_ != other.size_ ) {
            return false;
        }
        assert ( data_ != nullptr && other.data_ != nullptr  );
        for ( size_t i = 0; i < size_; ++i ) {
            if ( data_[i] != other.data_[i] ) { return false; }
        }
        return true;
    }
//======================================================================================================
    Proxy_Row<T> operator[] ( const int i ) { return Proxy_Row<T>{ data_ + cols_ * i }; }

    std::istream& operator >> ( std::istream &input_stream ) {
        int size = 0;
        for ( T elem = 0; ( input_stream >>elem)  && size < size_; ++size ) {
            data_[size] = elem;
        }
        if ( size != size_ ) { throw /**/ ; }

        return input_stream;
    }
//=========================================================================================================

private:
    void swap_rows ( int first, int second ) {
        if ( first == second )
            return;

        T* first_row  = data_ + first  * cols_;
        T* second_row = data_ + second * cols_;

        for ( size_t i = 0; i < cols_; ++i ) {
            std::swap ( first_row[i], second_row[i] );
        }
    }

};
