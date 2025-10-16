#include "mathlib/ODE/ExplicitSolvers.hpp"

#include <gtest/gtest.h>
#include <iostream>
#include <cmath>
#include <functional>

// Setup test fixture
class ExplicitSolversTest : public ::testing::Test {
protected:
	double y0, t0, t_final, h;
	int N;
	std::function<double(double, double)> f;

	void SetUp() override {
		double y0 = 1.0;
		double t0 = 0.0;
		double t_final = 1.0;
		double h = 0.2;
		int N = static_cast<int>((t_final - t0) / h);
		std::function<double(double, double)> f = [](double t, double y) { return y; };
	}
};

// Test Euler method
TEST_F(ExplicitSolversTest, EulerMethod) {
	double y = mathlib::ODE::EulerMethod(y0, t0, N, h, f);
	double exact = std::exp(t_final);
	EXPECT_NEAR(y, exact, 0.1) << "EulerMethod failed: Approx=" << y << ", Exact=" << exact;
}

// Test RK2 method
TEST_F(ExplicitSolversTest, RK2Method) {
	double y = mathlib::ODE::RK2Method(y0, t0, N, h, f);
	double exact = std::exp(t_final);
	EXPECT_NEAR(y, exact, 1e-2) << "RK2Method failed: Approx=" << y << ", Exact=" << exact;
}

// Test RK4 method
TEST_F(ExplicitSolversTest, RK4Method) {
	double y = mathlib::ODE::RK4Method(y0, t0, N, h, f);
	double exact = std::exp(t_final);
	EXPECT_NEAR(y, exact, 1e-5) << "RK4Method failed: Approx=" << y << ", Exact=" << exact;
}