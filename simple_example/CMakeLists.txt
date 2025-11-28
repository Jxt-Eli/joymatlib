cmake_minimum_required(VERSION 3.31)
project(SimpleMatrixExample)

set(CMAKE_CXX_STANDARD 20)

# Add the MatrixLib as a subdirectory
add_subdirectory(../MatrixLib MatrixLib)

# Create your executable
add_executable(simple_example main.cpp)

# Link against the MatrixLib
target_link_libraries(simple_example PRIVATE MatrixLib)

# Include directories for MatrixLib headers
target_include_directories(simple_example PRIVATE ../MatrixLib/include) 