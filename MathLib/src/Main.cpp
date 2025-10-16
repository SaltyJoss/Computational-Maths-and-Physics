#include "mathlib/ODESolver.h"
#include <iostream>
#include <functional>

void ODESolver(std::function<double(double, double)> f);
int test(std::function<double(double, double)> f);

// Main function to run tests
int main() {
    auto f = [](double t, double y) { return t + y; };

	test(f);

	return 0;
}

// Function to test ODE solvers
void ODESolver(std::function<double(double, double)> f) {
	std::cout
		<< "TESTING ODE SOLVERS:\n"
		<< "=====\n\n";

	double eulerResult = mathlib::ODESolver::EulerMethod(1.0, 0.0, 1, 0.1, f);
	double RK2Result = mathlib::ODESolver::RK2Method(1.0, 0.0, 1, 0.1, f);
	double rk4Result = mathlib::ODESolver::RK4Method(1.0, 0.0, 1, 0.1, f);

	double eulerResult2 = mathlib::ODESolver::EulerMethod(1.0, 0.0, 1, 0.5, f);
	double RK2Result2 = mathlib::ODESolver::RK2Method(1.0, 0.0, 1, 0.5, f);
	double rk4Result2 = mathlib::ODESolver::RK4Method(1.0, 0.0, 1, 0.5, f);

	double eulerResult3 = mathlib::ODESolver::EulerMethod(1.0, 0.0, 1, 0.25, f);
	double RK2Result3 = mathlib::ODESolver::RK2Method(1.0, 0.0, 1, 0.25, f);
	double rk4Result3 = mathlib::ODESolver::RK4Method(1.0, 0.0, 1, 0.25, f);

	double eulerResult4 = mathlib::ODESolver::EulerMethod(1.0, 0.0, 1, 0.01, f);
	double RK2Result4 = mathlib::ODESolver::RK2Method(1.0, 0.0, 1, 0.01, f);
	double rk4Result4 = mathlib::ODESolver::RK4Method(1.0, 0.0, 1, 0.01, f);

	std::cout
		<< "Running EulerMethod Test: " << "\n"
		<< "-----\n"
		<< "\tOutput: " << eulerResult << ", " << eulerResult2 << ", " << eulerResult3 << ", " << eulerResult4 << "\n\n\n"
		<< "Running RK2Method Test: " << "\n"
		<< "-----\n"
		<< "\tOutput: " << RK2Result << ", " << RK2Result2 << ", " << RK2Result3 << ", " << RK2Result4 << "\n\n\n"
		<< "Running Runge-Kutta4Method Test: " << "\n"
		<< "-----\n"
		<< "\tOutput: " << rk4Result << ", " << rk4Result2 << ", " << rk4Result3 << ", " << rk4Result4 << "\n\n\n";

}