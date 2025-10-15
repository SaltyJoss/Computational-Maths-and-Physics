#include "ODESolver.h"
#include <iostream>
#include <functional>

// Main function to run tests
int main() {
    auto f = [](double x, double y) { return x + y; };

    double eulerResult = NumericalMethods::ODESolver::EulerMethod(1.0, 0.0, 10, 0.1, f);
    double rk4Result = NumericalMethods::ODESolver::RungeKutta4Method(1.0, 0.0, 10, 0.1, f);
    double fdResult = NumericalMethods::ODESolver::FiniteDifferenceMethod(1.0, 0.0, 10, 0.1, f);

	std::cout << "Running EulerMethod Test: " << eulerResult << "\n";
	std::cout << "Running Runge-Kutta4Method Test: " << rk4Result << "\n";
	std::cout << "Running FiniteDifferenceMethod Test: " << fdResult << "\n";

	return 0;
}