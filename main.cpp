#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "matrix.hpp"

int main() try {
	using KeyT = double;

	std::size_t size;
	std::cin >> size;
	if (!std::cin.good()) {
		throw std::runtime_error("Invalid size\n");
	}

	Matrix<KeyT> matrix{size, size};
	std::cin >> matrix;

	std::cout << matrix.determinant() << '\n';

	return 0;
} catch (const std::exception& e) {
	std::cerr << "Error : " << e.what() << '\n';
	return EXIT_FAILURE;
} catch (...) {
	std::cerr << "Caught unknown exception\n";
	return EXIT_FAILURE;
}