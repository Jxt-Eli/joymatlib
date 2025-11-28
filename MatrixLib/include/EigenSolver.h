//
// Created by ADMIN on 8/3/2025.
//

#ifndef EIGENSOLVER_H
#define EIGENSOLVER_H


#include <vector>
#include <utility> // for std::pair


std::pair<double, std::vector<double>> powerIteration(
    const std::vector<std::vector<double>>& matrix,
    int maxIterations = 1000,
    double tolerance = 1e-6
);


#endif //EIGENSOLVER_H
