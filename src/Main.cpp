#include "mathlib/Integration/Integrate_ODE.hpp"

#include <iostream>
#include <functional>

int test(std::function<double(double, double)> f);

// Main function to run tests
int main() {
    auto f = [](double t, const double y) -> double {
		return -y; 
	};

	auto result = integrate_ODE();
	return 0;
}