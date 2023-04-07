# control
control libraries written in c++

## package
- LQR Solver
  - solve Linear Quadratic Regurator Problem.
- StaetSpace
  - Basic State Space class.
  - This folder includes Extended State Space class which is used for robust control.

## Dependencies
If you are using CMake, libraries are installed automatically.
- Eigen
  - Required
  - Fast Linear Algebra Library
- nlohmann/json
  - Required
  - This library is used for reading settings written in json format.