#include "mathlib/Integration/Integrate_ODE.hpp"
#include "mathlib/ODE/ExplicitSolvers.hpp"

#include <iostream>
#include <vector>
#include <functional>

// Main function to run tests
int main() {
    auto f = [](double t, const double y) -> double {
		return -y; 
	};

	double y0 = 1.0;	  // Initial condition
	double t0 = 0.0;	  // Initial time
	double t_final = 1.0; // Final time
	double dt = 0.1;		// Step size

	// Lamdba wrapper of Euler function
	auto euler_lambda = [](const std::function<double(double, const double&)>& f, double t, const double& y, double dt) -> double {
		return mathlib::ODE::euler_step<double>(y, t, dt, f);
	};

	std::vector<double> trajectory = mathlib::Integration::integrate_ODE<double>(
		f, y0, t0, t_final, dt, euler_lambda
	);

	// Test output
	double t = t0;
	for (auto y : trajectory) {
		std::cout << "t=" << t << ", y=" << y << "\n";
		t += dt;
	}

	return 0;
}