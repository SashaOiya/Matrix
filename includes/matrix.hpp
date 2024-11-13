#pragma once

#include <cstdlib>
#include <iostream>

#include "buffer.hpp"

template<typename T>
class Matrix final: private Buffer<T> { // privat
    const double epsilon = 1.0e-7;

    using Buffer<T>::rows_;
    using Buffer<T>::cols_;
    using Buffer<T>::size_;
    using Buffer<T>::data_;

    struct Proxy_Row  {
        T *row;

        T& operator[] ( const int j ) noexcept { return row[j]; }
        const T& operator[] ( const int j ) const noexcept { return row[j]; }
    };

public:
    Matrix ( int n_rows, int n_cols ) : Buffer<T> ( n_rows, n_cols ) {}

    Matrix ( const Matrix& rhs ) : Buffer<T> ( rhs.rows_, rhs.cols_ )
    {
        for ( int i = 0; i < size_; ++i ) { // iterator
            data_[i] = rhs.data_[i];
        }
    }

    Matrix& operator= ( Matrix &rhs )
    {
        Matrix lhs {rhs};
        this->move ( lhs );

        return *this;
    }

    Matrix ( Matrix &&rhs ) noexcept { move ( rhs ); }

    Matrix& operator= ( Matrix &&rhs ) noexcept
    {
        this->move ( rhs );
        return *this;
    }

    ~Matrix () { delete data_; }

//=========================================================================================================
    int n_cols () const noexcept { return cols_; }

    int n_rows () const noexcept { return rows_; }

    // Вычисление определителя методом Гаусса
    double determinant() const
    {
        if ( rows_ != cols_ ) {
            //throw invalid_argument("Determinant is only defined for square matrices");
        }

        Matrix triangular_matrix = *this;
        double det = 1.0;

        for ( int col = 0; col < rows_; col++ ) {
            // Ищем ведущую строку (pivotRow) для текущего столбца
            int pivot_row = col;
            for ( int row = col + 1; row < rows_; ++row ) {
                if ( std::abs ( triangular_matrix[row][col] ) > std::abs ( triangular_matrix[pivot_row][col] ) ) {
                    pivot_row = row;
                }
            }

            // Если ведущий элемент равен нулю, определитель матрицы равен нулю
            if ( std::abs ( triangular_matrix[pivot_row][col] ) < epsilon ) {
                return 0.0;
            }

            // Меняем местами текущую строку и ведущую строку, если они разные
            if ( col != pivot_row ) {
                std::swap ( triangular_matrix.data_[col], triangular_matrix.data_[pivot_row] );
                det *= -1;  // Меняем знак определителя при перестановке строк
            }

            det *= triangular_matrix[col][col];

            // Обнуляем элементы ниже ведущего элемента в текущем столбце
            for ( int row = col + 1; row < rows_; ++row ) {
                double elimination_factor = triangular_matrix[row][col] / triangular_matrix[col][col];
                for ( int j = col; j < cols_; ++j ) {
                    triangular_matrix[row][j] -= elimination_factor * triangular_matrix[col][j];
                }
            }
        }

        return det;
    }
//======================================================================================================
    Proxy_Row operator[] ( const int i ) { return Proxy_Row{ data_ + cols_ * i }; }

    std::istream& operator>> ( std::istream &input_stream ) {
        int size = 0;
        for ( T elem = 0; ( input_stream >>elem)  && size < size_; ++size ) {
            data_[size] = elem;
        }
        if ( size != size_ ) { throw /**/ ; }

        return input_stream;
    }

    /*bool equal ( const Matrix& other )
    {
        if ( rows_ != other.rows_ || cols_ != other.cols_ || size_ != other.size_ ) {
            return false;
        }

        for ( int i = 0; i < size_; ++i ) {

        }
    }*/


};
