//
// Created by ADMIN on 8/1/2025.
//

#include "../include/LUDecomposition.h"
#include <stdexcept>  // for std::invalid_argument

void luDecomposition(const std::vector<std::vector<double>>& A,
                     std::vector<std::vector<double>>& L,
                     std::vector<std::vector<double>>& U) {
    int n = A.size();

    if (n == 0 || A[0].size() != n)
        throw std::invalid_argument("Matrix must be square for LU decomposition.");

    L.assign(n, std::vector<double>(n, 0));
    U.assign(n, std::vector<double>(n, 0));

    for (int i = 0; i < n; ++i) {
        // Upper Triangular
        for (int k = i; k < n; ++k) {
            double sum = 0;
            for (int j = 0; j < i; ++j)
                sum += L[i][j] * U[j][k];
            U[i][k] = A[i][k] - sum;
        }

        // Lower Triangular
        for (int k = i; k < n; ++k) {
            if (i == k)
                L[i][i] = 1;
            else {
                double sum = 0;
                for (int j = 0; j < i; ++j)
                    sum += L[k][j] * U[j][i];
                if (U[i][i] == 0)
                    throw std::invalid_argument("Matrix is singular, cannot decompose.");
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }
}

