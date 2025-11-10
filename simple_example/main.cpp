#include <iostream>
#include <vector>

// Include the matrix library headers
#include "SparseMatrix.h"
#include "LUDecomposition.h"
#include "QRDecomposition.h"
#include "SVDDecomposition.h"
#include "EigenSolver.h"

int main() {
    // Example 1: LU Decomposition
    std::cout << "=== LU Decomposition Example ===\n";
    std::vector<std::vector<double>> A = {
        {2, 1, 1},
        {1, 3, 2},
        {1, 0, 0}
    };
    
    std::vector<std::vector<double>> L, U;
    luDecomposition(A, L, U);
    
    std::cout << "Matrix A decomposed into L and U matrices.\n";
    std::cout << "L matrix size: " << L.size() << "x" << L[0].size() << "\n";
    std::cout << "U matrix size: " << U.size() << "x" << U[0].size() << "\n\n";

    // Example 2: QR Decomposition
    std::cout << "=== QR Decomposition Example ===\n";
    std::vector<std::vector<double>> Q, R;
    qrDecomposition(A, Q, R);
    
    std::cout << "Matrix A decomposed into Q and R matrices.\n";
    std::cout << "Q matrix size: " << Q.size() << "x" << Q[0].size() << "\n";
    std::cout << "R matrix size: " << R.size() << "x" << R[0].size() << "\n\n";

    // Example 3: SVD Decomposition
    std::cout << "=== SVD Decomposition Example ===\n";
    std::vector<std::vector<double>> U, S, Vt;
    svdDecomposition(A, U, S, Vt);
    
    std::cout << "Matrix A decomposed into U, S, and V^T matrices.\n";
    std::cout << "U matrix size: " << U.size() << "x" << U[0].size() << "\n";
    std::cout << "S matrix size: " << S.size() << "x" << S[0].size() << "\n";
    std::cout << "V^T matrix size: " << Vt.size() << "x" << Vt[0].size() << "\n\n";

    // Example 4: Eigenvalue computation
    std::cout << "=== Eigenvalue Computation Example ===\n";
    auto [eigenvalue, eigenvector] = powerIteration(A);
    std::cout << "Dominant eigenvalue: " << eigenvalue << "\n";
    std::cout << "Eigenvector size: " << eigenvector.size() << "\n\n";

    // Example 5: Sparse Matrix operations
    std::cout << "=== Sparse Matrix Example ===\n";
    SparseMatrix sparse(3, 3);
    sparse.set(0, 0, 2.0);
    sparse.set(0, 1, 1.0);
    sparse.set(1, 1, 3.0);
    sparse.set(2, 2, 1.0);
    
    std::cout << "Sparse matrix created with 4 non-zero elements.\n";
    std::cout << "Matrix size: " << sparse.getRows() << "x" << sparse.getCols() << "\n";
    std::cout << "Determinant: " << sparse.determinant() << "\n\n";

    return 0;
} 