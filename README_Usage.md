# Matrix Library Usage Guide

This guide explains how to use the C++ Matrix Library in your own projects.

## Library Overview

The Matrix Library provides the following functionality:
- **LU Decomposition**: Decompose a matrix A into L and U matrices where A = L × U
- **QR Decomposition**: Decompose a matrix A into Q and R matrices where A = Q × R
- **SVD Decomposition**: Decompose a matrix A into U, S, and V^T matrices where A = U × S × V^T
- **Eigenvalue Computation**: Find the dominant eigenvalue and eigenvector using power iteration
- **Sparse Matrix Operations**: Efficient operations on sparse matrices including addition, multiplication, transpose, and determinant calculation

## How to Use the Library

### Method 1: Using CMake (Recommended)

1. **Include the library as a subdirectory** in your project's `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.31)
project(YourProject)

set(CMAKE_CXX_STANDARD 20)

# Add the MatrixLib as a subdirectory
add_subdirectory(../MatrixLib MatrixLib)

# Create your executable
add_executable(your_app main.cpp)

# Link against the MatrixLib
target_link_libraries(your_app PRIVATE MatrixLib)

# Include directories for MatrixLib headers
target_include_directories(your_app PRIVATE ../MatrixLib/include)
```

2. **Include the headers** in your C++ code:

```cpp
#include "SparseMatrix.h"
#include "LUDecomposition.h"
#include "QRDecomposition.h"
#include "SVDDecomposition.h"
#include "EigenSolver.h"
```

### Method 2: Direct Compilation

If you prefer not to use CMake, you can compile directly:

```bash
g++ -std=c++20 -I../MatrixLib/include your_file.cpp ../MatrixLib/src/*.cpp -o your_program
```

## Function Usage Examples

### 1. LU Decomposition

```cpp
#include "LUDecomposition.h"

std::vector<std::vector<double>> A = {
    {2, 1, 1},
    {1, 3, 2},
    {1, 0, 0}
};

std::vector<std::vector<double>> L, U;
luDecomposition(A, L, U);
// Now L and U contain the LU decomposition of A
```

### 2. QR Decomposition

```cpp
#include "QRDecomposition.h"

std::vector<std::vector<double>> A = {
    {2, 1, 1},
    {1, 3, 2},
    {1, 0, 0}
};

std::vector<std::vector<double>> Q, R;
qrDecomposition(A, Q, R);
// Now Q and R contain the QR decomposition of A
```

### 3. SVD Decomposition

```cpp
#include "SVDDecomposition.h"

std::vector<std::vector<double>> A = {
    {2, 1, 1},
    {1, 3, 2},
    {1, 0, 0}
};

std::vector<std::vector<double>> U, S, Vt;
svdDecomposition(A, U, S, Vt);
// Now U, S, and Vt contain the SVD decomposition of A
```

### 4. Eigenvalue Computation

```cpp
#include "EigenSolver.h"

std::vector<std::vector<double>> A = {
    {2, 1, 1},
    {1, 3, 2},
    {1, 0, 0}
};

auto [eigenvalue, eigenvector] = powerIteration(A);
// eigenvalue contains the dominant eigenvalue
// eigenvector contains the corresponding eigenvector
```

### 5. Sparse Matrix Operations

```cpp
#include "SparseMatrix.h"

// Create a sparse matrix
SparseMatrix sparse(3, 3);
sparse.set(0, 0, 2.0);
sparse.set(0, 1, 1.0);
sparse.set(1, 1, 3.0);
sparse.set(2, 2, 1.0);

// Get a value
double value = sparse.get(0, 0); // Returns 2.0

// Convert to dense matrix
auto dense = sparse.toDense();

// Transpose
SparseMatrix transposed = sparse.transpose();

// Determinant
double det = sparse.determinant();

// Addition
SparseMatrix sparse2(3, 3);
sparse2.set(0, 0, 1.0);
SparseMatrix sum = sparse.add(sparse2);
```

## Available Functions

### LUDecomposition.h
- `void luDecomposition(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& L, std::vector<std::vector<double>>& U)`

### QRDecomposition.h
- `void qrDecomposition(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& Q, std::vector<std::vector<double>>& R)`

### SVDDecomposition.h
- `void svdDecomposition(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& U, std::vector<std::vector<double>>& S, std::vector<std::vector<double>>& Vt)`

### EigenSolver.h
- `std::pair<double, std::vector<double>> powerIteration(const std::vector<std::vector<double>>& matrix, int maxIterations = 1000, double tolerance = 1e-6)`

### SparseMatrix.h
- Constructor: `SparseMatrix(int rows, int cols)`
- `void set(int i, int j, double val)` - Set value at position (i,j)
- `double get(int i, int j) const` - Get value at position (i,j)
- `void print() const` - Print the matrix
- `double determinant() const` - Calculate determinant
- `SparseMatrix add(const SparseMatrix& other) const` - Add two sparse matrices
- `SparseMatrix transpose() const` - Transpose the matrix
- `SparseMatrix multiply(const SparseMatrix& other) const` - Multiply two sparse matrices
- `std::vector<std::vector<double>> toDense() const` - Convert to dense matrix
- `int getRows() const` - Get number of rows
- `int getCols() const` - Get number of columns

## Building and Running Examples

1. **Build the examples**:
   ```bash
   ./build_examples.sh
   ```

2. **Run the comprehensive example**:
   ```bash
   cd build/example_usage && ./example_app
   ```

3. **Run the simple example**:
   ```bash
   cd build/simple_example && ./simple_example
   ```

## Notes

- All matrix operations expect `std::vector<std::vector<double>>` for dense matrices
- Sparse matrices use the `SparseMatrix` class for memory efficiency
- The library uses C++20 standard
- All decomposition functions modify the output parameters passed by reference
- The power iteration method returns a pair containing the eigenvalue and eigenvector 