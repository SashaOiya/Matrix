#include "includes/matrix.hpp"
#include <iostream>

int main ()
try
{

    using KeyT = double;

    int size;
    std::cin >> size;
    if ( size <= 0 ) {
        std::cout << "Error: invalid size\n";
        return EXIT_FAILURE;
    }
    Matrix<KeyT> matrix { static_cast<size_t>(size), static_cast<size_t>(size) };
    std::cin >> matrix;

    std::cout  << matrix.determinant () << '\n';
    //printf ( "%f\n", matrix.determinant () );

    return 0;
}
catch (std::exception& expt)
{
    std::cout << expt.what() << std::endl;
    exit (1);
}