#include "operations.hpp"

Matrix::Matrix(unsigned rows, unsigned cols)
    : data_(rows, std::vector<double>(cols, 0.0)), rows_(rows), cols_(cols) {}

Matrix::Matrix(const std::vector<std::vector<double>>& data)
    : data_(data), rows_(data.size()), cols_(data.empty() ? 0 : data[0].size()) {}

unsigned Matrix::getRows() const { return rows_; }
unsigned Matrix::getCols() const { return cols_; }

double& Matrix::at(unsigned row, unsigned col) { return data_[row][col]; }
double Matrix::at(unsigned row, unsigned col) const { return data_[row][col]; }

Matrix Matrix::operator+(const Matrix& rhs) const {
    if (rows_ != rhs.rows_ || cols_ != rhs.cols_)
        throw std::invalid_argument("Matrix dimensions must match for addition.");
    Matrix result(rows_, cols_);
    for (unsigned i = 0; i < rows_; ++i)
        for (unsigned j = 0; j < cols_; ++j)
            result.data_[i][j] = data_[i][j] + rhs.data_[i][j];
    return result;
}

Matrix Matrix::operator-(const Matrix& rhs) const {
    if (rows_ != rhs.rows_ || cols_ != rhs.cols_)
        throw std::invalid_argument("Matrix dimensions must match for subtraction.");
    Matrix result(rows_, cols_);
    for (unsigned i = 0; i < rows_; ++i)
        for (unsigned j = 0; j < cols_; ++j)
            result.data_[i][j] = data_[i][j] - rhs.data_[i][j];
    return result;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
    if (cols_ != rhs.rows_)
        throw std::invalid_argument("Matrix dimensions must match for multiplication.");
    Matrix result(rows_, rhs.cols_);
    for (unsigned i = 0; i < rows_; ++i)
        for (unsigned j = 0; j < rhs.cols_; ++j)
            for (unsigned k = 0; k < cols_; ++k)
                result.data_[i][j] += data_[i][k] * rhs.data_[k][j];
    return result;
}

double Matrix::determinant() const {
    if (rows_ != cols_)
        throw std::invalid_argument("Matrix must be square to compute determinant.");
    return determinantRecursive(data_);
}

double Matrix::determinantRecursive(const std::vector<std::vector<double>>& mat) const {
    unsigned n = mat.size();
    if (n == 1) return mat[0][0];
    if (n == 2) return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];

    double det = 0.0;
    for (unsigned p = 0; p < n; ++p) {
        std::vector<std::vector<double>> submat(n-1, std::vector<double>(n-1));
        for (unsigned i = 1; i < n; ++i) {
            unsigned colIdx = 0;
            for (unsigned j = 0; j < n; ++j) {
                if (j == p) continue;
                submat[i-1][colIdx] = mat[i][j];
                ++colIdx;
            }
        }
        det += (p % 2 == 0 ? 1 : -1) * mat[0][p] * determinantRecursive(submat);
    }
    return det;
}