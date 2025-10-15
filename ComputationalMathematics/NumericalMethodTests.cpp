#include "ODETests.h"
#include "NumericalMethods.h"
#include <iostream>

// Test namespaces
namespace NumericalMethodTests {

	// Test implementations
	double EulerMethodTest(std::function<double(double, double)> f)
	{
		return NumericalMethods::ODESolver::EulerMethod(1.0, 0.0, 10, 0.1, f);
	}

	double RungeKutta4MethodTest(std::function<double(double, double)> f)
	{
		return NumericalMethods::ODESolver::RungeKutta4Method(1.0, 0.0, 10, 0.1, f);
	}

	double FiniteDifferenceMethodTest(std::function<double(double, double)> f)
	{
		return NumericalMethods::ODESolver::FiniteDifferenceMethod(1.0, 0.0, 10, 0.1, f);
	}

	void ODETests() {
		auto f = [](double x, double y) { return x + y; };

		// Example test for Euler Method
		std::cout << "\n" << "Running EulerMethod Test: " << EulerMethodTest(f) << "\n";

		// Example test for Runge-Kutta 4 Method
		std::cout << "Running Runge-Kutta4Method Test: " << RungeKutta4MethodTest(f) << "\n";

		// Example test for Finite Difference Method
		std::cout << "Running FiniteDifferenceMethod Test: " << FiniteDifferenceMethodTest(f) << "\n";
	}
}