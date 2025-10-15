#include "ODESolver.h"

// Simple Runge-Kutta 4th order method implementation
double NumericalMethods::ODESolver::RungeKutta4Method(double y0, double x0, int steps, double h, std::function<double(double, double)> f) {
	double y = y0;
	double x = x0;
	for (int i = 0; i < steps; ++i) {
		double k1 = h * f(x, y);
		double k2 = h * f(x + h / 2.0, y + k1 / 2.0);
		double k3 = h * f(x + h / 2.0, y + k2 / 2.0);
		double k4 = h * f(x + h, y + k3);
		y += (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
		x += h;
	}
	return y;
}