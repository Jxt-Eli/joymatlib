#include <iostream>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <Eigen/Eigenvalues>
#include <Spectra/SymEigsSolver.h>
#include <Spectra/MatOp/SparseSymMatProd.h>

using namespace Eigen;
using namespace Spectra;

// Function to compute eigenvalues and eigenvectors of a dense symmetric matrix
void denseEigenSolver(const MatrixXd& mat) {
    SelfAdjointEigenSolver<MatrixXd> eigensolver(mat);
    if (eigensolver.info() != Success) {
        std::cerr << "Dense eigen solver failed!" << std::endl;
        return;
    }

    VectorXd eigenvalues = eigensolver.realEigenvalues();
    MatrixXd eigenvectors = eigensolver.eigenvectors();

    std::cout << "\nDense Matrix Eigenvalues:\n" << eigenvalues.transpose() << std::endl;
    std::cout << "\nDense Matrix Eigenvectors (columns):\n" << eigenvectors << std::endl;
}

// Function to compute largest eigenvalues/eigenvectors of a sparse symmetric matrix
void sparseEigenSolver(const SparseMatrix<double>& sparseMat, int numEigenvalues = 5) {
    // Use Spectra for sparse eigenvalue problems
    SparseSymMatProd<double> op(sparseMat);
    SymEigsSolver<double, LARGEST_ALGE, SparseSymMatProd<double>> eigs(&op, numEigenvalues, std::min(2 * numEigenvalues, sparseMat.rows()));

    eigs.init();
    int nconv = eigs.compute();

    if (eigs.info() == SUCCESS) {
        VectorXd evalues = eigs.eigenvalues();
        MatrixXd evectors = eigs.eigenvectors();

        std::cout << "\nSparse Matrix - " << nconv << " eigenvalues computed:\n" << evalues.transpose() << std::endl;
        std::cout << "\nSparse Matrix - Corresponding eigenvectors:\n" << evectors << std::endl;
    } else {
        std::cerr << "Sparse eigen solver failed to converge!" << std::endl;
    }
}

int main() {
    // === Example 1: Dense Symmetric Matrix ===
    std::cout << "=== Dense Matrix Eigen Computation ===" << std::endl;
    MatrixXd A(3, 3);
    A << 4, -2, -1,
         -2, 4, -1,
         -1, -1, 4;

    std::cout << "Matrix A:\n" << A << std::endl;
    denseEigenSolver(A);

    // === Example 2: Sparse Symmetric Matrix ===
    std::cout << "\n\n=== Sparse Matrix Eigen Computation ===" << std::endl;
    SparseMatrix<double> B(4, 4);
    std::vector<Triplet<double>> triplets;
    triplets.push_back(Triplet<double>(0, 0, 3.0));
    triplets.push_back(Triplet<double>(1, 1, 2.0));
    triplets.push_back(Triplet<double>(2, 2, 1.0));
    triplets.push_back(Triplet<double>(3, 3, 4.0));
    triplets.push_back(Triplet<double>(0, 1, -1.0));
    triplets.push_back(Triplet<double>(1, 0, -1.0));
    triplets.push_back(Triplet<double>(1, 2, -1.0));
    triplets.push_back(Triplet<double>(2, 1, -1.0));

    B.setFromTriplets(triplets.begin(), triplets.end());
    B.makeCompressed();

    std::cout << "Sparse Matrix B:\n" << B << std::endl;
    sparseEigenSolver(B, 3);  // compute 3 largest eigenvalues

    return 0;
}