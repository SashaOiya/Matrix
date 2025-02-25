#include <gtest/gtest.h>

#include "matrix.hpp"

TEST(matrix, init_list_check) {
    Matrix<double> matrix = {3, 3, {1, 2, 3, 4, 6, 7, 8, 12, 1}};

    EXPECT_TRUE(matrix.size() == 9);
}

TEST(array, copy_ctor) {
    Array<double> array = {1, 2, 3, 4, 6, 7, 8, 12, 1};
    Array<double> lhs = array;

    EXPECT_TRUE(array.size() == lhs.size());
	const std::size_t size = array.size();
	for (std::size_t i = 0; i < size; ++i)
		EXPECT_EQ(array[i], lhs[i]);
}

TEST(array, copy_assignment) {
    Array<double> array = {2, 3, 5, 6};

    Array<double> lhs = {0};
    lhs = array;

    EXPECT_TRUE(array.size() == lhs.size());
	auto size = array.size();
	for (size_t i = 0; i < size; ++i)
		EXPECT_EQ(array[i], lhs[i]);
}

TEST(array, move_ctor) {
    Array<double> array = {-4, 9, 6, 4, -11, 0, 7, 4, 5};

    std::vector<double> data = {};
	const std::size_t size = array.size();
	for (std::size_t i = 0; i < size; ++i) {
        data.push_back(array[i]);
	}
	Array<double> lhs = std::move(array);

    for (size_t i = 0; i < size; ++i)
        EXPECT_EQ(data[i], lhs[i]);
}

TEST(array, move_assignment) {
    Array<double> array = {-4, 9, 6, 4, -11, 0, 7, 4, 5};

    std::vector<double> data = {};
	const std::size_t size = array.size();
	for (std::size_t i = 0; i < size; ++i) {
        data.push_back(array[i]);
	}
	Array<double> lhs = {0};
	lhs = std::move(array);

	for (size_t i = 0; i < size; ++i)
        EXPECT_EQ(data[i], lhs[i]);
}

TEST(matrix, copy_ctor) {
    Matrix<double> matrix = {3, 3, {-4, 9, 6, 4, -11, 0, 7, 4, 5}};
    Matrix<double> lhs = matrix;

    EXPECT_TRUE(matrix.size() == lhs.size());
	auto cols_ = matrix.n_cols(), rows_ = matrix.n_rows();
	for (size_t i = 0; i < cols_; ++i)
        for (auto j = 0; j < rows_; ++j) EXPECT_EQ(matrix[i][j], lhs[i][j]);
}

TEST(matrix, copy_assignment) {
    Matrix<double> matrix = {3, 3, {-4, 9, 6, 4, -11, 0, 7, 4, 5}};
    Matrix<double> lhs = {0,0};
	lhs = matrix;

	EXPECT_TRUE(matrix.size() == lhs.size());
	auto cols_ = matrix.n_cols(), rows_ = matrix.n_rows();
	for (size_t i = 0; i < cols_; ++i)
        for (auto j = 0; j < rows_; ++j) EXPECT_EQ(matrix[i][j], lhs[i][j]);
}

TEST(matrix, move_ctor) {
    Matrix<double> matrix = {3, 3, {-4, 9, 6, 4, -11, 0, 7, 4, 5}};

    std::vector<std::vector<double>> data = {};
    const int cols_ = matrix.n_cols(), rows_ = matrix.n_rows();
    for (size_t i = 0; i < cols_; ++i) {
        std::vector<double> row = {};
        for (auto j = 0; j < rows_; ++j) row.push_back(matrix[i][j]);
        data.push_back(row);
    }
    Matrix<double> lhs = std::move(matrix);

    for (size_t i = 0; i < cols_; ++i)
        for (auto j = 0; j < rows_; ++j) EXPECT_EQ(data[i][j], lhs[i][j]);
}

TEST(matrix, move_assignment) {
    Matrix<double> matrix = {3, 3, {5, 8, 9, 12, 3, -4, 67, 18, -5}};

    std::vector<std::vector<double>> data = {};
    const int cols_ = matrix.n_cols(), rows_ = matrix.n_rows();
    for (size_t i = 0; i < cols_; ++i) {
        std::vector<double> row = {};
        for (auto j = 0; j < rows_; ++j) row.push_back(matrix[i][j]);
        data.push_back(row);
    }

    Matrix<double> lhs = {0, 0};
    lhs = std::move(matrix);

    for (size_t i = 0; i < cols_; ++i)
        for (auto j = 0; j < rows_; ++j) EXPECT_EQ(data[i][j], lhs[i][j]);
}

TEST(matrix, equal_true) {
    Matrix<double> matrix = {3, 3, {5, 8, 9, 12, 3, -4, 67, 18, -5}};
    Matrix<double> lhs = matrix;

    EXPECT_TRUE(matrix.equal(lhs));
}

TEST(matrix, equal_false) {
    Matrix<double> matrix = {3, 3, {5, 8, 9, 12, 3, -4, 67, 18, -5}};
    Matrix<double> matrix_2 = {3, 3, {5, 8, 9, 12, 3, -4, 67, 18, 10}};

    EXPECT_FALSE(matrix.equal(matrix_2));
}