#include <iostream>
#include <vector>
#include <string>
#include "operations.hpp"
#include "matrix_reader.hpp"

int main() {
    std::string file1, file2, op;

    // Ask for file names
    std::cout << "Enter first matrix file: ";
    std::cin >> file1;

    std::cout << "Enter second matrix file (or 'none' if not needed): ";
    std::cin >> file2;

    // Ask for operation
    std::cout << "Enter operation (add, subtract, multiply, determinant): ";
    std::cin >> op;

    // Read first matrix
    auto mat1_data = read_matrix(file1);
    Matrix m1(mat1_data);

    std::cout << "Matrix 1 size: " << mat1_data.size() << "x" 
              << (mat1_data.empty() ? 0 : mat1_data[0].size()) << std::endl;

    if (op == "determinant") {
        std::cout << "Determinant: " << m1.determinant() << std::endl;
        return 0;
    }

    // For binary operations, read the second matrix
    if (file2 == "none") {
        std::cerr << "Second matrix file required for this operation.\n";
        return 1;
    }
    auto mat2_data = read_matrix(file2);
    Matrix m2(mat2_data);

    std::cout << "Matrix 2 size: " << mat2_data.size() << "x" 
              << (mat2_data.empty() ? 0 : mat2_data[0].size()) << std::endl;

    if (op == "add") {
        Matrix result = m1 + m2;
        std::cout << "Sum:\n";
        for (unsigned i = 0; i < result.getRows(); ++i) {
            for (unsigned j = 0; j < result.getCols(); ++j)
                std::cout << result.at(i, j) << " ";
            std::cout << "\n";
        }
    } else if (op == "subtract") {
        Matrix result = m1 - m2;
        std::cout << "Difference:\n";
        for (unsigned i = 0; i < result.getRows(); ++i) {
            for (unsigned j = 0; j < result.getCols(); ++j)
                std::cout << result.at(i, j) << " ";
            std::cout << "\n";
        }
    } else if (op == "multiply") {
        Matrix result = m1 * m2;
        std::cout << "Product:\n";
        for (unsigned i = 0; i < result.getRows(); ++i) {
            for (unsigned j = 0; j < result.getCols(); ++j)
                std::cout << result.at(i, j) << " ";
            std::cout << "\n";
        }
    } else {
        std::cerr << "Unknown operation.\n";
        return 1;
    }

    return 0;
}