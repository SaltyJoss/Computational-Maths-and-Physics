#include <iostream>
#include <functional>

int test(std::function<double(double, double)> f);

// Main function to run tests
int main() {
    auto f = [](double t, double y) { return t + y; };

	return 0;
}