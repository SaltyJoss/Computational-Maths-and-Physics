# PxM

## Documentation

## Overview

## Latest Update

### Updates- 2025-10-17: Testing logic changed *<ins>ALL FAILED</ins>*

#### *Revised Testing Logic*

```C++
TEST_F(ODETest, example_step) {
	auto exampple_lambda = [](const std::function<double(double, const double&)>& f, double t, const double& y, double dt) -> double {
		return mathlib::ODE::example_step<double>(y, t, dt, f);
		};

	std::vector<double> trajectory = mathlib::Integration::integrate_ODE<double>(
		f, y0, t0, t_final, dt, euler_lambda
	);

	double t = t0;
	for (auto y : trajectory) {
		t += dt;
		approx = y;
	}

	double exact = (2 * std::exp(t_final)) - t_final - 1;
	EXPECT_NEAR(approx, exact, 0.3) << "EulerMethodExample failed: Approx=" << approx << ", Exact=" << exact << "\n";
}
```

#### *Euler Test*

```shell
error: The difference between approx and exact is 3.12275306082809, which exceeds 0.3, where
approx evaluates to 0.31381059609,
exact evaluates to 3.4365636569180902, and
0.3 evaluates to 0.29999999999999999.
Euler Method failed: Approx=0.31381059609, Exact=3.4365636569180902


[  FAILED  ] ODETest.euler_step (0 ms)
```

#### *RK2 Test*

```shell
error: The difference between approx and exact is 3.1030340656437256, which exceeds 1e-2, where
approx evaluates to 0.33352959127436443,
exact evaluates to 3.4365636569180902, and
1e-2 evaluates to 0.01.
RK2 Method failed: Approx = 0.33352959127436443, Exact = 3.4365636569180902


[  FAILED  ] ODETest.rk2_step (0 ms)
```

#### *RK4 Test*

```shell
error: The difference between approx and exact is 3.1036922415381212, which exceeds 1e-5, where
approx evaluates to 0.33287141537996906,
exact evaluates to 3.4365636569180902, and
1e-5 evaluates to 1.0000000000000001e-05.
RK4 Method failed: Approx=0.33287141537996906, Exact=3.4365636569180902


[  FAILED  ] ODETest.rk4_step (0 ms)
```

#### *Output of the tests*:

```shell
[----------] 3 tests from ODETest (1 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 1 test suite ran. (2 ms total)
[  PASSED  ] 0 tests.
[  FAILED  ] 3 tests, listed below:
[  FAILED  ] ODETest.euler_step
[  FAILED  ] ODETest.rk2_step
[  FAILED  ] ODETest.rk4_step
```