#pragma once
#include <functional>

namespace mathlib
{
	namespace RootFinding
	{
		double BisectionMethod(double a, double b, double tol, int maxIter, std::function<double(double)> f);
		double NewtonRaphsonMethod(double x0, double tol, int maxIter, std::function<double(double)> f, std::function<double(double)> df);
		double SecantMethod(double x0, double x1, double tol, int maxIter, std::function<double(double)> f);
	}
}