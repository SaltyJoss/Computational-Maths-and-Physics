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
	double h = 0.1;		  // Step size

	int N = static_cast<int>((t_final - t0) / h); // Number of steps

	std::function<double(double, double)> f = [](double t, double y) { return t + y; }; // Differential equation
};

/*
// Test Euler method
TEST_F(ODETest, EulerMethod) {
	double y = mathlib::ODE::EulerMethod(y0, t0, N, h, f);
	double exact = (2 * std::exp(t_final)) - t_final - 1;
	EXPECT_NEAR(y, exact, 0.3) << "EulerMethod failed: Approx=" << y << ", Exact=" << exact << "\n";
}

// Test RK2 method
TEST_F(ODETest, RK2Method) {
	double y = mathlib::ODE::RK2Method(y0, t0, N, h, f);
	double exact = (2 * std::exp(t_final)) - t_final - 1;
	EXPECT_NEAR(y, exact, 1e-2) << "RK2Method failed: Approx=" << y << ", Exact=" << exact << "\n";
}

// Test RK4 method
TEST_F(ODETest, RK4Method) {
	double y = mathlib::ODE::RK4Method(y0, t0, N, h, f);
	double exact = (2 * std::exp(t_final)) - t_final - 1;
	EXPECT_NEAR(y, exact, 1e-5) << "RK4Method failed: Approx=" << y << ", Exact=" << exact << "\n";
}
*/