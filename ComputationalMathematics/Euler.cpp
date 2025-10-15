#include "ODESolver.h"

// Simple Euler method implementation
double NumericalMethods::ODESolver::EulerMethod(double y0, double x0, int steps, double h, std::function<double(double, double)> f) {
	double y = y0;
	double x = x0;
	for (int i = 0; i < steps; ++i) 
	{
		y += h * f(x, y);
		x += h;
	}
	return y;
}