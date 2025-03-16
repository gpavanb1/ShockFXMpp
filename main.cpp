#include <map>
#include <memory>
#include <string>
#include <spdlog/spdlog.h>
#include "Eigen/Dense"
#include "models/euler1d_conservative.h"
#include "splitfxm/bc.h"
#include "splitfxm/domain.h"
#include "splitfxm/schemes.h"
#include "splitfxm/simulation.h"

int main()
{
    std::string method = "FVM";

    // Euler equations with gamma for ideal gas
    auto m = std::make_shared<Euler1DConservative>(1.4, method);

    // Create a domain for the shock tube
    auto d = Domain::from_size(100, 1, 1, {"rho", "rhou", "E"});

    // Set default initial conditions
    auto ics = std::map<std::string, std::string>{};

    // Boundary conditions (transmissive for both sides)
    BCMap bcs;
    bcs["rho"]["LEFT"] = std::make_pair("neumann", 0.0);
    bcs["rho"]["RIGHT"] = std::make_pair("neumann", 0.0);
    bcs["rhou"]["LEFT"] = std::make_pair("neumann", 0.0);
    bcs["rhou"]["RIGHT"] = std::make_pair("neumann", 0.0);
    bcs["E"]["LEFT"] = std::make_pair("neumann", 0.0);
    bcs["E"]["RIGHT"] = std::make_pair("neumann", 0.0);

    // Create a simulation object
    auto s = std::make_shared<Simulation>(d, m, ics, bcs, Schemes::FV_LAX_FRIEDRICHS);

    // Initial conditions
    int rho_idx = d->component_index("rho");
    int rhou_idx = d->component_index("rhou");
    int E_idx = d->component_index("E");
    for (auto &cell : d->interior())
    {
        double x = cell->x();
        cell->set_value(rho_idx, x < 0.5 ? 1.0 : 0.125);
        cell->set_value(rhou_idx, 0.0);
        cell->set_value(E_idx, (x < 0.5) ? 2.5 : 0.25);
    }

    // Evolve in time (using a small time step due to the shock)
    std::vector<int> split_locs = {1};
    s->evolve_sim(0.2, split_locs, "BDF3");

    // Get the primitive values
    std::vector<Eigen::VectorXd> domain_primitives;
    for (auto &cell : d->interior())
    {
        Eigen::VectorXd values = cell->values();
        Eigen::VectorXd primitives = m->conservative_to_primitive(values);
        domain_primitives.push_back(primitives);
    }

    // Output the values
    auto interior = d->interior();
    for (int i = 0; i < interior.size(); i++)
    {
        std::cout << interior[i]->x() << " ";
        std::cout << domain_primitives[i].transpose() << std::endl;
    }
}