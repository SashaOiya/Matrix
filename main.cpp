#include "includes/matrix.hpp"
#include <iostream>

int main ()
{
    using KeyT = double;

    int size;
    std::cin >> size;
    if ( size <= 0 ) {
        std::cout << "Error: invalid size\n";
        return EXIT_FAILURE;
    }
    Matrix<KeyT> matrix { static_cast<size_t>(size), static_cast<size_t>(size) };
    matrix >> ( std::cin );

    std::cout  << matrix.determinant () << '\n';
    //printf ( "%f\n", matrix.determinant () );

    return 0;
}