#include "MPCSimple.hpp"

MPCSimple::MPCSimple(Eigen::MatrixXd A, Eigen::MatrixXd B, Eigen::MatrixXd C, Eigen::MatrixXd Q, Eigen::MatrixXd R, int horizon)
: A(A), B(B), C(C), Q(Q), R(R) {
    int n = A.rows();
    int m = B.cols();
    int l = C.rows();

    F = Eigen::MatrixXd::Zero(n*horizon, n);
    G = Eigen::MatrixXd::Zero(n*horizon, m*horizon);
    H = Eigen::MatrixXd::Zero(l*horizon, n*horizon);

    Eigen::MatrixXd powA = A;
    Eigen::MatrixXd powBA = B;
    for(int i = 0; i < horizon; ++i) {
        F.block(n*i, 0, n, n) = powA;
        H.block(l*i, n*i, l, n) = C;
        for(int j = 0; j < horizon; ++j) {
            G.block(n*i, n*j, n, n) = powBA
        }
        powA *= A;
        powBA *= A;

    }


}