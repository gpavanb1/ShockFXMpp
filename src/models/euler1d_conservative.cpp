#include <string>
#include "Eigen/Dense"
#include "splitfxm/equations/fd_transport.h"
#include "splitfxm/equations/fv_transport.h"
#include "models/euler1d_conservative.h"

Euler1DConservative::Euler1DConservative(double gamma, std::string method, double eps) : Model(nullptr), gamma_(gamma), equation_(nullptr)
{

    // Define the flux function
    auto F = [this](const CellPtr &cell) -> Eigen::VectorXd
    {
        Eigen::VectorXd U = cell->values();
        double gamma = this->gamma_;
        Eigen::VectorXd F(3);
        double U1 = U(0), U2 = U(1), U3 = U(2);
        F(0) = U2;
        F(1) = 0.5 * (3 - gamma) * U2 * U2 / U1 + (gamma - 1) * U3;
        F(2) = gamma * U2 * U3 / U1 - 0.5 * (gamma - 1) * (U2 * U2 * U2 / (U1 * U1));
        return F;
    };

    // Diffusion term (not used in standard Euler equations)
    auto D = [](const CellPtr &cell) -> Eigen::VectorXd
    {
        return Eigen::VectorXd::Zero(3);
    };

    // Source term (assuming no external forces)
    auto S = [](const CellPtr &cell) -> Eigen::VectorXd
    {
        return Eigen::VectorXd::Zero(3);
    };

    // Derivative of flux function
    auto dFdU = [this](const Eigen::VectorXd &U) -> Eigen::MatrixXd
    {
        double gamma = this->gamma_;
        Eigen::MatrixXd dF_matrix(3, 3);
        double U1 = U(0), U2 = U(1), U3 = U(2);

        dF_matrix(0, 0) = 0.0;
        dF_matrix(0, 1) = 1.0;
        dF_matrix(0, 2) = 0.0;

        dF_matrix(1, 0) = -0.5 * (3 - gamma) * (U2 * U2 / (U1 * U1));
        dF_matrix(1, 1) = (3 - gamma) * U2 / U1;
        dF_matrix(1, 2) = gamma - 1;

        dF_matrix(2, 0) = -gamma * U2 * U3 / (U1 * U1) + (gamma - 1) * (U2 * U2 * U2 / (U1 * U1 * U1));
        dF_matrix(2, 1) = gamma * U3 / U1 - 1.5 * (gamma - 1) * (U2 * U2 / (U1 * U1));
        dF_matrix(2, 2) = gamma * U2 / U1;

        return dF_matrix;
    };

    if (method == "FDM")
    {
        equation_ = std::make_shared<FDTransportEquation>(F, D, S);
    }
    else if (method == "FVM")
    {
        equation_ = std::make_shared<FVTransportEquation>(F, D, S, dFdU);
    }
    else
    {
        throw SFXM("Invalid numerical method specified");
    }
    Model::set_equation(equation_);
}

Eigen::VectorXd Euler1DConservative::conservative_to_primitive(const Eigen::VectorXd &U) const
{
    Eigen::VectorXd primitive(3);
    double U1 = U(0), U2 = U(1), U3 = U(2);
    primitive(0) = U1;
    primitive(1) = U2 / U1;
    primitive(2) = (gamma_ - 1) * (U3 - 0.5 * U2 * U2 / U1);
    return primitive;
}
