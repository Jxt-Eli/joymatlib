
#include <cstdlib>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Eigenvalues>

int main() {
    Eigen::Matrix3d A;
    A << -1.2,  2.3, -3.4,
          4.5, -5.6,  6.7,
         -7.8,  8.9, -9.0;

    Eigen::EigenSolver<Eigen::Matrix3d> solver(A);
    std::cout << "Eigenvalues of A:" << std::endl << solver.eigenvalues() << std::endl;
    return EXIT_SUCCESS;
}
