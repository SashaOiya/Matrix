#include <gtest/gtest.h>
#include "matrix.hpp"

TEST ( test1, test1_unit )
{
	Matrix<double> matrix = { 3, 3, {1, 2, 3, 4, 6, 7, 8, 12, 1}};
	Matrix<double> lhs = matrix;

	EXPECT_TRUE ( matrix.size() == lhs.size() );
	size_t size = matrix.size();
	for ( size_t i = 0; i < size; ++i ) {
		EXPECT_EQ ( matrix.data()[i] , lhs.data()[i] );
	}
}

TEST ( test2, test2_unit )
{
	Matrix<double> matrix = { 2, 2, { 2, 3, 5, 6 } };

	Matrix<double> lhs = {};
	lhs = matrix;

	EXPECT_TRUE( matrix.size() == lhs.size() );
	size_t size = matrix.size();
	for ( size_t i = 0; i < size; ++i ) {
		EXPECT_EQ ( matrix.data()[i] , lhs.data()[i] );
	}
}

TEST ( test3, test3_unit )
{
	Matrix<double> matrix = { 3, 3, {-4, 9, 6, 4, -11, 0, 7, 4, 5} };

	std::vector<double> data = {};
    size_t matrix_size = matrix.size();
	for ( size_t i = 0; i < matrix_size; ++i ) {
		data.push_back ( matrix.data()[i] );
	}

	Matrix<double> lhs = std::move ( matrix );

	EXPECT_TRUE ( data.size() == lhs.size() );
    size_t size = data.size();
	for ( size_t i = 0; i < size; ++i ) {
		EXPECT_EQ ( data[i] , lhs.data()[i] );
	}
}

TEST ( test4, test4_unit )
{
	Matrix<double> matrix = { 3, 3, { 5, 8, 9, 12, 3, -4, 67, 18, -5 } };

	std::vector<double> data = {};
	size_t matrix_size = matrix.size();
	for ( size_t i = 0; i < matrix_size; ++i ) {
		data.push_back ( matrix.data()[i] );
	}

	Matrix<double> lhs = {};
	lhs = std::move ( matrix );

	EXPECT_TRUE(data.size() == lhs.size());
	size_t size = data.size();
	for ( size_t i = 0; i < size; ++i ) {
		EXPECT_EQ ( data[i] , lhs.data()[i] );
	}
}

TEST ( test5, test5_unit )
{
	Matrix<double> matrix = { 3, 3, { 5, 8, 9, 12, 3, -4, 67, 18, -5 } };
	Matrix<double> lhs = matrix;

    EXPECT_TRUE(matrix.equal ( lhs ));
}

TEST ( test6, test6_unit )
{
	Matrix<double> matrix = { 3, 3, { 5, 8, 9, 12, 3, -4, 67, 18, -5 } };
	Matrix<double> matrix_2 = matrix;

    EXPECT_TRUE(matrix.equal ( matrix_2 ));
}

TEST ( test7, test7_unit )
{
	Matrix<double> matrix = { 3, 3, { 5, 8, 9, 12, 3, -4, 67, 18, -5 } };
	Matrix<double> matrix_2 = { 3, 3, { 5, 8, 9, 12, 3, -4, 67, 18, 10 } };

    EXPECT_FALSE(matrix.equal ( matrix_2 ));
}