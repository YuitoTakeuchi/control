#include "ExtendedStateSpace.hpp"

ExtendedStateSpace::ExtendedStateSpace(int n, int m, int p)
 :StateSpace(n, m), p(p) {
    D22 = Eigen::MatrixXd::Zero();
};