#include "operations.hpp"

// Constructor: Create a matrix with given rows and columns, initialized to 0.0
Matrix::Matrix(unsigned rows, unsigned cols)
    : data_(rows, std::vector<double>(cols, 0.0)), rows_(rows), cols_(cols) {}

// Constructor: Create a matrix from a 2D vector
Matrix::Matrix(const std::vector<std::vector<double>>& data)
    : data_(data), rows_(data.size()), cols_(data.empty() ? 0 : data[0].size()) {}

// Get the number of rows
unsigned Matrix::getRows() const { return rows_; }

// Get the number of columns
unsigned Matrix::getCols() const { return cols_; }

// Access an element (modifiable)
double& Matrix::at(unsigned row, unsigned col) { return data_[row][col]; }

// Access an element (read-only)
double Matrix::at(unsigned row, unsigned col) const { return data_[row][col]; }

// Matrix addition
Matrix Matrix::operator+(const Matrix& rhs) const {
    // Check dimensions match
    if (rows_ != rhs.rows_ || cols_ != rhs.cols_)
        throw std::invalid_argument("Matrix dimensions must match for addition.");
    Matrix result(rows_, cols_);
    // Add corresponding elements
    for (unsigned i = 0; i < rows_; ++i)
        for (unsigned j = 0; j < cols_; ++j)
            result.data_[i][j] = data_[i][j] + rhs.data_[i][j];
    return result;
}

// Matrix subtraction
Matrix Matrix::operator-(const Matrix& rhs) const {
    // Check dimensions match
    if (rows_ != rhs.rows_ || cols_ != rhs.cols_)
        throw std::invalid_argument("Matrix dimensions must match for subtraction.");
    Matrix result(rows_, cols_);
    // Subtract corresponding elements
    for (unsigned i = 0; i < rows_; ++i)
        for (unsigned j = 0; j < cols_; ++j)
            result.data_[i][j] = data_[i][j] - rhs.data_[i][j];
    return result;
}

// Matrix multiplication
Matrix Matrix::operator*(const Matrix& rhs) const {
    // Check if multiplication is possible (cols of left == rows of right)
    if (cols_ != rhs.rows_)
        throw std::invalid_argument("Matrix dimensions must match for multiplication.");
    Matrix result(rows_, rhs.cols_);
    // Standard matrix multiplication algorithm
    for (unsigned i = 0; i < rows_; ++i)
        for (unsigned j = 0; j < rhs.cols_; ++j)
            for (unsigned k = 0; k < cols_; ++k)
                result.data_[i][j] += data_[i][k] * rhs.data_[k][j];
    return result;
}

// Calculate the determinant of the matrix
double Matrix::determinant() const {
    // Only square matrices have a determinant
    if (rows_ != cols_)
        throw std::invalid_argument("Matrix must be square to compute determinant.");
    return determinantRecursive(data_);
}

// Helper function: recursively calculate the determinant of a matrix
double Matrix::determinantRecursive(const std::vector<std::vector<double>>& mat) const {
    unsigned n = mat.size();
    // Base case for 1x1 matrix
    if (n == 1) return mat[0][0];
    // Base case for 2x2 matrix
    if (n == 2) return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];

    double det = 0.0;
    // Laplace expansion along the first row
    for (unsigned p = 0; p < n; ++p) {
        // Create submatrix by removing first row and p-th column
        std::vector<std::vector<double>> submat(n-1, std::vector<double>(n-1));
        for (unsigned i = 1; i < n; ++i) {
            unsigned colIdx = 0;
            for (unsigned j = 0; j < n; ++j) {
                if (j == p) continue;
                submat[i-1][colIdx] = mat[i][j];
                ++colIdx;
            }
        }
        // Add or subtract the minor, depending on position
        det += (p % 2 == 0 ? 1 : -1) * mat[0][p] * determinantRecursive(submat);
    }
    return det;
}