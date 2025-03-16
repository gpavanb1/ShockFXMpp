#ifndef FV_TRANSPORT_EQUATION_H
#define FV_TRANSPORT_EQUATION_H

#include <functional>
#include <map>
#include <vector>
#include "Eigen/Dense"
#include "splitfxm/cell.h"
#include "splitfxm/flux.h"
#include "splitfxm/equation.h"
#include "splitfxm/schemes.h"

class FVTransportEquation : public Equation
{
public:
    FVTransportEquation(const FunctionType &F, const FunctionType &D, const FunctionType &S, const JacobianType &dFdU);

    Eigen::VectorXd residuals(const std::vector<CellPtr> &cell_sub, Schemes scheme, const std::map<std::string, double> &scheme_opts = {}) const override;

    Eigen::VectorXd mask(int size) const override;

private:
    FunctionType F_, D_, S_;
    JacobianType dFdU_;
};

#endif // FV_TRANSPORT_EQUATION_H
