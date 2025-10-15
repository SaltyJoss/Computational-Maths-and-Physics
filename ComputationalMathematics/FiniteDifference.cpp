#include "ODESolver.h"

double NumericalMethods::ODESolver::FiniteDifferenceMethod(double y0, double x0, int steps, double h, std::function<double(double, double)> f) {
	double y = y0;
	double x = x0;
	for (int i = 0; i < steps; ++i) {
		// Central difference approximation
		double y_next = y + h * f(x + h / 2.0, y + (h / 2.0) * f(x, y));
		y = y_next;
		x += h;
	}
	return y;
}