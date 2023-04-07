#include "LQRSolver.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main() {
    std::filesystem::path file_path = __FILE__;
    std::ifstream setting_ifs(std::string(file_path.parent_path()) + "/setting.json");
    json setting = json::parse(setting_ifs);

    const int dim_x = setting["dim_x"].get<int>();
    const int dim_u = setting["dim_u"].get<int>();
    std::vector<std::vector<double>> A_in = setting["A"].get<std::vector<std::vector<double>>>();
    std::vector<std::vector<double>> B_in = setting["B"].get<std::vector<std::vector<double>>>();
    std::vector<std::vector<double>> Q_in = setting["Q"].get<std::vector<std::vector<double>>>();
    std::vector<std::vector<double>> R_in = setting["R"].get<std::vector<std::vector<double>>>();
    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(dim_x, dim_x);
    Eigen::MatrixXd B = Eigen::MatrixXd::Zero(dim_x, dim_u);
    Eigen::MatrixXd Q = Eigen::MatrixXd::Zero(dim_x, dim_x);
    Eigen::MatrixXd R = Eigen::MatrixXd::Zero(dim_u, dim_u);

    for(int i = 0; i < dim_x; ++i) {
        for(int j = 0; j < dim_x; ++j) {
            A(i, j) = A_in[i][j];
            Q(i, j) = Q_in[i][j];
        }
        for(int j = 0; j < dim_u; ++j) {
            B(i, j) = B_in[i][j];
        }
    }
    for(int i = 0; i < dim_u; ++i) for(int j = 0; j < dim_u; ++j) R(i, j) = R_in[i][j];

    LQRSolver sol(A, B, Q, R);
    Eigen::MatrixXd P; sol.getP(P);
    Eigen::MatrixXd K; sol.getK(K);

    Eigen::VectorXd x = Eigen::VectorXd::Zero(dim_x);
    Eigen::VectorXd u = Eigen::VectorXd::Zero(dim_u);

    std::cout << "The solution to Liccati Equation P is\n";
    std::cout << "P:\n" << P << "\n\n";
    std::cout << "Optimal feedback gain K is\n";
    std::cout << "K:\n" << K << "\n\n";
    
    const bool do_simulation = setting["simulation"]["execute"].get<bool>();
    if(do_simulation) {
        std::cout << "execute simulation...\n";
        const int max_iter = setting["simulation"]["max_iter"].get<int>();
        const double dt = setting["simulation"]["dt"].get<double>();
        std::vector<double> x_in = setting["simulation"]["initial_x"].get<std::vector<double>>();
        for(int i = 0; i < dim_x; ++i) x(i) = x_in[i];
        double t = 0.0;

        double x_history[dim_x][max_iter];
        double u_history[dim_u][max_iter];
        double t_histroy[max_iter];
        double J_history[max_iter];

        for(int i = 0; i < max_iter; ++i) {
            t_histroy[i] = t;
            u = -K*x;
            J_history[i] = (x.transpose() * Q * x + u.transpose() * R * u)(0);
            for(int j = 0; j < dim_x; ++j) x_history[j][i] = x(j);
            for(int j = 0; j < dim_u; ++j) u_history[j][i] = u(j);
            Eigen::VectorXd k1 = A * x + B * u;
            Eigen::VectorXd k2 = (A - B * K) * (x + k1 * dt/2.0);
            Eigen::VectorXd k3 = (A - B * K) * (x + k2 * dt/2.0);
            Eigen::VectorXd k4 = (A - B * K) * (x + k3 * dt);
            x += (k1 + 2.0 * k2 + 2.0 * k3 + k4) * dt / 6.0;
            t += dt;
        }

        // output result to text file
        std::ofstream result_log(std::string(file_path.parent_path()) + "/result/result.txt");
        result_log << max_iter << " " << dim_x << " " << dim_u << "\n";
        for(int i = 0; i < max_iter; ++i) {
            result_log << t_histroy[i] << " ";
            for(int j = 0; j < dim_x; ++j) result_log << x_history[j][i] << " ";
            for(int j = 0; j < dim_u; ++j) result_log << u_history[j][i] << " ";
            result_log << J_history[i] << "\n";
        }
    }
}