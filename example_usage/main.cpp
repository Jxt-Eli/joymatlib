#include <iostream>
#include <vector>
#include <iomanip>

// Include your matrix library headers
#include "SparseMatrix.h"
#include "LUDecomposition.h"
#include "QRDecomposition.h"
#include "SVDDecomposition.h"
#include "EigenSolver.h"

// Helper function to print a matrix
void printMatrix(const std::vector<std::vector<double>>& matrix, const std::string& name) {
    std::cout << "\n" << name << ":\n";
    for (const auto& row : matrix) {
        for (double val : row) {
            std::cout << std::setw(10) << std::fixed << std::setprecision(4) << val << " ";
        }
        std::cout << "\n";
    }
}

// Helper function to create a test matrix
std::vector<std::vector<double>> createTestMatrix() {
    return {
        {2.0, 1.0, 1.0},
        {1.0, 3.0, 2.0},
        {1.0, 0.0, 0.0}
    };
}

int main() {
    std::cout << "=== Matrix Library Usage Example ===\n\n";

    // Create a test matrix
    auto A = createTestMatrix();
    printMatrix(A, "Original Matrix A");

    // 1. LU Decomposition
    std::cout << "\n=== LU Decomposition ===";
    std::vector<std::vector<double>> L, U;
    luDecomposition(A, L, U);
    printMatrix(L, "L Matrix");
    printMatrix(U, "U Matrix");

    // 2. QR Decomposition
    std::cout << "\n=== QR Decomposition ===";
    std::vector<std::vector<double>> Q, R;
    qrDecomposition(A, Q, R);
    printMatrix(Q, "Q Matrix");
    printMatrix(R, "R Matrix");

    // 3. SVD Decomposition
    std::cout << "\n=== SVD Decomposition ===";
    std::vector<std::vector<double>> U_svd, S, Vt;
    svdDecomposition(A, U_svd, S, Vt);
    printMatrix(U_svd, "U Matrix (SVD)");
    printMatrix(S, "S Matrix (Singular Values)");
    printMatrix(Vt, "V^T Matrix");

    // 4. Eigenvalue computation using Power Iteration
    std::cout << "\n=== Eigenvalue Computation ===";
    auto [eigenvalue, eigenvector] = powerIteration(A);
    std::cout << "Dominant Eigenvalue: " << eigenvalue << "\n";
    std::cout << "Corresponding Eigenvector: ";
    for (double val : eigenvector) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // 5. Sparse Matrix Operations
    std::cout << "\n=== Sparse Matrix Operations ===";
    
    // Create a sparse matrix
    SparseMatrix sparse(3, 3);
    sparse.set(0, 0, 2.0);
    sparse.set(0, 1, 1.0);
    sparse.set(1, 1, 3.0);
    sparse.set(2, 2, 1.0);
    
    std::cout << "Sparse Matrix:\n";
    sparse.print();
    
    // Convert to dense matrix
    auto dense = sparse.toDense();
    printMatrix(dense, "Dense Matrix (from sparse)");
    
    // Transpose
    SparseMatrix transposed = sparse.transpose();
    std::cout << "\nTransposed Sparse Matrix:\n";
    transposed.print();
    
    // Determinant
    std::cout << "\nDeterminant of sparse matrix: " << sparse.determinant() << "\n";

    // 6. Matrix Addition with Sparse Matrices
    std::cout << "\n=== Sparse Matrix Addition ===";
    SparseMatrix sparse2(3, 3);
    sparse2.set(0, 0, 1.0);
    sparse2.set(1, 1, 2.0);
    sparse2.set(2, 2, 1.0);
    
    std::cout << "Second Sparse Matrix:\n";
    sparse2.print();
    
    SparseMatrix sum = sparse.add(sparse2);
    std::cout << "Sum of sparse matrices:\n";
    sum.print();

    std::cout << "\n=== Example Complete ===\n";
    return 0;
} 