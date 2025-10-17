# PxM

## Documentation

## Overview

## Latest Update

### Updates- 2025-10-17: Testing logic changed: ALL *<ins> PASSED</ins>*

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
	EXPECT_NEAR(approx, exact, 0.3) << "Example Method failed: Approx=" << approx << ", Exact=" << exact << "\n";
}
```

#### *Euler Test*

```shell
[ RUN      ] ODETest.euler_step
[       OK ] ODETest.euler_step (0 ms)
```

#### *RK2 Test*

```shell
[ RUN      ] ODETest.rk2_step
[       OK ] ODETest.rk2_step (0 ms)
```

#### *RK4 Test*

```shell
[ RUN      ] ODETest.rk4_step
[       OK ] ODETest.rk4_step (0 ms)
```

#### *Output of the tests*:

```shell
[----------] 3 tests from ODETest (1 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 1 test suite ran. (1 ms total)
[  PASSED  ] 3 tests.
```