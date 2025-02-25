#pragma once

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "buffer.hpp"

template <typename T>
class Matrix final : private Array<T> {
	static constexpr double epsilon = 1.0e-9;
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
	Matrix(std::size_t n_rows, std::size_t n_cols)
		: Array<T>(n_rows * n_cols), rows_(n_rows), cols_(n_cols) {
	}

	Matrix(std::size_t n_rows, std::size_t n_cols, std::initializer_list<T> l)
		: rows_(n_rows), cols_(n_cols), Array<T>(n_rows * n_cols) {
		if ((l.size() > rows_ * cols_) || (l.size() < rows_ * cols_)) {
			throw std::runtime_error("Incorrect initializer list size");
		}
		std::size_t i = 0;
		for (auto& val : l) {
			data_[i] = val;
			++i;
		}
	}

	//=========================================================================================================
	Proxy_Row<T> operator[](const std::size_t i) {
		return Proxy_Row<T>{data_ + cols_ * i};
	}
	Proxy_Row<const T> operator[](const std::size_t i) const {
		return Proxy_Row<const T>{data_ + cols_ * i};
	}

	int n_cols() const noexcept {
		return cols_;
	}

	int n_rows() const noexcept {
		return rows_;
	}

	double determinant() const {
		if (rows_ != cols_) {
			throw std::runtime_error("Determinant is only defined for square matrices");
		}

		Matrix<double> triangular_matrix = *this;
		double det = 1.0;

		for (std::size_t col = 0; col < rows_; col++) {
			int pivot_row = col;
			for (std::size_t row = col + 1; row < rows_; ++row) {
				if (std::abs(triangular_matrix[row][col]) >
					std::abs(triangular_matrix[pivot_row][col])) {
					pivot_row = row;
				}
			}

			if (std::fabs(triangular_matrix[pivot_row][col]) < epsilon) {
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
		const std::size_t size = this->size();
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
		if (rows_ != other.rows_ || cols_ != other.cols_ || size() != other.size()) {
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
	int col = 0, size = 0;
	const int cols_ = matrix.n_cols(), rows_ = matrix.n_rows();
	for (T elem = 0; col < cols_; ++col) {
		for (int row = 0; (row < rows_) && (input_stream >> elem); ++row, ++size) {
			if (!std::cin.good()) {
				throw std::runtime_error("Error: invalid input");
			}
			matrix[col][row] = elem;
		}
	}
	if (size != matrix.size()) {
		throw std::runtime_error("Invalid number of elements");
	}

	return input_stream;
}
