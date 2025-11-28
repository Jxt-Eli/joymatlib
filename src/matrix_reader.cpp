#include "matrix_reader.hpp"
#include <fstream>
#include <sstream>

std::vector<std::vector<double>> read_matrix(const std::string& filename) {
    std::vector<std::vector<double>> matrix;
    std::ifstream infile(filename);
    std::string line;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::vector<double> row;
        double num;
        while (iss >> num) {
            row.push_back(num);
        }
        if (!row.empty()) {
            matrix.push_back(row);
        }
    }
    return matrix;
}