#include <iostream>
#include "../include/SparseMatrix.h"
#include "../include/LUDecomposition.h"
#include "../include/QRDecomposition.h"
#include "../include/SVDDecomposition.h"
#include "../include/EigenSolver.h"

void inputMatrix(SparseMatrix& mat, int nonZeroCount) {
    int i, j;
    double val;
    std::cout << "Enter each non-zero value as: row column value\n";
    for (int k = 0; k < nonZeroCount; ++k) {
        std::cin >> i >> j >> val;
        mat.set(i, j, val);
    }
}

void decompose(const SparseMatrix& mat, const std::string& label) {
    if (mat.getRows() == mat.getCols()) {
        std::vector<std::vector<double>> dense = mat.toDense();
        std::vector<std::vector<double>> L, U, Q, R;

        std::cout << "\nPerforming LU Decomposition on " << label << "...\n";
        try {
            luDecomposition(dense, L, U);
            std::cout << "\nL matrix (" << label << "):\n";
            for (const auto& row : L) {
                for (double val : row) std::cout << val << " ";
                std::cout << "\n";
            }
            std::cout << "\nU matrix (" << label << "):\n";
            for (const auto& row : U) {
                for (double val : row) std::cout << val << " ";
                std::cout << "\n";
            }
        } catch (const std::exception& e) {
            std::cout << "LU Error: " << e.what() << "\n";
        }

        std::cout << "\nPerforming QR Decomposition on " << label << "...\n";
        try {
            qrDecomposition(dense, Q, R);
            std::cout << "\nQ matrix (" << label << "):\n";
            for (const auto& row : Q) {
                for (double val : row) std::cout << val << " ";
                std::cout << "\n";
            }
            std::cout << "\nR matrix (" << label << "):\n";
            for (const auto& row : R) {
                for (double val : row) std::cout << val << " ";
                std::cout << "\n";
            }
        } catch (const std::exception& e) {
            std::cout << "QR Error: " << e.what() << "\n";
        }

        // Eigenvalue computation
        std::cout << "\nComputing dominant eigenvalue of " << label << "...\n";
        try {
            auto result = powerIteration(dense);
            std::cout << "Dominant Eigenvalue: " << result.first << "\n";
            std::cout << "Eigenvector:\n";
            for (double val : result.second)
                std::cout << val << "\n";
        } catch (const std::exception& e) {
            std::cout << "Eigenvalue Error: " << e.what() << "\n";
        }

    } else {
        std::cout << "\nSkipping decomposition: " << label << " is not square.\n";
    }
}

void performSVD(const SparseMatrix& matrix, const std::string& label) {
    std::vector<std::vector<double>> dense = matrix.toDense();
    std::vector<std::vector<double>> U, S, Vt;

    try {
        svdDecomposition(dense, U, S, Vt);
        std::cout << "\nU matrix (" << label << "):\n";
        for (const auto& row : U) {
            for (double val : row) std::cout << val << " ";
            std::cout << "\n";
        }

        std::cout << "\nSigma (S) matrix (" << label << "):\n";
        for (const auto& row : S) {
            for (double val : row) std::cout << val << " ";
            std::cout << "\n";
        }

        std::cout << "\nV transpose(V^T) matrix (" << label << "):\n";
        for (const auto& row : Vt) {
            for (double val : row) std::cout << val << " ";
            std::cout << "\n";
        }
    } catch (const std::invalid_argument& e) {
        std::cout << "SVD Error: " << e.what() << "\n";
    }
}

int main() {
    int rowsA, colsA;
    std::cout << "Enter number of rows for Matrix A: ";
    std::cin >> rowsA;
    std::cout << "Enter number of columns for Matrix A: ";
    std::cin >> colsA;

    SparseMatrix A(rowsA, colsA);
    int nonZeroA;
    std::cout << "Enter number of non-zero elements for A: ";
    std::cin >> nonZeroA;
    inputMatrix(A, nonZeroA);

    int rowsB, colsB;
    std::cout << "Enter number of rows for Matrix B: ";
    std::cin >> rowsB;
    std::cout << "Enter number of columns for Matrix B: ";
    std::cin >> colsB;

    SparseMatrix B(rowsB, colsB);
    int nonZeroB;
    std::cout << "Enter number of non-zero elements for B: ";
    std::cin >> nonZeroB;
    inputMatrix(B, nonZeroB);

    std::cout << "\nMatrix A:\n";
    A.print();
    std::cout << "\nMatrix B:\n";
    B.print();

    if (rowsA == rowsB && colsA == colsB) {
        std::cout << "\nA + B:\n";
        A.add(B).print();
    }

    std::cout << "\nTranspose of A:\n";
    A.transpose().print();

    if (colsA == rowsB) {
        std::cout << "\nA * B:\n";
        A.multiply(B).print();
    }

    // Decompositions
    decompose(A, "Matrix A");
    decompose(B, "Matrix B");

    // Determinants
    if (A.getRows() == A.getCols()) {
        try {
            std::cout << "\nDeterminant of Matrix A: " << A.determinant() << "\n";
        } catch (const std::exception& e) {
            std::cout << "Error computing determinant of A: " << e.what() << "\n";
        }
    } else {
        std::cout << "\nSkipping determinant: Matrix A is not square.\n";
    }

    if (B.getRows() == B.getCols()) {
        try {
            std::cout << "\nDeterminant of Matrix B: " << B.determinant() << "\n";
        } catch (const std::exception& e) {
            std::cout << "Error computing determinant of B: " << e.what() << "\n";
        }
    } else {
        std::cout << "\nSkipping determinant: Matrix B is not square.\n";
    }

    std::cout << "\nPerforming SVD Decomposition on Matrix A...\n";
    performSVD(A, "Matrix A");

    std::cout << "\nPerforming SVD Decomposition on Matrix B...\n";
    performSVD(B, "Matrix B");

    return 0;
}
