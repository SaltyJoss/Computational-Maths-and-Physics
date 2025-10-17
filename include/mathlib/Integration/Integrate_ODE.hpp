#pragma once
#include <vector>
#include <functional>

namespace mathlib::Integration {
	template<typename T>
	std::vector<T> integrate_ODE(
		const std::function<T(double, const T&)>& f,
		T y0, double t0, double t_final, double dt,
		const std::function<T(const std::function < T(double, const T&)>&, double, const T&, double)>& step_function
	) {
		// Applies logic from cpp file (see git commit changes)
		std::vector<T> trajectory;
		T y = y0;
		double t = t0;
		trajectory.push_back(y);

		while (t < t_final) {
			y = step_function(f, t, y, dt);
			t += dt;
			trajectory.push_back(y);
		}

		return trajectory;
	}
}