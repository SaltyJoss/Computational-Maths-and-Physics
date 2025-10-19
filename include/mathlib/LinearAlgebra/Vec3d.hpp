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