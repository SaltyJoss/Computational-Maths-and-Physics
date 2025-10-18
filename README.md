# PxM

## Documentation

## Overview

## Latest Update

### Updates- 2025-10-17: Testing logic changed: ALL *<ins> PASSED</ins>*

#### *Main test for physics & mathematics constants*

```C++
#include "mathlib/Integration/Integrate_ODE.hpp"
#include "mathlib/ODE/ExplicitSolvers.hpp"
#include "mathlib/Constants/cmath.hpp"
#include "physlib/Constants/cphys.hpp"
#include <iostream>
#include <iomanip> 
#include <vector>
#include <functional>
using namespace physlib::cphys;
using namespace mathlib::cmath;

// Main function to run tests
int main() {
    std::cout << std::fixed << std::setprecision(20);   // Set output to fixed-point, 20dp

    // Test math constants
    std::cout 
        << "Math constants:\n"
        << "pi        = " << pi << "\n"
        << "two_pi    = " << two_pi << "\n"
        << "pi/2      = " << pi_over_2 << "\n"
        << "pi/4      = " << pi_over_4 << "\n"
        << "1/pi      = " << inv_pi << "\n"
        << "2/pi      = " << two_over_pi << "\n"
        << "e         = " << e << "\n"
        << "phi       = " << phi << "\n"
        << "sqrt2     = " << sqrt2 << "\n"
        << "inv_sqrt2 = " << inv_sqrt2 << "\n";

    // Test physics constants
    std::cout 
        << "\nPhysics constants:\n"
        << "G         = " << G << " m^3/kg/s^2\n"
        << "mu_Earth  = " << mu_Earth << " m^3/s^2\n"
        << "g_Earth   = " << g_Earth << " m/s^2\n"
        << "g_Moon    = " << g_Moon << " m/s^2\n"
        << "g_Mars    = " << g_Mars << " m/s^2\n"
        << "c         = " << c << " m/s\n"
        << "microgravity_threshold    = " << microgravity_threshold << " m/s^2\n"
        << "air_density               = " << air_density << " kg/m^3\n"
        << "vacuum_density            = " << vacuum_density << "\n";

    // Derived tests
    double circumference = 2 * pi * 1.0; // radius = 1
    double weight_on_earth = 75.0 * g_Earth; // 75kg object
    double microgravity_limit = g_Earth * microgravity_threshold;

    std::cout 
        << "\nDerived tests with constants:\n"
        << "\nCircumference of unit circle = " << circumference << "\n"
        << "Weight of 75kg object on Earth = " << weight_on_earth << " N\n"
        << "Microgravity threshold (earth) = " << microgravity_limit << " m/s^2\n";

	return 0;
}
```

#### *Mathematical constants output*

```shell
Math constants:
e         = 2.71828182845904509080
pi        = 3.14159265358979311600
two_pi    = 6.28318530717958623200
pi/2      = 1.57079632679489655800
pi/4      = 0.78539816339744827900
1/pi      = 0.31830988618379069122
2/pi      = 0.63661977236758138243
phi       = 1.61803398874989490253
sqrt2     = 1.41421356237309514547
inv_sqrt2 = 0.70710678118654757274
```

#### *Physics constants output*

```shell
Physics constants:
G         = 0.00000000006674300000 m^3/kg/s^2
mu_Earth  = 398600441800000.00000000000000000000 m^3/s^2
g_Earth   = 9.80664999999999942304 m/s^2
g_Moon    = 1.62200129999999997921 m/s^2
g_Mars    = 3.72075999999999984524 m/s^2
c         = 299792458.00000000000000000000 m/s
microgravity_threshold    = 0.00000100000000000000 m/s^2
air_density               = 1.22500000000000008882 kg/m^3
vacuum_density            = 0.00000000000000000000
```

#### *Derived Tests output*

```shell
Derived tests with constants:
Circumference of unit circle = 6.28318530717958623200
Weight of 75kg object on Earth = 735.49874999999997271516 N
Microgravity threshold (earth) = 0.00000980665000000000 m/s^2
```