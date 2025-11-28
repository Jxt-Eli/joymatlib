//
// Created by ADMIN on 8/3/2025.
//

#ifndef SVDDECOMPOSITION_H
#define SVDDECOMPOSITION_H


#include <vector>

void svdDecomposition(const std::vector<std::vector<double>>& A,
                      std::vector<std::vector<double>>& U,
                      std::vector<std::vector<double>>& S,
                      std::vector<std::vector<double>>& Vt);


#endif //SVDDECOMPOSITION_H
