#pragma once
#include <functional>

namespace mathlib
{
	namespace ODESolver {
		double EulerMethod(double y0, double t0, int N, double h, std::function<double(double, double)> f);
		double RK2Method(double y0, double t0, int N, double h, std::function<double(double, double)> f);
		double RK4Method(double y0, double t0, int N, double h, std::function<double(double, double)> f);
	}
}