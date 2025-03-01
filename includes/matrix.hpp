#pragma once

#include <cmath>
#include <iostream>
#include <stdexcept>

#include "buffer.hpp"

template <typename T>
	requires std::is_same_v<T, double>
class Matrix final : private Array<T> {
	static constexpr double kEpsilon = 1.0e-9;
	using Array<T>::data_;
	using Array<T>::size_;
	std::size_t rows_;
	std::size_t cols_;

	template <typename Data_t>
	struct Proxy_Row {
		Data_t* row;
		Data_t& operator[](std::size_t j) const {
			return row[j];
		}
	};

   public:
	using Array<T>::size;
	using typename Array<T>::size_type;
	Matrix(std::size_t n_rows, std::size_t n_cols)
		: Array<T>(n_rows * n_cols), rows_(n_rows), cols_(n_cols) {
	}

	Matrix(std::size_t n_rows, std::size_t n_cols, std::initializer_list<T> l)
		: Array<T>(n_rows * n_cols), rows_(n_rows), cols_(n_cols) {
		if (l.size() != size()) {
			throw std::invalid_argument("Incorrect initializer list size");
		}
		std::copy(l.begin(), l.end(), data_);
	}

	//=========================================================================================================
	Proxy_Row<T> operator[](size_type i) {
		return Proxy_Row<T>{data_ + cols_ * i};
	}
	Proxy_Row<const T> operator[](size_type i) const {
		return Proxy_Row<const T>{data_ + cols_ * i};
	}

	size_type n_cols() const noexcept {
		return cols_;
	}

	size_type n_rows() const noexcept {
		return rows_;
	}

	double determinant() const {
		if (rows_ != cols_) {
			throw std::runtime_error("Determinant is only defined for square matrices");
		}

		Matrix<T> triangular_matrix = *this;
		double det = 1.0;

		for (std::size_t col = 0; col < rows_; col++) {
			auto pivot_row = col;
			for (std::size_t row = col + 1; row < rows_; ++row) {
				if (std::abs(triangular_matrix[row][col]) >
					std::abs(triangular_matrix[pivot_row][col])) {
					pivot_row = row;
				}
			}

			if (std::fabs(triangular_matrix[pivot_row][col]) < kEpsilon) {
				return 0.0;
			}

			if (col != pivot_row) {
				triangular_matrix.swap_rows(col, pivot_row);
				det *= -1;
			}

			det *= triangular_matrix[col][col];

			for (std::size_t row = col + 1; row < rows_; ++row) {
				double elimination_factor =
					triangular_matrix[row][col] / triangular_matrix[col][col];
				for (std::size_t j = col; j < cols_; ++j) {
					triangular_matrix[row][j] -= elimination_factor * triangular_matrix[col][j];
				}
			}
		}

		return det;
	}

	Matrix& negate() & {
		auto size = size();
		for (std::size_t i = 0; i < size; ++i) {
			data_[i] *= -1;
		}
		return *this;
	}

	T trace() const {
		T result = 0;
		for (std::size_t i = 0; i < rows_; ++i) {
			result += data_[i * cols_ + i];
		}
		return result;
	}

	bool equal(const Matrix& other) const {
		if (size() != other.size()) {
			return false;
		}
		return std::equal(data_, data_ + size(), other.data_);
	}

   private:
	void swap_rows(std::size_t first, std::size_t second) {
		if (first == second) return;

		T* first_row = data_ + first * cols_;
		T* second_row = data_ + second * cols_;

		std::swap_ranges(first_row, first_row + cols_, second_row);
	}
};

template <typename T>
std::istream& operator>>(std::istream& input_stream, Matrix<T>& matrix) {
	std::size_t col = 0, size = 0;
	const std::size_t cols_ = matrix.n_cols(), rows_ = matrix.n_rows();
	for (T elem = 0; col < cols_; ++col) {
		for (std::size_t row = 0; (row < rows_) && (input_stream >> elem); ++row, ++size) {
			if (!std::cin.good()) {
				throw std::runtime_error("Invalid input");
			}
			matrix[col][row] = elem;
		}
	}
	if (size != matrix.size()) {
		throw std::runtime_error("Invalid number of elements");
	}

	return input_stream;
}
