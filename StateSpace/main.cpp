#include "StateSpace.hpp"
#include <iostream>

int main() {
    StateSpace ss(2, 2, 1);

    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(2, 2);
    A << 0, 0, 0, -1;
    Eigen::MatrixXd B = Eigen::MatrixXd::Zero(2, 1);
    B << 1, 1;
    Eigen::MatrixXd C = Eigen::MatrixXd::Zero(1, 2);
    C << 1, 1;
    ss.setA(A);
    ss.setB(B);
    ss.setC(C);
    std::cout << "A: \n" << A << "\nB: \n" << B << "\nC: \n" << C << std::endl;;
    std::cout << "stabilizable: " << ss.stabilizable() << std::endl;
    std::cout << "controllable: " << ss.controllable() << std::endl;
    std::cout << "detectable:   " << ss.detectable()   << std::endl;
    std::cout << "observable:   " << ss.observable()   << std::endl;

    A = Eigen::MatrixXd::Zero(2, 2);
    A << -1, 0, 0, -1;
    B = Eigen::MatrixXd::Zero(2, 1);
    B << 1, 1;
    C = Eigen::MatrixXd::Zero(1, 2);
    C << 1, 1;
    ss.setA(A);
    ss.setB(B);
    ss.setC(C);
    std::cout << "A: \n" << A << "\nB: \n" << B << "\nC: \n" << C << std::endl;;
    std::cout << "stabilizable: " << ss.stabilizable() << std::endl;
    std::cout << "controllable: " << ss.controllable() << std::endl;
    std::cout << "detectable:   " << ss.detectable()   << std::endl;
    std::cout << "observable:   " << ss.observable()   << std::endl;
}