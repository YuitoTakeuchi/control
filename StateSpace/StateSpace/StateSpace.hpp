#pragma once
#include <Eigen/Dense>

// SIMPLE STATE SPACE LIBRARY
// State Equation and Observation equation are expressed as follows.
// \dot{x} = Ax + Bu
//       y = Cx + Du

class StateSpace {
private:
    Eigen::MatrixXd A;
    Eigen::MatrixXd B;
    Eigen::MatrixXd C;
    Eigen::MatrixXd D;

    const int n, m, l;

    Eigen::VectorXd x;
    Eigen::VectorXd y;

public:
    StateSpace(int n, int m, int l);
    StateSpace(Eigen::MatrixXd A, Eigen::MatrixXd B, Eigen::MatrixXd C, Eigen::MatrixXd D);
    static bool stabilizable(Eigen::MatrixXd A, Eigen::MatrixXd B);
    static bool controllable(Eigen::MatrixXd A, Eigen::MatrixXd B);
    static bool detectable(Eigen::MatrixXd A, Eigen::MatrixXd C);
    static bool observable(Eigen::MatrixXd A, Eigen::MatrixXd C);

    bool stabilizable(){return stabilizable(A, B);};
    bool controllable(){return controllable(A, B);};
    bool detectable(){return detectable(A, C);};
    bool observable(){return observable(A, C);};

    void setA(Eigen::MatrixXd A_in) {
        if(A.rows() != n || A.cols() != n) return;
        A = A_in;
    };
    void setB(Eigen::MatrixXd B_in) {
        if(B.rows() != n || B.cols() != m) return;
        B = B_in;
    };
    void setC(Eigen::MatrixXd C_in) {
        if(C.rows() != l || C.cols() != n) return;
        C = C_in;
    };
    void setD(Eigen::MatrixXd D_in) {
        if(D.rows() != l || D.cols() != m) return;
        D = D_in;
    };
};