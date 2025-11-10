#include <iostream>
#include <vector>
#include <iomanip>
#include "MatrixLib/include/SparseMatrix.h"
#include "MatrixLib/include/LUDecomposition.h"
#include "MatrixLib/include/QRDecomposition.h"
#include "MatrixLib/include/SVDDecomposition.h"
#include "MatrixLib/include/EigenSolver.h"

// Helper function to print dense matrices nicely
void printDenseMatrix(const std::vector<std::vector<double>>& matrix, const std::string& name) {
    std::cout << "\n" << name << ":\n";
    for (const auto& row : matrix) {
        for (double val : row) {
            std::cout << std::setw(10) << std::fixed << std::setprecision(4) << val << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    // Create two 3x3 sparse matrices
    SparseMatrix A(3, 3), B(3, 3);

    // Set values for A
    A.set(0, 0, 2.0);
    A.set(0, 1, 1.0);
    A.set(1, 1, 3.0);
    A.set(2, 2, 1.0);

    // Set values for B
    B.set(0, 0, 1.0);
    B.set(1, 1, 2.0);
    B.set(2, 2, 1.0);

    // Addition
    SparseMatrix sum = A.add(B);

    // Subtraction: Create negative B manually
    SparseMatrix negB(3, 3);
    negB.set(0, 0, -1.0);  // Negative of B's values
    negB.set(1, 1, -2.0);
    negB.set(2, 2, -1.0);
    SparseMatrix diff = A.add(negB);

    // Multiplication
    SparseMatrix prod = A.multiply(B); //gives the product of matrix A and B

    // Determinant (finds the determinant of a given matrix)
    double detA = A.determinant();

    // Print basic operation results
    std::cout << "Matrix A:\n";
    A.print();
    
    std::cout << "\nMatrix B:\n";
    B.print();
    
    // prints out the sum of A and B
    std::cout << "\nA + B =\n";
    sum.print();
    // prints out the difference of A and B
    std::cout << "\nA - B =\n";
    diff.print();

    // prints out the product of A and B
    std::cout << "\nA * B =\n";
    prod.print();

    std::cout << "\nDeterminant of A: " << detA << std::endl; // print the determinant of matrix A

    // ===== DECOMPOSITIONS =====
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "MATRIX DECOMPOSITIONS\n";
    std::cout << std::string(50, '=') << "\n";

    // Convert sparse matrix to dense for decompositions
    auto denseA = A.toDense();
    printDenseMatrix(denseA, "Original Matrix A (Dense)");

    // 1. LU Decomposition
    std::cout << "\n=== LU DECOMPOSITION ===";
    std::vector<std::vector<double>> L, U;
    luDecomposition(denseA, L, U);
    printDenseMatrix(L, "L Matrix (Lower Triangular)");
    printDenseMatrix(U, "U Matrix (Upper Triangular)");

    // 2. QR Decomposition
    std::cout << "\n=== QR DECOMPOSITION ===";
    std::vector<std::vector<double>> Q, R;
    qrDecomposition(denseA, Q, R);
    printDenseMatrix(Q, "Q Matrix (Orthogonal)");
    printDenseMatrix(R, "R Matrix (Upper Triangular)");

    // 3. SVD Decomposition
    std::cout << "\n=== SVD DECOMPOSITION ===";
    std::vector<std::vector<double>> U_svd, S, Vt;
    svdDecomposition(denseA, U_svd, S, Vt);
    printDenseMatrix(U_svd, "U Matrix (Left Singular Vectors)");
    printDenseMatrix(S, "S Matrix (Singular Values)");
    printDenseMatrix(Vt, "V^T Matrix (Right Singular Vectors)");

    // 4. Eigenvalue computation
    std::cout << "\n=== EIGENVALUE COMPUTATION ===";
    auto [eigenvalue, eigenvector] = powerIteration(denseA);
    std::cout << "\nDominant Eigenvalue: " << std::fixed << std::setprecision(6) << eigenvalue << "\n";
    std::cout << "Corresponding Eigenvector:\n";
    for (size_t i = 0; i < eigenvector.size(); ++i) {
        std::cout << "  v[" << i << "] = " << std::fixed << std::setprecision(6) << eigenvector[i] << "\n";
    }

    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "DECOMPOSITION COMPLETE!\n";
    std::cout << std::string(50, '=') << "\n";

    return 0;
}