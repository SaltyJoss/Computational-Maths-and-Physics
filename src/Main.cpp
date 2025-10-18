#include "mathlib/Integration/Integrate_ODE.hpp"
#include "mathlib/ODE/ExplicitSolvers.hpp"
#include "mathlib/Constants/cmath.hpp"
#include "physlib/Constants/cphys.hpp"
#include <iostream>
#include <iomanip> 
#include <vector>
#include <functional>
using namespace physlib::cphys;
using namespace mathlib::cmath;

// Main function to run tests
int main() {
    std::cout << std::fixed << std::setprecision(20);   // Set output to fixed-point, 20dp

    // Test math constants
    std::cout 
        << "Math constants:\n"
        << "e         = " << e << "\n"
        << "pi        = " << pi << "\n"
        << "two_pi    = " << two_pi << "\n"
        << "pi/2      = " << pi_over_2 << "\n"
        << "pi/4      = " << pi_over_4 << "\n"
        << "1/pi      = " << inv_pi << "\n"
        << "2/pi      = " << two_over_pi << "\n"
        << "phi       = " << phi << "\n"
        << "sqrt2     = " << sqrt2 << "\n"
        << "inv_sqrt2 = " << inv_sqrt2 << "\n";

    // Test physics constants
    std::cout 
        << "\nPhysics constants:\n"
        << "G         = " << G << " m^3/kg/s^2\n"
        << "mu_Earth  = " << mu_Earth << " m^3/s^2\n"
        << "g_Earth   = " << g_Earth << " m/s^2\n"
        << "g_Moon    = " << g_Moon << " m/s^2\n"
        << "g_Mars    = " << g_Mars << " m/s^2\n"
        << "c         = " << c << " m/s\n"
        << "microgravity_threshold    = " << microgravity_threshold << " m/s^2\n"
        << "air_density               = " << air_density << " kg/m^3\n"
        << "vacuum_density            = " << vacuum_density << "\n";

    // Derived tests
    double circumference = 2 * pi * 1.0; // radius = 1
    double weight_on_earth = 75.0 * g_Earth; // 75kg object
    double microgravity_limit = g_Earth * microgravity_threshold;

    std::cout 
        << "\nDerived tests with constants:\n"
        << "Circumference of unit circle = " << circumference << "\n"
        << "Weight of 75kg object on Earth = " << weight_on_earth << " N\n"
        << "Microgravity threshold (earth) = " << microgravity_limit << " m/s^2\n";

	return 0;
}