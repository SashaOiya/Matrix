#include <gtest/gtest.h>

#include "buffer.hpp"

TEST(array, copy_ctor) {
    detail::Array<double> array = {1, 2, 3, 4, 6, 7, 8, 12, 1};
    detail::Array<double> lhs = array;

    EXPECT_TRUE(array.size() == lhs.size());
    const std::size_t size = array.size();
    for (std::size_t i = 0; i < size; ++i) EXPECT_EQ(array[i], lhs[i]);
}

TEST(array, copy_assignment) {
    detail::Array<double> array = {2, 3, 5, 6};

    detail::Array<double> lhs = {0};
    lhs = array;

    EXPECT_TRUE(array.size() == lhs.size());
    auto size = array.size();
    for (size_t i = 0; i < size; ++i) EXPECT_EQ(array[i], lhs[i]);
}

TEST(array, move_ctor) {
    detail::Array<double> array = {-4, 9, 6, 4, -11, 0, 7, 4, 5};

    std::vector<double> data = {};
    const std::size_t size = array.size();
    for (std::size_t i = 0; i < size; ++i) {
        data.push_back(array[i]);
    }
    detail::Array<double> lhs = std::move(array);

    for (size_t i = 0; i < size; ++i) EXPECT_EQ(data[i], lhs[i]);
}

TEST(array, move_assignment) {
    detail::Array<double> array = {-4, 9, 6, 4, -11, 0, 7, 4, 5};

    std::vector<double> data = {};
    const std::size_t size = array.size();
    for (std::size_t i = 0; i < size; ++i) {
        data.push_back(array[i]);
    }
    detail::Array<double> lhs = {0};
    lhs = std::move(array);

    for (size_t i = 0; i < size; ++i) EXPECT_EQ(data[i], lhs[i]);
}
