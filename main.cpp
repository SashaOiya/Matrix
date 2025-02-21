#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "includes/matrix.hpp"

int main() try {
    using KeyT = double;

    int size;
    std::cin >> size;
    if (size <= 0) {
        throw std::runtime_error("Error: invalid size\n");
    }

    Matrix<KeyT> matrix{static_cast<std::size_t>(size), static_cast<std::size_t>(size)};
    std::cin >> matrix;

    std::cout << matrix.determinant() << '\n';

    return 0;
} catch (const std::exception& expt) {
    std::cerr << expt.what() << std::endl;
    return EXIT_FAILURE;
} catch (...) {
    std::cerr << "Caught unknown exception\n";
    return EXIT_FAILURE;
}