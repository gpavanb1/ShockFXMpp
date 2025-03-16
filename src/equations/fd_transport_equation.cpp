#include "splitfxm/cell.h"
#include "splitfxm/schemes.h"
#include "equations/fd_transport_equation.h"

FDTransportEquation::FDTransportEquation(const FunctionType &F, const FunctionType &D, const FunctionType &S)
    : F_(F), D_(D), S_(S)
{
}

Eigen::VectorXd FDTransportEquation::residuals(const std::vector<CellPtr> &cell_sub, Schemes scheme, const std::map<std::string, double> &scheme_opts) const
{
    int ic = static_cast<int>(cell_sub.size()) / 2;
    return S_(cell_sub[ic]) - Dx(F_, cell_sub, scheme) + D2x(D_, cell_sub, scheme);
}

Eigen::VectorXd FDTransportEquation::mask(int size) const
{
    return Eigen::VectorXd::Ones(size);
}
