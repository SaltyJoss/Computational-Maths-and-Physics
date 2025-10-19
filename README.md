# PxM

## Documentation

## Overview

## Latest Update

### Updates- 2025-10-19: Added 2D and 3D Vectors, with tests: *ALL <ins>PASSED</ins>*

#### *3-Dimensional Vector Header*

```C++
#pragma once
#include <cmath>
#include <iostream>

namespace mathlib {
	template<typename T>
	struct Vec3 {
		T x, y, z;

        constexpr Vec3() : x(0), y(0), z(0) {}
        constexpr Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

        inline Vec3 operator+(const Vec3& v) const { return { x + v.x, y + v.y, z + v.z }; }  // Addition operator
        inline Vec3 operator-(const Vec3& v) const { return { x - v.x, y - v.y, z - v.z }; }  // Subtraction operator
        inline Vec3 operator*(double s) const { return { x * s, y * s, z * s }; }              // Multiply operator

        inline double dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; } // dot product
        inline Vec3 cross(const Vec3& v) const {
            return { y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x };         // cross product
        }

        inline double magnitude() const { return std::sqrt(x * x + y * y + z * z); } // calculate magnitude
        inline Vec3 normalised() const { double n = magnitude(); return n > 0 ? (*this) * (1.0 / n) : Vec3(); }   // normalise vector using magnitude

        friend std::ostream& operator<<(std::ostream& os, const Vec3& v) {
            return os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
        }
	};

    using Vec3d = Vec3<double>;
    using Vec3f = Vec3<float>;
    using Vec3i = Vec3<int>;
}
}
```

#### *ODE TESTS*

```shell
[----------] 3 tests from ODETest
[ RUN      ] ODETest.euler_step
[       OK ] ODETest.euler_step (0 ms)
[ RUN      ] ODETest.rk2_step
[       OK ] ODETest.rk2_step (0 ms)
[ RUN      ] ODETest.rk4_step
[       OK ] ODETest.rk4_step (0 ms)
[----------] 3 tests from ODETest (1 ms total)
```

#### *Vec2d TESTS*

```shell
[----------] 7 tests from test_Vec2d
[ RUN      ] test_Vec2d.DefaultConstructor
[       OK ] test_Vec2d.DefaultConstructor (0 ms)
[ RUN      ] test_Vec2d.ParamConstructor
[       OK ] test_Vec2d.ParamConstructor (0 ms)
[ RUN      ] test_Vec2d.AdditionTest
[       OK ] test_Vec2d.AdditionTest (0 ms)
[ RUN      ] test_Vec2d.SubtractionTest
[       OK ] test_Vec2d.SubtractionTest (0 ms)
[ RUN      ] test_Vec2d.ScalarMultiplicationTest
[       OK ] test_Vec2d.ScalarMultiplicationTest (0 ms)
[ RUN      ] test_Vec2d.DotProductTest
[       OK ] test_Vec2d.DotProductTest (0 ms)
[ RUN      ] test_Vec2d.NormalisetTest
[       OK ] test_Vec2d.NormalisetTest (0 ms)
[----------] 7 tests from test_Vec2d (2 ms total)
```

#### *Vec3d TESTS*

```shell
[----------] 8 tests from test_Vec3d
[ RUN      ] test_Vec3d.DefaultConstructor
[       OK ] test_Vec3d.DefaultConstructor (0 ms)
[ RUN      ] test_Vec3d.ParamConstructor
[       OK ] test_Vec3d.ParamConstructor (0 ms)
[ RUN      ] test_Vec3d.AdditionTest
[       OK ] test_Vec3d.AdditionTest (0 ms)
[ RUN      ] test_Vec3d.SubtractionTest
[       OK ] test_Vec3d.SubtractionTest (0 ms)
[ RUN      ] test_Vec3d.ScalarMultiplicationTest
[       OK ] test_Vec3d.ScalarMultiplicationTest (0 ms)
[ RUN      ] test_Vec3d.DotProductTest
[       OK ] test_Vec3d.DotProductTest (0 ms)
[ RUN      ] test_Vec3d.CrossProductTest
[       OK ] test_Vec3d.CrossProductTest (0 ms)
[ RUN      ] test_Vec3d.NormalisetTest
[       OK ] test_Vec3d.NormalisetTest (0 ms)
[----------] 8 tests from test_Vec3d (2 ms total)
```

#### *Full test OUTPUT*

```shell
[----------] Global test environment tear-down
[==========] 18 tests from 3 test suites ran. (6 ms total)
[  PASSED  ] 18 tests.
```