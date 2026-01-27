#include "splitfxm/cell.h"
#include "splitfxm/flux.h"
#include "splitfxm/schemes.h"
#include "equations/fv_transport_equation.h"

FVTransportEquation::FVTransportEquation(FunctionType F, FunctionType D, FunctionType S, JacobianType dFdU)
    : F(F), D(D), S(S), dFdU(dFdU) {}

Eigen::VectorXd FVTransportEquation::non_stiff_residuals(const std::vector<CellPtr>& cell_sub) const
{
    int target_size = stencil_sizes.at(scheme_);
    if (cell_sub.size() != (size_t)target_size)
    {
        throw SFXM("FVTransportEquation: Improper stencil size for scheme. Expected " + std::to_string(target_size) + ", got " + std::to_string(cell_sub.size()));
    }

    int ic = target_size / 2;

    double dxw = cell_sub[ic]->coords()[0] - cell_sub[ic - 1]->coords()[0];
    double dxe = cell_sub[ic + 1]->coords()[0] - cell_sub[ic]->coords()[0];
    double dx = 0.5 * (dxw + dxe);

    auto [Fw, Fe] = fluxes(F, cell_sub, scheme_, dFdU);
    auto [DFw, DFe] = diffusion_fluxes(D, cell_sub);

    return S(cell_sub[ic]) - (1 / dx) * (Fe - Fw) + (1 / dx) * (DFe - DFw);
}

Eigen::VectorXd FVTransportEquation::stiff_residuals(const std::vector<CellPtr>& cell_sub) const
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
