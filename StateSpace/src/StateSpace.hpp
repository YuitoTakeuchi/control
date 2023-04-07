#pragma once
#include <Eigen/Dense>

class StateSpace {
private:
    Eigen::MatrixXd A;
    Eigen::MatrixXd B;
    Eigen::MatrixXd C;
    Eigen::MatrixXd D;

    const int n, m;

public:
    StateSpace(int n, int m);
    StateSpace(Eigen::MatrixXd A, Eigen::MatrixXd B, Eigen::MatrixXd C, Eigen::MatrixXd D);
    static bool stabilizable(Eigen::MatrixXd A, Eigen::MatrixXd B);
    static bool controllable(Eigen::MatrixXd A, Eigen::MatrixXd B);
    static bool detectable(Eigen::MatrixXd A, Eigen::MatrixXd C);
    static bool observable(Eigen::MatrixXd A, Eigen::MatrixXd C);


};