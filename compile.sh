#!/bin/bash

g++ -Iinclude MatrixLib/src/main.cpp MatrixLib/src/EigenSolver.cpp MatrixLib/src/QRDecomposition.cpp 
MatrixLib/src/SparseMatrix.cpp MatrixLib/src/SVDDecomposition.cpp MatrixLib/src/LUDecomposition.cpp -o build

echo "✅ compilation complete! Run it with ./build.exe"