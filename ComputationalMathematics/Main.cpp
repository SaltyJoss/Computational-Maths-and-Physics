#include "ODESolver.h"
#include <iostream>
#include <functional>

void ODESolver(std::function<double(double, double)> f);

// Main function to run tests
int main() {
    auto f = [](double t, double y) { return t + y; };

	std::cout << "Testing ODE Solvers with dy/dt = t + y, y(0) = 0:\n\n";
	ODESolver(f);

	return 0;
}

// Function to test ODE solvers
void ODESolver(std::function<double(double, double)> f) {
	double eulerResult = NumericalMethods::ODESolver::EulerMethod(1.0, 0.0, 1, 0.25, f);
	double fdResult = NumericalMethods::ODESolver::FiniteDifferenceMethod(1.0, 0.0, 1, 0.25, f);
	double rk4Result = NumericalMethods::ODESolver::RungeKutta4Method(1.0, 0.0, 1, 0.25, f);

	std::cout
		<< "Running EulerMethod Test: " << "\n"
		<< "-----\n"
		<< "\tOutput: " << eulerResult << "\n\n\n"
		<< "Running FiniteDifferenceMethod Test: " << "\n"
		<< "-----\n"
		<< "\tOutput: " << fdResult << "\n\n\n"
		<< "Running Runge-Kutta4Method Test: " << "\n"
		<< "-----\n"
		<< "\tOutput: " << rk4Result << "\n\n\n";
}
/* Predicted Output (through my own calculations):
 * eulerResult -> 
 * rk4Result -> 
 * fdResult -> 
 */