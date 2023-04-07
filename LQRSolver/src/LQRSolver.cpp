#include "LQRSolver.hpp"

LQRSolver::LQRSolver(Eigen::MatrixXd A_in, Eigen::MatrixXd B_in, Eigen::MatrixXd Q_in, Eigen::MatrixXd R_in)
: A(A_in), B(B_in), Q(Q_in), R(R_in) {
    solve();
}

// solve Liccati equation using Arimoto Potter method. 
void LQRSolver::solve() {
    const int dim_x = A.rows();
    const int dim_u = B.cols();

    Eigen::MatrixXd H = Eigen::MatrixXd::Zero(2 * dim_x, 2 * dim_x);
    H << A, -B * R.inverse() * B.transpose(), -Q, -A.transpose();

    // calculate eigenvalues and eigenvectors
    Eigen::EigenSolver<Eigen::MatrixXd> Eigs(H);

    Eigen::MatrixXcd eigvec = Eigen::MatrixXcd::Zero(2 * dim_x, dim_x);
    int j = 0;
    for (int i = 0; i < 2 * dim_x; ++i) {
        if (Eigs.eigenvalues()[i].real() < 0.0) {
            eigvec.col(j) = Eigs.eigenvectors().block(0, i, 2 * dim_x, 1);
            ++j;
        }
    }

    // calc P with stable eigen vector matrix
    Eigen::MatrixXcd Vs_1, Vs_2;
    Vs_1 = eigvec.block(0, 0, dim_x, dim_x);
    Vs_2 = eigvec.block(dim_x, 0, dim_x, dim_x);
    P = (Vs_2 * Vs_1.inverse()).real();

    K = R.inverse() * B.transpose() * P;
}
