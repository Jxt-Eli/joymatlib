#pragma once
#include <vector>
#include <stdexcept>

class Matrix {
public:
    Matrix(unsigned rows, unsigned cols);
    Matrix(const std::vector<std::vector<double>>& data);

    unsigned getRows() const;
    unsigned getCols() const;
    double& at(unsigned row, unsigned col);
    double at(unsigned row, unsigned col) const;

    Matrix operator+(const Matrix& rhs) const;
    Matrix operator-(const Matrix& rhs) const;
    Matrix operator*(const Matrix& rhs) const;
    double determinant() const;

private:
    std::vector<std::vector<double>> data_;
    unsigned rows_, cols_;

    double determinantRecursive(const std::vector<std::vector<double>>& mat) const;
};