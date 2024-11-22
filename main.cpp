#include "includes/matrix.hpp"
#include <cstdlib>
#include <iostream>

int main () try
{
    using KeyT = double;

    int size;
    std::cin >> size;
    if ( size <= 0 ) {
        std::cerr << "Error: invalid size\n";
        return EXIT_FAILURE;
    }
    Matrix<KeyT> matrix { static_cast<std::size_t>(size), static_cast<std::size_t>(size) };
    std::cin >> matrix;

    std::cout  << matrix.determinant () << '\n';
    //printf ( "%f\n", matrix.determinant () );

    return 0;
}
catch (const std::exception& expt)
{
    std::cerr << expt.what() << std::endl;
    return EXIT_FAILURE;
}