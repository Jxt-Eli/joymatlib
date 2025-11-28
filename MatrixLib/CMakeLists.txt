cmake_minimum_required(VERSION 3.31)
project(MatrixLib)

set(CMAKE_CXX_STANDARD 20)

add_library(MatrixLib STATIC
        src/SparseMatrix.cpp
        src/LUDecomposition.cpp
        src/QRDecomposition.cpp
        src/SVDDecomposition.cpp
        src/EigenSolver.cpp

        include/SparseMatrix.h
        include/LUDecomposition.h
        include/QRDecomposition.h
        include/SVDDecomposition.h
        include/EigenSolver.h
)

# Make headers available to anything that links this library
target_include_directories(MatrixLib PUBLIC include)

# Define the executable (your test/main file)
add_executable(main_app src/main.cpp)

# Link the static library to the executable
target_link_libraries(main_app PRIVATE MatrixLib)


target_include_directories(MatrixLib PUBLIC include)
