#include "StateSpace.hpp"

StateSpace::StateSpace(int n, int m, int l):n(n), m(m), l(l) {
    A = Eigen::MatrixXd::Zero(n, n);
    B = Eigen::MatrixXd::Zero(n, m);
    C = Eigen::MatrixXd::Zero(l, n);
    D = Eigen::MatrixXd::Zero(l, m);
    
    x = Eigen::VectorXd::Zero(n);
    y = Eigen::VectorXd::Zero(l);
}
StateSpace::StateSpace(Eigen::MatrixXd A, Eigen::MatrixXd B, Eigen::MatrixXd C, Eigen::MatrixXd D) 
 :n(A.rows()), m(B.cols()), l(C.rows()), A(A), B(B), C(C), D(D){
    assert(A.rows() == A.cols());
    assert(A.rows() == B.rows());
    assert(C.cols() == A.rows());
    assert(D.rows() == C.rows());
    assert(D.cols() == B.cols());

    x = Eigen::VectorXd::Zero(n);
    y = Eigen::VectorXd::Zero(l);
}

bool StateSpace::stabilizable(Eigen::MatrixXd A, Eigen::MatrixXd B) {
    // iff for all \lambda rank[\lambda I - A B] = n
    // lambda is in eigenvalues of A, and its real part is non-negative
    bool ret = true;
    int n = A.rows();
    int m = B.cols();
    Eigen::EigenSolver<Eigen::MatrixXd> s(A);
    Eigen::VectorXcd eigenValues = s.eigenvalues();
    int nEigenValues = eigenValues.rows();

    for(int i = 0; i < nEigenValues; ++i) {
        std::complex<double> eigenValue = eigenValues(i);
        if(eigenValue.real() < 0) continue;
        Eigen::MatrixXcd testMatrix = Eigen::MatrixXcd::Zero(n, n+m);
        testMatrix << eigenValue*Eigen::MatrixXd::Identity(n, n) - A, B;
        Eigen::JacobiSVD decomp(testMatrix);
        int rank = decomp.rank();
        if(rank < n) {
            ret = false;
            break;
        }
    }
    return ret;
}

bool StateSpace::controllable(Eigen::MatrixXd A, Eigen::MatrixXd B) {
    // iff for all \lambda \in C rank[\lambda I - A B] = n
    // lambda is in eigenvalues of A
    bool ret = true;
    int n = A.rows();
    int m = B.cols();
    Eigen::EigenSolver<Eigen::MatrixXd> s(A);
    Eigen::VectorXcd eigenValues = s.eigenvalues();
    int nEigenValues = eigenValues.rows();

    for(int i = 0; i < nEigenValues; ++i) {
        std::complex<double> eigenValue = eigenValues(i);
        Eigen::MatrixXcd testMatrix = Eigen::MatrixXcd::Zero(n, n+m);
        testMatrix << eigenValue*Eigen::MatrixXd::Identity(n, n) - A, B;
        Eigen::JacobiSVD decomp(testMatrix);
        int rank = decomp.rank();
        if(rank < n) {
            ret = false;
            break;
        }
    }
    return ret;
}

bool StateSpace::detectable(Eigen::MatrixXd A, Eigen::MatrixXd C) {
    // iff for all \lambda rank[\lambda I - A B] = n
    // lambda is in eigenvalues of A, and its real part is non-negative
    bool ret = true;
    int n = A.rows();
    int l = C.rows();
    Eigen::EigenSolver<Eigen::MatrixXd> s(A);
    Eigen::VectorXcd eigenValues = s.eigenvalues();
    int nEigenValues = eigenValues.rows();
    for(int i = 0; i < nEigenValues; ++i) {
        std::complex<double> eigenValue = eigenValues(i);
        if(eigenValue.real() < 0) continue;
        Eigen::MatrixXcd testMatrix = Eigen::MatrixXcd::Zero(n+l, n);
        testMatrix << eigenValue*Eigen::MatrixXd::Identity(n, n) - A, C;
        Eigen::JacobiSVD decomp(testMatrix);
        int rank = decomp.rank();
        if(rank < n) {
            ret = false;
            break;
        }
    }
    return ret;
}

bool StateSpace::observable(Eigen::MatrixXd A, Eigen::MatrixXd C) {
    // iff for all \lambda rank[\lambda I - A B] = n
    // lambda is in eigenvalues of A, and its real part is non-negative
    bool ret = true;
    int n = A.rows();
    int l = C.rows();
    Eigen::EigenSolver<Eigen::MatrixXd> s(A);
    Eigen::VectorXcd eigenValues = s.eigenvalues();
    int nEigenValues = eigenValues.rows();
    for(int i = 0; i < nEigenValues; ++i) {
        std::complex<double> eigenValue = eigenValues(i);
        Eigen::MatrixXcd testMatrix = Eigen::MatrixXcd::Zero(n+l, n);
        testMatrix << eigenValue*Eigen::MatrixXd::Identity(n, n) - A, C;
        Eigen::JacobiSVD decomp(testMatrix);
        int rank = decomp.rank();
        if(rank < n) {
            ret = false;
            break;
        }
    }
    return ret;
}