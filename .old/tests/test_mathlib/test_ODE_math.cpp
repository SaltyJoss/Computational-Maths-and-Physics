#include "mathlib/Integration/Integrate_ODE.hpp"
#include "mathlib/ODE/ExplicitSolvers.hpp"

#include <gtest/gtest.h>
#include <iostream>
#include <cmath>
#include <functional>

// Setup test fixture
class ODETest : public ::testing::Test {
protected:
	double y0 = 1.0;	  // Initial condition
	double t0 = 0.0;	  // Initial time
	double t_final = 1.0; // Final time
	double dt = 0.01;	  // Step size

	double approx = 0.0;

	int N = static_cast<int>((t_final - t0) / dt); // Number of steps

	std::function<double(double, double)> f = [](double t, const double y) -> double { return -y; };
};


// Test Euler method
TEST_F(ODETest, euler_step) {
	auto euler_lambda = [](const std::function<double(double, const double&)>& f, double t, const double& y, double dt) -> double {
		return mathlib::ODE::euler_step<double>(y, t, dt, f);
		};

	std::vector<double> trajectory = mathlib::Integration::integrate_ODE<double>(
		f, y0, t0, t_final, dt, euler_lambda
	);

	double t = t0;
	for (auto y : trajectory) {
		t += dt;
		approx = y;
	}

	double exact = std::exp(-t_final);
	EXPECT_NEAR(approx, exact, 0.01) << "Euler Method failed: Approx=" << approx << ", Exact=" << exact << "\n";
}

// Test RK2 method
TEST_F(ODETest, rk2_step) {
	auto rk2_lambda = [](const std::function<double(double, const double&)>& f, double t, const double& y, double dt) -> double {
		return mathlib::ODE::rk2_step<double>(y, t, dt, f);
		};

	std::vector<double> trajectory = mathlib::Integration::integrate_ODE<double>(
		f, y0, t0, t_final, dt, rk2_lambda
	);

	double t = t0;
	for (auto y : trajectory) {
		t += dt;
		approx = y;
	}

	double exact = std::exp(-t_final);
	EXPECT_NEAR(approx, exact, 1e-4) << "RK2 Method failed: Approx = " << approx << ", Exact = " << exact << "\n";
}

// Test RK4 method
TEST_F(ODETest, rk4_step) {
	auto rk4_lambda = [](const std::function<double(double, const double&)>& f, double t, const double& y, double dt) -> double {
		return mathlib::ODE::rk4_step<double>(y, t, dt, f);
		};

	std::vector<double> trajectory = mathlib::Integration::integrate_ODE<double>(
		f, y0, t0, t_final, dt, rk4_lambda
	);

	double t = t0;
	for (auto y : trajectory) {
		t += dt;
		approx = y;
	}

	double exact = std::exp(-t_final);
	EXPECT_NEAR(approx, exact, 1e-8) << "RK4 Method failed: Approx=" << approx << ", Exact=" << exact << "\n";
}