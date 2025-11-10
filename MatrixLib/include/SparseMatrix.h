// Created by ADMIN on 7/29/2025.

#ifndef SPARSEMATRIX_HPP
#define SPARSEMATRIX_HPP

#include <vector>
#include <map> /* This includes the STL std::map container. A map is a key-value data structure, perfect
                  for storing only non-zero elements with their position (i,j) as the key.*/
#include <utility> /* Required for using std::pair<int, int>, which will represent coordinates (i, j)
                      in the matrix.*/
#include <iostream>

/* class sparsematrix; It is designed to represent a matrix where most elements are zero,
 * so we store only non-zero values for memory efficiency.*/
class SparseMatrix {
private:
    int rows, cols;
    std::map<std::pair<int, int>, double> data;  // only stores non-zero values

public:
    SparseMatrix(int r, int c);   // constructor

    void set(int i, int j, double val);  // set value at a position
    double get(int i, int j) const;      // get value at a position

    void input();     // user enters non-zero elements
    void print() const;  // display the full matrix

    double determinant() const;

    SparseMatrix add(const SparseMatrix& other) const;

    SparseMatrix transpose() const;

    SparseMatrix multiply(const SparseMatrix& other) const;

    std::vector<std::vector<double>> toDense() const;

    int getRows() const { return rows; }
    int getCols() const { return cols; }


};

#endif
