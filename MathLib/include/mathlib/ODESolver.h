#pragma once
#include <functional>

namespace NumericalMethods
{
	namespace ODESolver {
		double EulerMethod(double y0, double t0, int N, double h, std::function<double(double, double)> f);
		double MidpointMethod(double y0, double t0, int N, double h, std::function<double(double, double)> f);
		double RungeKutta4Method(double y0, double t0, int N, double h, std::function<double(double, double)> f);
	}
}