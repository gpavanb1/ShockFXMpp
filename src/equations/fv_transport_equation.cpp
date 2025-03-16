#include "splitfxm/cell.h"
#include "splitfxm/flux.h"
#include "equations/fv_transport_equation.h"

FVTransportEquation::FVTransportEquation(const FunctionType &F, const FunctionType &D, const FunctionType &S, const JacobianType &dFdU)
    : F_(F), D_(D), S_(S), dFdU_(dFdU)
{
}

Eigen::VectorXd FVTransportEquation::residuals(const std::vector<CellPtr> &cell_sub, Schemes scheme, const std::map<std::string, double> &scheme_opts) const
{
    int ic = static_cast<int>(cell_sub.size()) / 2;

    // Compute cell width as the average distance between adjacent cell centers
    double dxw = cell_sub[ic]->x() - cell_sub[ic - 1]->x();
    double dxe = cell_sub[ic + 1]->x() - cell_sub[ic]->x();
    double dx = 0.5 * (dxw + dxe);

    // Compute fluxes
    Eigen::VectorXd Fw, Fe;
    std::tie(Fw, Fe) = fluxes(F_, cell_sub, scheme, dFdU_);

    // Compute diffusion fluxes
    Eigen::VectorXd DFw, DFe;
    std::tie(DFw, DFe) = diffusion_fluxes(D_, cell_sub);

    // Compute right-hand side
    Eigen::VectorXd rhs = S_(cell_sub[ic]) - (1.0 / dx) * (Fe - Fw) + (1.0 / dx) * (DFe - DFw);
    return rhs;
}

Eigen::VectorXd FVTransportEquation::mask(int size) const
{
    return Eigen::VectorXd::Ones(size);
}
