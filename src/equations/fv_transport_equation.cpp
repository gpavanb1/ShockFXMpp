#include "splitfxm/cell.h"
#include "splitfxm/flux.h"
#include "splitfxm/schemes.h"
#include "equations/fv_transport_equation.h"

FVTransportEquation::FVTransportEquation(FunctionType F, FunctionType D, FunctionType S, JacobianType dFdU)
    : F(F), D(D), S(S), dFdU(dFdU) {}

Eigen::VectorXd FVTransportEquation::non_stiff_residuals(const std::vector<CellPtr> &cell_sub, Schemes scheme, const std::map<std::string, double> &scheme_opts) const
{
    // Cell width
    // Calculate for center cell
    // Average of distance between adjacent cell centers
    int ic = cell_sub.size() / 2;
    double dxw = cell_sub[ic]->x() - cell_sub[ic - 1]->x();
    double dxe = cell_sub[ic + 1]->x() - cell_sub[ic]->x();
    double dx = 0.5 * (dxw + dxe);

    auto [Fw, Fe] = fluxes(F, cell_sub, scheme, dFdU);
    auto [DFw, DFe] = diffusion_fluxes(D, cell_sub);
    return S(cell_sub[0]) - (1 / dx) * (Fe - Fw) + (1 / dx) * (DFe - DFw);
}

Eigen::VectorXd FVTransportEquation::stiff_residuals(const std::vector<CellPtr> &cell_sub, Schemes scheme, const std::map<std::string, double> &scheme_opts) const
{
    int size = cell_sub[0]->values().size();
    return Eigen::VectorXd::Zero(size);
}

Eigen::VectorXd FVTransportEquation::dae_mask(int size) const
{
    return Eigen::VectorXd::Ones(size);
}

Eigen::VectorXd FVTransportEquation::stiff_mask(int size) const
{
    return Eigen::VectorXd::Zero(size);
}

Eigen::VectorXd FVTransportEquation::non_stiff_mask(int size) const
{
    return Eigen::VectorXd::Ones(size);
}
