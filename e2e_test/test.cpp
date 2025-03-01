#include <gtest/gtest.h>

#include "funcs.hpp"

TEST(test1, e2e_test_data1) { test_funcs::run_test("/test1/"); }

TEST(test2, e2e_test_data2) { test_funcs::run_test("/test2/"); }

TEST(test3, e2e_test_data3) { test_funcs::run_test("/test3/"); }

TEST(test4, e2e_test_data14) { test_funcs::run_test("/test4/"); }