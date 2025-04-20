#include "splitfxm/cell.h"
#include "splitfxm/derivatives.h"
#include "splitfxm/schemes.h"
#include "equations/fd_transport_equation.h"

FDTransportEquation::FDTransportEquation(FunctionType F, FunctionType D, FunctionType S)
    : F(F), D(D), S(S) {}

Eigen::VectorXd FDTransportEquation::non_stiff_residuals(const std::vector<CellPtr> &cell_sub, Schemes scheme, const std::map<std::string, double> &scheme_opts) const
{
    return S(cell_sub[0]) - Dx(F, cell_sub, scheme) + D2x(D, cell_sub, scheme);
}

Eigen::VectorXd FDTransportEquation::stiff_residuals(const std::vector<CellPtr> &cell_sub, Schemes scheme, const std::map<std::string, double> &scheme_opts) const
{
    int size = cell_sub[0]->values().size();
    return Eigen::VectorXd::Zero(size);
}

Eigen::VectorXd FDTransportEquation::dae_mask(int size) const
{
    return Eigen::VectorXd::Ones(size);
}

Eigen::VectorXd FDTransportEquation::stiff_mask(int size) const
{
    return Eigen::VectorXd::Zero(size);
}

Eigen::VectorXd FDTransportEquation::non_stiff_mask(int size) const
{
    return Eigen::VectorXd::Ones(size);
}
