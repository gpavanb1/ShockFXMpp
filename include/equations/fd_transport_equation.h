#ifndef FD_TRANSPORT_EQUATION_H
#define FD_TRANSPORT_EQUATION_H

#include <functional>
#include <map>
#include <vector>
#include <Eigen/Dense>
#include "splitfxm/cell.h"
#include "splitfxm/equation.h"
#include "splitfxm/schemes.h"

class FDTransportEquation : public Equation
{
public:
    FDTransportEquation(FunctionType F, FunctionType D, FunctionType S);

    Eigen::VectorXd dae_mask(int size) const override;
    Eigen::VectorXd stiff_mask(int size) const override;
    Eigen::VectorXd non_stiff_mask(int size) const override;

private:
    FunctionType F;
    FunctionType D;
    FunctionType S;

    Eigen::VectorXd stiff_residuals(const std::vector<CellPtr> &cell_sub, Schemes scheme, const std::map<std::string, double> &scheme_opts = {}) const;
    Eigen::VectorXd non_stiff_residuals(const std::vector<CellPtr> &cell_sub, Schemes scheme, const std::map<std::string, double> &scheme_opts = {}) const;
};

#endif // FD_TRANSPORT_EQUATION_H
