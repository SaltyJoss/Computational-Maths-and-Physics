#pragma once
#include <functional>

namespace mathlib::ODE {
	template<typename T>
	T euler_step(const T& y, double t, double dt, const std::function<T(double, const T&)>& f) { return y + dt * f(t, y); }

	template<typename T>
	T rk2_step(const T& y, double t, double dt, const std::function<T(double, const T&)>& f) { return y + dt * f(t + dt / 2.0, y + (dt / 2.0) * f(t, y)); }

	template<typename T>
	T rk4_step(const T& y, double t, double dt, const std::function<T(double, const T&)>& f) {
		T k1 = dt * f(t, y);
		T k2 = dt * f(t + dt / 2.0, y + k1 / 2.0);
		T k3 = dt * f(t + dt / 2.0, y + k2 / 2.0);
		T k4 = dt * f(t + dt, y + k3);
		return y + (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
	}
}