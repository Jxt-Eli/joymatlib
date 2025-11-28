//
// Created by ADMIN on 7/29/2025.
//
#include "../include/SparseMatrix.h"

SparseMatrix::SparseMatrix(int r, int c) : rows(r), cols(c) {}

void SparseMatrix::set(int i, int j, double val) {
    if (val != 0)
        data[{i, j}] = val; // store only non-zero
}

double SparseMatrix::get(int i, int j) const {
    auto it = data.find({i, j});
    return (it != data.end()) ? it->second : 0.0; // return 0 if not found
}

void SparseMatrix::input() {
    int nonZeroCount;
    std::cout << "Enter number of non-zero elements: ";
    std::cin >> nonZeroCount;

    std::cout << "Enter each as: row column value\n";
    std::cout << "Example: to set row 0, column 2 to value 8.5, type: 0 2 8.5\n";
    for (int k = 0; k < nonZeroCount; ++k) {
        int i, j;
        double val;
        std::cin >> i >> j >> val;

        if (i >= 0 && i < rows && j >= 0 && j < cols) {
            set(i, j, val);
        } else {
            std::cout << "Invalid position: (" << i << ", " << j << ")\n";
        }
    }
}

void SparseMatrix::print() const
{
    std::cout << "Sparse Matrix (" << rows << "x" << cols << "):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            std::cout << get(i, j) << " ";
        std::cout << "\n";
    }
}

    SparseMatrix SparseMatrix::add(const SparseMatrix& other) const {
        // Check size compatibility
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions do not match for addition.");
        }

        SparseMatrix result(rows, cols);

        // Step 1: Add all non-zero values from the current matrix
        for (const auto& entry : data) {
            result.set(entry.first.first, entry.first.second, entry.second);
        }

        // Step 2: Add all values from the other matrix
        for (const auto& entry : other.data) {
            int i = entry.first.first;
            int j = entry.first.second;
            double val = result.get(i, j) + entry.second;
            result.set(i, j, val);
        }

        return result;
    }

SparseMatrix SparseMatrix::transpose() const {
    SparseMatrix result(cols, rows);  // note: rows and cols are swapped

    for (const auto& entry : data) {
        int i = entry.first.first;
        int j = entry.first.second;
        result.set(j, i, entry.second);  // Swap i and j
    }

    return result;
}

SparseMatrix SparseMatrix::multiply(const SparseMatrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Matrix dimensions incompatible for multiplication.");
    }

    SparseMatrix result(rows, other.cols);

    for (const auto& aEntry : data) {
        int i = aEntry.first.first;
        int k = aEntry.first.second;
        double aVal = aEntry.second;

        for (int j = 0; j < other.cols; ++j) {
            double bVal = other.get(k, j);
            if (bVal != 0) {
                double sum = result.get(i, j) + aVal * bVal;
                result.set(i, j, sum);
            }
        }
    }

    return result;
}

std::vector<std::vector<double>> SparseMatrix::toDense() const {
    std::vector<std::vector<double>> dense(rows, std::vector<double>(cols, 0.0));

    for (const auto& entry : data) {
        int i = entry.first.first;
        int j = entry.first.second;
        dense[i][j] = entry.second;
    }

    return dense;
}

double SparseMatrix::determinant() const {
    if (rows != cols) {
        throw std::invalid_argument("Determinant is only defined for square matrices.");
    }

    std::vector<std::vector<double>> mat = toDense();
    int n = rows;
    double det = 1.0;

    for (int i = 0; i < n; ++i) {
        // Find pivot
        if (std::abs(mat[i][i]) < 1e-10) {
            // Find a row to swap
            bool pivotFound = false;
            for (int k = i + 1; k < n; ++k) {
                if (std::abs(mat[k][i]) > 1e-10) {
                    std::swap(mat[i], mat[k]);
                    det *= -1;  // Row swap changes sign of determinant
                    pivotFound = true;
                    break;
                }
            }
            if (!pivotFound) {
                return 0.0;  // Singular matrix
            }
        }

        det *= mat[i][i];

        // Eliminate below
        for (int j = i + 1; j < n; ++j) {
            double factor = mat[j][i] / mat[i][i];
            for (int k = i; k < n; ++k) {
                mat[j][k] -= factor * mat[i][k];
            }
        }
    }

    return det;
}
