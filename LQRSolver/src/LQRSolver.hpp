#pragma once
#include <Eigen/Dense>

class LQRSolver {
private:
    const Eigen::MatrixXd A;
    const Eigen::MatrixXd B;
    const Eigen::MatrixXd Q;
    const Eigen::MatrixXd R;
    Eigen::MatrixXd P;
    Eigen::MatrixXd K;
    void solve();
public:
    LQRSolver(Eigen::MatrixXd A, Eigen::MatrixXd B, Eigen::MatrixXd Q, Eigen::MatrixXd R);
    void getK(Eigen::MatrixXd& K_ref) {K_ref = K;};
    void getP(Eigen::MatrixXd& P_ref) {P_ref = P;};
};