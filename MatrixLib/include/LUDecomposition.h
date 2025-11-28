//
// Created by ADMIN on 8/1/2025.
//

#ifndef LU_DECOMPOSITION_H
#define LU_DECOMPOSITION_H

#include <vector>

// Decomposes A into L and U such that A = L * U
void luDecomposition(const std::vector<std::vector<double>>& A,
                     std::vector<std::vector<double>>& L,
                     std::vector<std::vector<double>>& U);


#endif //LU_DECOMPOSITION_H
