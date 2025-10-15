#pragma once

namespace NumericalMethodsTests
{
	namespace ODESolverTests
	{
		double EulerMethodTest(std::function<double(double, double)> f);
		double RungeKutta4MethodTest(std::function<double(double, double)> f);
		double FiniteDifferenceMethodTest(std::function<double(double, double)> f);
	}
}