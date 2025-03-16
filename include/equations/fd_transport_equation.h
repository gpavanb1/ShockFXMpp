#ifndef FD_TRANSPORT_EQUATION_H
#define FD_TRANSPORT_EQUATION_H

#include <map>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include "splitfxm/cell.h"
#include "splitfxm/equation.h"
#include "splitfxm/derivatives.h"

class FDTransportEquation : public Equation
{
public:
    FDTransportEquation(const FunctionType &F, const FunctionType &D, const FunctionType &S);

    Eigen::VectorXd residuals(const std::vector<CellPtr> &cell_sub, Schemes scheme, const std::map<std::string, double> &scheme_opts) const;
    Eigen::VectorXd mask(int size) const;

private:
    FunctionType F_;
    FunctionType D_;
    FunctionType S_;
};

#endif // FD_TRANSPORT_EQUATION_H
