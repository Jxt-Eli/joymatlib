//
// Created by ADMIN on 8/3/2025.
//

#include "../include/QRDecomposition.h"
#include <cmath>
#include <stdexcept>

double dot(const std::vector<double>& a, const std::vector<double>& b) {
    double result = 0;
    for (size_t i = 0; i < a.size(); ++i)
        result += a[i] * b[i];
    return result;
}

double norm(const std::vector<double>& v) {
    return std::sqrt(dot(v, v));
}

void qrDecomposition(const std::vector<std::vector<double>>& A,
                     std::vector<std::vector<double>>& Q,
                     std::vector<std::vector<double>>& R) {
    int m = A.size();
    int n = A[0].size();

    Q = std::vector<std::vector<double>>(m, std::vector<double>(n, 0.0));
    R = std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));
    std::vector<std::vector<double>> V = A;

    for (int i = 0; i < n; ++i) {
        R[i][i] = norm(V[i]);
        if (R[i][i] == 0.0)
            throw std::invalid_argument("Matrix has linearly dependent columns.");

        for (int j = 0; j < m; ++j)
            Q[j][i] = V[i][j] / R[i][i];

        for (int j = i + 1; j < n; ++j) {
            R[i][j] = 0.0;
            for (int k = 0; k < m; ++k)
                R[i][j] += Q[k][i] * V[j][k];

            for (int k = 0; k < m; ++k)
                V[j][k] -= R[i][j] * Q[k][i];
        }
    }
}
