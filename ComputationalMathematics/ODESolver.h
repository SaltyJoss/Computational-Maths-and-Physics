#pragma once
#include <functional>

namespace NumericalMethods 
{
	namespace ODESolver 
	{
		double EulerMethod(double y0, double x0, int steps, double h, std::function<double(double, double)> f);
		double RungeKutta4Method(double y0, double x0, int steps, double h, std::function<double(double, double)> f);
		double FiniteDifferenceMethod(double y0, double x0, int steps, double h, std::function<double(double, double)> f);
	}
}