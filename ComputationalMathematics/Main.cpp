#include "ODESolver.h"
#include <iostream>
#include <functional>

void ODESolver(std::function<double(double, double)> f);

// Main function to run tests
int main() {
    auto f = [](double t, double y) { return t + y; };

	std::cout 
		<< "TESTING ODE SOLVERS:\n" 
		<< "=====\n\n";
	ODESolver(f);

	return 0;
}

// Function to test ODE solvers
void ODESolver(std::function<double(double, double)> f) {
	double eulerResult = NumericalMethods::ODESolver::EulerMethod(1.0, 0.0, 1, 0.1, f);
	double midpointResult = NumericalMethods::ODESolver::MidpointMethod(1.0, 0.0, 1, 0.1, f);
	double rk4Result = NumericalMethods::ODESolver::RungeKutta4Method(1.0, 0.0, 1, 0.1, f);

	double eulerResult2 = NumericalMethods::ODESolver::EulerMethod(1.0, 0.0, 1, 0.5, f);
	double midpointResult2 = NumericalMethods::ODESolver::MidpointMethod(1.0, 0.0, 1, 0.5, f);
	double rk4Result2 = NumericalMethods::ODESolver::RungeKutta4Method(1.0, 0.0, 1, 0.5, f);

	double eulerResult3 = NumericalMethods::ODESolver::EulerMethod(1.0, 0.0, 1, 0.25, f);
	double midpointResult3 = NumericalMethods::ODESolver::MidpointMethod(1.0, 0.0, 1, 0.25, f);
	double rk4Result3 = NumericalMethods::ODESolver::RungeKutta4Method(1.0, 0.0, 1, 0.25, f);

	double eulerResult4 = NumericalMethods::ODESolver::EulerMethod(1.0, 0.0, 1, 0.01, f);
	double midpointResult4 = NumericalMethods::ODESolver::MidpointMethod(1.0, 0.0, 1, 0.01, f);
	double rk4Result4 = NumericalMethods::ODESolver::RungeKutta4Method(1.0, 0.0, 1, 0.01, f);

	std::cout
		<< "Running EulerMethod Test: " << "\n"
		<< "-----\n"
		<< "\tOutput: " << eulerResult << ", " << eulerResult2 << ", " << eulerResult3 << ", " << eulerResult4 << "\n\n\n"
		<< "Running MidpointMethod Test: " << "\n"
		<< "-----\n"
		<< "\tOutput: " << midpointResult << ", " << midpointResult2 << ", " << midpointResult3 << ", " << midpointResult4 << "\n\n\n"
		<< "Running Runge-Kutta4Method Test: " << "\n"
		<< "-----\n"
		<< "\tOutput: " << rk4Result << ", " << rk4Result2 << ", " << rk4Result3 << ", " << rk4Result4 << "\n\n\n";

}
/* Predicted Output (through my own calculations):
 * eulerResult -> 
 * rk4Result -> 
 * fdResult -> 
 */