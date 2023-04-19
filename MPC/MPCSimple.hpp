#pragma once
#include <Eigen/Dense>

// x_{k+1} = A x_k + B u_k
// y_k = C x_k

class MPCSimple {
private:
    const Eigen::MatrixXd A;
    const Eigen::MatrixXd B;
    const Eigen::MatrixXd C;

    Eigen::MatrixXd F;
    Eigen::MatrixXd G;
    Eigen::MatrixXd H;
    const Eigen::MatrixXd Q, R; // 評価関数用

public:
    MPCSimple(Eigen::MatrixXd A, Eigen::MatrixXd B, Eigen::MatrixXd C, Eigen::MatrixXd Q, Eigen::MatrixXd R, int horizon)
};
