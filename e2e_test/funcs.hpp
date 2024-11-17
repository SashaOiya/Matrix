#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <gtest/gtest.h>

#include "matrix.hpp"

namespace test_funcs
{
    const double epsilon = 1.0e-1;

	double get_result ( const std::string& filename )
    {
        std::ifstream file(filename);
        if (!file) { throw "Error open file\n"; }

        int size;
        file >> size;
        if ( size <= 0 ) {
            //throw "Error: invalid size\n";
        }
        Matrix<double> matrix { static_cast<size_t>(size), static_cast<size_t>(size) };

        matrix >> ( file );

        return matrix.determinant();
    }

    double get_answer ( const std::string& filename )
    {
        std::ifstream answer_file(filename);

        double answer;
        answer_file >> answer;

        return answer;
    }

	void run_test ( const std::string& test_name )
	{
		std::string test_directory = "/tests";
		std::string test_path = std::string ( TEST_DATA_DIR ) + test_directory + test_name;

		double res = get_result ( test_path + "data.txt" );
		double ans = get_answer ( test_path + "ans.txt"  );

        EXPECT_TRUE ( std::fabs ( res - ans ) < epsilon );
	}
}