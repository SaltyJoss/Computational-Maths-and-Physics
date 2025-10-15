#include <iostream>
#include "NumericalMethodTests.cpp"

int Main() {
	std::cout << "Numerical Methods Library Test\n" << "\n";
	NumericalMethodTests::ODESolverTests();

	return 0;
}