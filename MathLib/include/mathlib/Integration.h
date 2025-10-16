#pragma once
#include <functional>

namespace mathlib
{
	namespace Integration
	{
		double TrapezoidalRule(double a, double b, int n, std::function<double(double)> f);
		double SimpsonRule(double a, double b, int n, std::function<double(double)> f);
		double RombergIntegration(double a, double b, int maxIter, double tol, std::function<double(double)> f);
	}
}
