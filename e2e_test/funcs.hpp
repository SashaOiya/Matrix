#pragma once

#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "matrix.hpp"

namespace test_funcs {
static constexpr double epsilon = 1.0e-5;
using KeyT = double;

double get_result(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::invalid_argument("Open file");
    }

    std::size_t size;
    file >> size;
    if (!file.good()) {
        throw std::runtime_error("Reading size");
    }

    Matrix<KeyT> matrix{size, size};

    file >> matrix;

    return matrix.determinant();
}

double get_answer(const std::string& filename) {
    std::ifstream answer_file(filename);

    KeyT answer;
    answer_file >> answer;
    if (!answer_file.good()) {
        throw std::runtime_error("Invalid tests name");
    }

    return answer;
}

static void run_test(const std::string& test_name) {
    std::string test_directory = "/tests";
    std::string test_path = std::string(TEST_DATA_DIR) + test_directory + test_name;

    double res = get_result(test_path + "data.txt");
    double ans = get_answer(test_path + "ans.txt");

    EXPECT_TRUE(std::fabs(res - ans) < epsilon);
}
}  // namespace test_funcs