#pragma once
#include "StateSpace.hpp"
#include <Eigen/Dense>

class ExtendedStateSpace: public StateSpace {
    Eigen::MatrixXd A;
    Eigen::MatrixXd B1, B2;
    Eigen::MatrixXd C1, C2;
    Eigen::MatrixXd D11, D12, D21, D22;

    const int p; // sizes of z

    ExtendedStateSpace(int n, int m, int p);
    ExtendedStateSpace(Eigen::MatrixXd A, Eigen::MatrixXd B1, Eigen::MatrixXd B2,
     Eigen::MatrixXd C1, Eigen::MatrixXd C2, Eigen::MatrixXd D11, Eigen::MatrixXd D12,
     Eigen::MatrixXd D21, Eigen::MatrixXd D22);
};