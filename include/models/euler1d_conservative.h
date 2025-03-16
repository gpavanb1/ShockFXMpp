// Euler1DConservative.h
#ifndef EULER1D_CONSERVATIVE_H
#define EULER1D_CONSERVATIVE_H

#include <memory>
#include <Eigen/Dense>
#include "splitfxm/equation.h"
#include "splitfxm/error.h"
#include "splitfxm/model.h"

class Euler1DConservative : public Model
{
public:
    double gamma_;
    EquationPtr equation_;

    Euler1DConservative(double gamma = 1.4, std::string method = "FVM", double eps = 1e-10);

    Eigen::VectorXd conservative_to_primitive(const Eigen::VectorXd &U) const;
};

#endif // EULER1D_CONSERVATIVE_H