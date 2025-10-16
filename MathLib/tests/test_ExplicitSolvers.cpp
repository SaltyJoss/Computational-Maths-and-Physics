#include "mathlib/ODE/ExplicitSolvers.hpp"

#include <gtest/gtest.h>
#include <iostream>
#include <cmath>
#include <functional>

// Function prototypes
void testEulerMethod(std::function<double(double, double)> f);
void testRK2Method(std::function<double(double, double)> f);
void testRK4Method(std::function<double(double, double)> f);


int test(std::function<double(double, double)> f) {
	std::cout << "Testing ODESolver...\n" << std::endl;

	testEulerMethod(f);
	testRK2Method(f);
	testRK4Method(f);

	return 0;
}

void testEulerMethod(std::function<double(double, double)> f) {
	double y = mathlib::ODE::EulerMethod(1, 0, 1, 0.2, f);
	std::cout << "Testing Euler Method:\n---\n" << "\tApprox: " << y
		<< ", Exact: " << std::exp(1.0)
		<< ", Error: " << std::abs(y - std::exp(1.0)) << "\n\n";
}

void testRK2Method(std::function<double(double, double)> f) {
	double y = mathlib::ODE::RK2Method(1, 0, 1, 0.2, f);
	std::cout << "Testing RK2 Method:\n---\n" << "\tApprox: " << y 
		<< ", Exact: " << std::exp(1.0)
		<< ", Error: " << std::abs(y - std::exp(1.0)) << "\n\n";
}

void testRK4Method(std::function<double(double, double)> f) {
	double y = mathlib::ODE::RK4Method(1, 0, 1, 0.2, f);
	std::cout << "Testing RK4 Method:\n---\n" << "\tApprox: " << y 
		<< ", Exact: " << std::exp(1.0)
		<< ", Error: " << std::abs(y - std::exp(1.0)) << "\n\n";
}