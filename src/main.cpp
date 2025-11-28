#include <iostream>
#include <vector>
#include "operations.hpp"

int main() {
    // Declare matrices directly
    std::vector<std::vector<double>> data1 = {
        {1, 2, 3},
        {4, 5, 6}
    };
    std::vector<std::vector<double>> data2 = {
        {7, 8, 9},
        {10, 11, 12}
    };
    std::vector<std::vector<double>> data5 = {
        {1, 2},
        {3, 4}
    };

    Matrix m1(data1);
    Matrix m2(data2);

    // Addition
    Matrix sum = m1 + m2;
    std::cout << "Sum:\n";
    for (unsigned i = 0; i < sum.getRows(); ++i) {
        for (unsigned j = 0; j < sum.getCols(); ++j)
            std::cout << sum.at(i, j) << " ";
        std::cout << "\n";
    }

    // Subtraction
    Matrix diff = m1 - m2;
    std::cout << "Difference:\n";
    for (unsigned i = 0; i < diff.getRows(); ++i) {
        for (unsigned j = 0; j < diff.getCols(); ++j)
            std::cout << diff.at(i, j) << " ";
        std::cout << "\n";
    }

    // Multiplication (make sure dimensions match)
    std::vector<std::vector<double>> data3 = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    std::vector<std::vector<double>> data4 = {
        {7, 8, 9},
        {10, 11, 12}
    };
    Matrix m3(data3);
    Matrix m4(data4);
    Matrix prod = m3 * m4;
    std::cout << "Product:\n";
    for (unsigned i = 0; i < prod.getRows(); ++i) {
        for (unsigned j = 0; j < prod.getCols(); ++j)
            std::cout << prod.at(i, j) << " ";
        std::cout << "\n";
    }

    // Determinant (must be square)

    Matrix m5(data5);
    std::cout << "Determinant: " << m5.determinant() << std::endl;

    return 0;
}