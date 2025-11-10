cmake_minimum_required(VERSION 3.31)
project(MatrixExample)

set(CMAKE_CXX_STANDARD 20)

# Add the MatrixLib as a subdirectory
add_subdirectory(../MatrixLib MatrixLib)

# Create your executable
add_executable(example_app main.cpp)

# Link against the MatrixLib
target_link_libraries(example_app PRIVATE MatrixLib)

# Include directories for MatrixLib headers
target_include_directories(example_app PRIVATE ../MatrixLib/include) 