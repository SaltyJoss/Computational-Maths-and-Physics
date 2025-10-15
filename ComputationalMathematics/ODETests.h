#pragma once
#include <functional>

namespace NumericalMethodTests {

    class ODESolverTests {
    public:
        static double EulerMethodTest(std::function<double(double, double)> f);
        static double RungeKutta4MethodTest(std::function<double(double, double)> f);
        static double FiniteDifferenceMethodTest(std::function<double(double, double)> f);
    };

    void ODETests(); // wrapper function to run all tests
}