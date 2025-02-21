#include <gtest/gtest.h>

#include "matrix.hpp"

TEST(test1, test1_matrix_copy_ctor) {
    Matrix<double> matrix = {3, 3, {1, 2, 3, 4, 6, 7, 8, 12, 1}};
    Matrix<double> lhs = matrix;

    EXPECT_TRUE(matrix.size() == lhs.size());
    auto cols_ = matrix.n_cols(), rows_ = matrix.n_rows();
    for (size_t i = 0; i < cols_; ++i)
        for (auto j = 0; j < rows_; ++j) EXPECT_EQ(matrix[i][j], lhs[i][j]);
}

TEST(test2, test2_matrix_copy_ctor) {
    Matrix<double> matrix = {2, 2, {2, 3, 5, 6}};

    Matrix<double> lhs = {};
    lhs = matrix;

    EXPECT_TRUE(matrix.size() == lhs.size());
    auto cols_ = matrix.n_cols(), rows_ = matrix.n_rows();
    for (size_t i = 0; i < cols_; ++i)
        for (auto j = 0; j < rows_; ++j) EXPECT_EQ(matrix[i][j], lhs[i][j]);
}

TEST(test3, test_matrix_move_ctor) {
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

TEST(test4, test_matrix_move_assignment) {
    Matrix<double> matrix = {3, 3, {5, 8, 9, 12, 3, -4, 67, 18, -5}};

    std::vector<std::vector<double>> data = {};
    const int cols_ = matrix.n_cols(), rows_ = matrix.n_rows();
    for (size_t i = 0; i < cols_; ++i) {
        std::vector<double> row = {};
        for (auto j = 0; j < rows_; ++j) row.push_back(matrix[i][j]);
        data.push_back(row);
    }

    Matrix<double> lhs = {};
    lhs = std::move(matrix);

    for (size_t i = 0; i < cols_; ++i)
        for (auto j = 0; j < rows_; ++j) EXPECT_EQ(data[i][j], lhs[i][j]);
}

TEST(test5, test_matrix_equal_true) {
    Matrix<double> matrix = {3, 3, {5, 8, 9, 12, 3, -4, 67, 18, -5}};
    Matrix<double> lhs = matrix;

    EXPECT_TRUE(matrix.equal(lhs));
}

TEST(test7, test_matrix_equal_true) {
    Matrix<double> matrix = {3, 3, {5, 8, 9, 12, 3, -4, 67, 18, -5}};
    Matrix<double> matrix_2 = {3, 3, {5, 8, 9, 12, 3, -4, 67, 18, 10}};

    EXPECT_FALSE(matrix.equal(matrix_2));
}