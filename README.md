# PxM

## Documentation

## Overview

## Latest Update

### Updates- 2025-10-17: Renaming project to PxM (Physics x Mathematics) to match libraries purpose.

#### *Tests with* <ins>ERRORS</ins> *for explicit ODE solvers, using C++ and GoogleTest*.
```C++
// Test methods general format
TEST_F(ExplicitSolversTest, methodName) {
	double y = mathlib::ODE::methodName(y0, t0, N, h, f);
	double exact = std::exp(t_final);						// <-- Error here: wrong exact solution
	EXPECT_NEAR(y, exact, 0.3) << "Method failed: Approx=" << y << ", Exact=" << exact << "\n";
}
```

#### *First*  <ins>SUCCESSFULL</ins> *set of tests results for explicit ODE solvers, using C++ and GoogleTest*.

```C++
// Test methods general format
TEST_F(ExplicitSolversTest, methodName) {
	double y = mathlib::ODE::methodName(y0, t0, N, h, f);
	double exact = (2 * std::exp(t_final)) - t_final - 1;	// <-- Correct exact solution, no error
	EXPECT_NEAR(y, exact, 0.3) << "Method failed: Approx=" << y << ", Exact=" << exact << "\n";
}
```
#### *Output of the tests*:

```shell
[----------] Global test environment set-up.
[----------] 3 tests from ExplicitSolversTest
[ RUN      ] ExplicitSolversTest.EulerMethod
[       OK ] ExplicitSolversTest.EulerMethod (0 ms)
[ RUN      ] ExplicitSolversTest.RK2Method
[       OK ] ExplicitSolversTest.RK2Method (0 ms)
[ RUN      ] ExplicitSolversTest.RK4Method
[       OK ] ExplicitSolversTest.RK4Method (0 ms)
[----------] 3 tests from ExplicitSolversTest (0 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 1 test suite ran. (1 ms total)
[  PASSED  ] 3 tests.
```