//
// Created by ADMIN on 8/3/2025.
//

#include "../include/SVDDecomposition.h"
#include <stdexcept>
#include <cmath>
#include <iostream>

// This is a placeholder and does NOT perform full SVD.
// Replace with full implementation or use Eigen for actual values.
void svdDecomposition(const std::vector<std::vector<double>>& A,
                      std::vector<std::vector<double>>& U,
                      std::vector<std::vector<double>>& S,
                      std::vector<std::vector<double>>& Vt) {
    size_t m = A.size();
    size_t n = A[0].size();

    if (m != n) {
        throw std::invalid_argument("Only square matrices supported in placeholder SVD.");
    }

    // For now, assume identity matrices
    U = std::vector<std::vector<double>>(m, std::vector<double>(m, 0));
    S = std::vector<std::vector<double>>(m, std::vector<double>(n, 0));
    Vt = std::vector<std::vector<double>>(n, std::vector<double>(n, 0));

    for (size_t i = 0; i < m; ++i) {
        U[i][i] = 1;
        S[i][i] = A[i][i];  // Just using the diagonal (not actual SVD)
        Vt[i][i] = 1;
    }
}