#!/bin/bash
set -e

# Create build folder
mkdir -p build

# Compile MatrixLib into object files
g++ -Wall -Wextra -std=c++17 \
    -IMatrixLib/include \
    -c MatrixLib/src/*.cpp

# Archive into static library
ar rcs build/libmatrixlib.a *.o
rm *.o

# Compile matrix_parser with MatrixLib
g++ -Wall -Wextra -std=c++17 \
    -IMatrixLib/include -Imatrix_parser/src \
    matrix_parser/src/*.cpp \
    build/libmatrixlib.a \
    -o build/matrix_parser

echo "✅ Build complete. Run it with ./build/matrix_parser"
