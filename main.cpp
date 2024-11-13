#include "includes/matrix.hpp"
#include <iostream>

int main ()
{
    int size;
    std::cin >> size;
    if ( size <= 0 ) {
        std::cout << "Error: invalid size\n";
        return EXIT_FAILURE;
    }
    Matrix<int> matrix { size, size };

    matrix>>(std::cin);

    std::cout << matrix.determinant ();

    return 0;
}