
# MatrixLib (joymatlib)

A small C++ matrix operations library providing:

- Sparse matrix representation
- Matrix addition, transposition, and multiplication
- LU decomposition
- QR decomposition
- Singular Value Decomposition (SVD)
- Eigenvalue computation (power iteration + optional Eigen-based solver)


## Requirements

- C++17 or later
- CMake 3.10+
- Eigen 3 (header-only)

Install Eigen on Ubuntu/Debian:

```bash
sudo apt update
sudo apt install libeigen3-dev cmake build-essential
```

If you prefer, add Eigen as a git submodule or place it under `third_party/` and point CMake to it.


## Project layout

- `include/` — public headers (e.g. `SparseMatrix.h`, `LUDecomposition.h`, `EigenSolver.h`, ...)
- `src/` — implementation files and `main.cpp`
- `CMakeLists.txt` — project build definition


## Build (command line)

From the repository root:

```bash
mkdir -p build
cd build
cmake ..
cmake --build . -- -j$(nproc)
```

This produces an executable (see `CMakeLists.txt` for the exact target name). If CMake cannot find Eigen, install the system package (`libeigen3-dev`) or configure `CMAKE_PREFIX_PATH` to point to your Eigen headers.


## Running the example

The `main` program reads two sparse matrices interactively and performs decompositions and other operations.

Input format (for each matrix in interactive prompts):
1. Number of rows
2. Number of columns
3. Number of non-zero elements
4. For each non-zero element, one line with: `row column value` (0-based indices)

Example interactive session (inputs after prompts):

```
Enter number of rows for Matrix A: 3
Enter number of columns for Matrix A: 3
Enter number of non-zero elements for A: 3
0 0 1.0
1 1 2.0
2 2 3.0
... follow prompts for Matrix B ...
```


## Notes

- Eigen is header-only. Linking is not required, but the headers must be available during compilation.
- Header include paths in source expect `include/` to be at `../include` relative to `src/` (this is typical for the repository layout). CMake handles that when configured from the repo root.
- If you want a non-interactive test, I can add a small example runner that reads matrices from files.


## License

This project is released under the MIT License. See `LICENSE` for details.


