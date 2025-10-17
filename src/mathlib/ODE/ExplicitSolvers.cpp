#include <iostream>
#include <functional>

/*namespace mathlib {
	namespace ODE {

		template<typename T>

		// Simple Euler method implementation
		T EulerMethod(double y0, double t0, int N, double h, std::function<double(double, double)> f) {
			double y = y0;
			double t = t0;
			for (int i = 0; i < N; i++) {
				y += h * f(t, y);
				t += h;

				//std::cout << "t: " << t << " , y: " << y << " , i: " << i << "\n";
			}
			//std::cout << "\n";
			return y;
		}

		// Simple Runge-Kutta 2nd order / Midpoint method implementation
		T RK2Method(double y0, double t0, int N, double h, std::function<double(double, double)> f) {
			double y = y0;
			double t = t0;
			for (int i = 0; i < N; i++) {
				double y_next = y + h * f(t + h / 2, y + (h / 2) * f(t, y));
				y = y_next;
				t += h;

				//std::cout << "t: " << t << " , y: " << y << " , i: " << i << "\n";
			}
			//std::cout << "\n";
			return y;
		}

		// Simple Runge-Kutta 4th order method implementation
		T RK4Method(double y0, double t0, int N, double h, std::function<double(double, double)> f) {
			double y = y0;
			double t = t0;
			for (int i = 0; i < N; i++) {
				double k1 = h * f(t, y);
				double k2 = h * f(t + h / 2.0, y + k1 / 2.0);
				double k3 = h * f(t + h / 2.0, y + k2 / 2.0);
				double k4 = h * f(t + h, y + k3);
				y += (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
				t += h;

				//std::cout << "t: " << t << " , y: " << y << " , i: " << i << "\n";
			}
			//std::cout << "\n";
			return y;
		}
	}
}*/

