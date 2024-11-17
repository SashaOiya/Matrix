#include <gtest/gtest.h>
#include "matrix.hpp"

/*TEST ( test1, test1_unit )
{
	Matrix<double> matrix = { 3, 3, {-4, 9, 6, 4, -11, 0, 7, 4, 5} };

	std::vector<double> data = {};
    size_t matrix_size = matrix.size();
	for ( size_t i = 0; i < matrix_size; ++i ) {
		data.push_back ( matrix.data()[i] );
	}

	Matrix<double> lhs = std::move ( matrix );

	EXPECT_TRUE ( matrix.size() == lhs.size() );
    size_t size = matrix.size();
	for ( size_t i = 0; i < size; ++i ) {
		EXPECT_EQ ( matrix.data()[i] , lhs.data()[i] );
	}
}*/

TEST ( test2, test2_unit )
{
	Matrix<double> matrix = { 3, 3, {1, 2, 3, 4, 6, 7, 8, 12, 1}};
	Matrix<double> lhs = matrix;

	EXPECT_TRUE ( matrix.size() == lhs.size() );
	size_t size = matrix.size();
	for ( size_t i = 0; i < size; ++i ) {
		EXPECT_EQ ( matrix.data()[i] , lhs.data()[i] );
	}
}

/*TEST ( test3, test3_unit )
{
	Trees::SearchTree<int, int> tree = { 3, 6, 9, 1, 5, 10, 22 };

	std::vector<int> data = {};
	for ( auto itt : tree ) {
		data.push_back ( itt );
	}

	Trees::SearchTree<int, int> lhs = {};
	lhs = tree;

	EXPECT_TRUE(data.size() == lhs.size());
	auto itt_lhs = lhs.begin();
	for ( auto itt = data.begin(), end = data.end() ; itt != end; ++itt, ++itt_lhs ) {
		EXPECT_EQ ( *itt , *itt_lhs );
	}
}

TEST ( test4, test4_unit )
{
	Trees::SearchTree<int, int> tree = { 5, 8, 9, 12, 3, -4, 67, 18 };

	std::vector<int> data = {};
	for ( auto itt : tree ) {
		data.push_back ( itt );
	}

	Trees::SearchTree<int, int> lhs = {};
	lhs = std::move ( tree );

	EXPECT_TRUE(data.size() == lhs.size());
	auto itt_lhs = lhs.begin();
	for ( auto itt = data.begin(), end = data.end() ; itt != end; ++itt, ++itt_lhs ) {
		EXPECT_EQ ( *itt , *itt_lhs );
	}
}*/