// standard libraries
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

// external libraries
#include "nlohmann/json.hpp"

// internal libraries
#include "StateSpace.hpp"

using json = nlohmann::json;

int main() {
    std::filesystem::path file_path = __FILE__;
    std::ifstream setting_ifs(std::string(file_path.parent_path()) + "/setting.json");
    json setting = json::parse(setting_ifs);

    const int dim_x = setting["dim_x"].get<int>();
    const int dim_u = setting["dim_u"].get<int>();
    const int dim_y = setting["dim_y"].get<int>();
    std::vector<std::vector<double>> A_in = setting["A"].get<std::vector<std::vector<double>>>();
    std::vector<std::vector<double>> B_in = setting["B"].get<std::vector<std::vector<double>>>();
    std::vector<std::vector<double>> C_in = setting["C"].get<std::vector<std::vector<double>>>();
    std::vector<std::vector<double>> D_in = setting["D"].get<std::vector<std::vector<double>>>();
    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(dim_x, dim_x);
    Eigen::MatrixXd B = Eigen::MatrixXd::Zero(dim_x, dim_u);
    Eigen::MatrixXd C = Eigen::MatrixXd::Zero(dim_y, dim_x);
    Eigen::MatrixXd D = Eigen::MatrixXd::Zero(dim_y, dim_u);

    for(int i = 0; i < dim_x; ++i) {
        for(int j = 0; j < dim_x; ++j) A(i, j) = A_in[i][j];
        for(int j = 0; j < dim_u; ++j) B(i, j) = B_in[i][j];
    }
    for(int i = 0; i < dim_y; ++i) {
        for(int j = 0; j < dim_x; ++j) C(i, j) = C_in[i][j];
        for(int j = 0; j < dim_u; ++j) D(i, j) = D_in[i][j];
    }

    StateSpace ss(A, B, C, D);

    std::cout << "A:\n" << A << "\nB:\n" << B << "\nC\n" << C << "\nD\n" << D << "\n";

    std::cout << "Stabilizable: " << (ss.stabilizable() ? "TRUE" : "FALSE") << "\n";
    std::cout << "controllable: " << (ss.controllable() ? "TRUE" : "FALSE") << "\n";
    std::cout << "detectable:   " << (ss.detectable()   ? "TRUE" : "FALSE") << "\n";
    std::cout << "observable:   " << (ss.observable()   ? "TRUE" : "FALSE") << "\n";
}