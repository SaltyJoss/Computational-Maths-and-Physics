#include "ODESolver.h"
#include <iostream>

namespace NumericalMethods {
	namespace ODESolver {

		// Simple Euler method implementation
		double EulerMethod(double y0, double t0, int steps, double h, std::function<double(double, double)> f) {
			double y = y0;
			double t = t0;
			for (double i = 0; i < steps; i += h) {
				y += h * f(t, y);
				t += h;

				std::cout << "t: " << t << " , y: " << y << " , i: " << i << "\n";
			}
			std::cout << "\n";
			return y;
		}

		// Simple Finite Difference method implementation
		double FiniteDifferenceMethod(double y0, double t0, int steps, double h, std::function<double(double, double)> f) {
			double y = y0;
			double t = t0;
			for (double i = 0; i < steps; i += h) {
				// Central difference approximation
				double y_next = y + h * f(t + h / 2.0, y + (h / 2.0) * f(t, y));
				y = y_next;
				t += h;

				std::cout << "t: " << t << " , y: " << y << " , i: " << i << "\n";
			}
			std::cout << "\n";
			return y;
		}

		// Simple Runge-Kutta 4th order method implementation
		double RungeKutta4Method(double y0, double t0, int steps, double h, std::function<double(double, double)> f) {
			double y = y0;
			double t = t0;
			for (double i = 0; i < steps; i += h) {
				double k1 = h * f(t, y);
				double k2 = h * f(t + h / 2.0, y + k1 / 2.0);
				double k3 = h * f(t + h / 2.0, y + k2 / 2.0);
				double k4 = h * f(t + h, y + k3);
				y += (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
				t += h;

				std::cout << "t: " << t << " , y: " << y << " , i: " << i << "\n";
			}
			std::cout << "\n";
			return y;
		}
	}
}

