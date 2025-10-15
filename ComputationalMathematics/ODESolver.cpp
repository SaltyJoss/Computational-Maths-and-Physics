#include "ODESolver.h"
#include <iostream>

namespace NumericalMethods {
	namespace ODESolver {

		// Simple Euler method implementation
		double EulerMethod(double y0, double x0, int steps, double h, std::function<double(double, double)> f) {
			double y = y0;
			double x = x0;
			for (int i = 0; i < steps; ++i)
			{
				y += h * f(x, y);
				x += h;
			}
			return y;
		}

		// Simple Finite Difference method implementation
		double FiniteDifferenceMethod(double y0, double x0, int steps, double h, std::function<double(double, double)> f) {
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

		// Simple Runge-Kutta 4th order method implementation
		double RungeKutta4Method(double y0, double x0, int steps, double h, std::function<double(double, double)> f) {
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
	}
}

