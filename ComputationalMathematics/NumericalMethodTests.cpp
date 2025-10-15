#include "NumericalMethods.h"
#include "NumericalMethodTests.h"
#include <iostream>
using namespace NumericalMethodsTests;

// Test namespaces
namespace NumericalMethodTests {
	void ODETests() {
		auto f = [](double x, double y) { return x + y; };
		double result{};

		// Example test for Euler Method
		ODESolverTests::EulerMethodTest(f);
		std::cout
			<< "\n" << "EULER METHOD:" << "--------------------------\n"
			<< "Eulers Method Result: " << result << "\n";

		// Example test for Runge-Kutta 4 Method
		ODESolverTests::RungeKutta4MethodTest(f);
		std::cout
			<< "\n" << "RUNGE-KUTTA 4th-ORDER METHOD:" << "--------------------------\n"
			<< "Runge Kutta 4 Method Result: " << result << "\n";

		// Example test for Finite Difference Method
		ODESolverTests::FiniteDifferenceMethodTest(f);
		std::cout
			<< "\n" << "FINITE DIFFERENCE METHOD:" << "--------------------------\n"
			<< "Finite Difference Method Result: " << result << "\n";
	}
}

// Test implementations
double ODESolverTests::EulerMethodTest(std::function<double(double, double)> f)
{
	double result = NumericalMethods::ODESolver::EulerMethod(1.0, 0.0, 10, 0.1, f);
	return result;
}

double ODESolverTests::RungeKutta4MethodTest(std::function<double(double, double)> f)
{
	double result = NumericalMethods::ODESolver::RungeKutta4Method(1.0, 0.0, 10, 0.1, f);
	return result;
}

double ODESolverTests::FiniteDifferenceMethodTest(std::function<double(double, double)> f)
{
	double result = NumericalMethods::ODESolver::FiniteDifferenceMethod(1.0, 0.0, 10, 0.1, f);
	return result;
}