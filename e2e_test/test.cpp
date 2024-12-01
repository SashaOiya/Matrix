#include <gtest/gtest.h>
//#include <benchmark/benchmark.h>

#include "funcs.hpp"

TEST(test1, data)
{
	test_funcs::run_test("/test1/");
}

TEST(test2, data2)
{
	test_funcs::run_test("/test2/");
}

TEST(test3, data3)
{
	test_funcs::run_test("/test3/");
}

TEST(test4, data4)
{
	test_funcs::run_test("/test4/");
}
/*	static void BM_StringCreation(benchmark::State& state) {
		for (auto _ : state) {
			std::string test_path = std::string ( TEST_DATA_DIR ) + "/tests" + "/test4/";

			double res = test_funcs::get_result ( test_path + "data.txt" );
    	}
    }
BENCHMARK(BM_StringCreation);

BENCHMARK_MAIN(); */