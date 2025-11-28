#include "../include/EigenSolver.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

std::pair<double, std::vector<double>> powerIteration(
    const std::vector<std::vector<double>>& A,
    int maxIterations,
    double tolerance
) {
    int n = A.size();
    if (n == 0 || A[0].size() != n)
        throw std::invalid_argument("Matrix must be square for eigenvalue computation.");

    std::vector<double> b(n, 1.0); // Initial guess vector
    double eigenvalue = 0.0;

    for (int iter = 0; iter < maxIterations; ++iter) {
        // Multiply A * b
        std::vector<double> Ab(n, 0.0);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                Ab[i] += A[i][j] * b[j];

        // Compute norm of Ab
        double norm = 0.0;
        for (double val : Ab)
            norm += val * val;
        norm = std::sqrt(norm);

        // Normalize Ab to get new b
        for (int i = 0; i < n; ++i)
            b[i] = Ab[i] / norm;

        // Estimate eigenvalue using Rayleigh quotient
        double newEigenvalue = 0.0;
        for (int i = 0; i < n; ++i) {
            double dot = 0.0;
            for (int j = 0; j < n; ++j)
                dot += A[i][j] * b[j];
            newEigenvalue += b[i] * dot;
        }

        // Check for convergence
        if (std::abs(newEigenvalue - eigenvalue) < tolerance)
            break;

        eigenvalue = newEigenvalue;
    }

    return { eigenvalue, b };
}
