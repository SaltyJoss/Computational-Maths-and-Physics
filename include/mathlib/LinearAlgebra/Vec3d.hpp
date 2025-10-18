#pragma once
#include <cmath>
#include <iostream>

namespace mathlib {
	template<typename T>
	struct Vec3d {
		T x, y;

        double x, y, z;

        constexpr Vec3d() : x(0), y(0), z(0) {}
        constexpr Vec3d(double x, double y, double z) : x(x), y(y), z(z) {}

        inline Vec3d operator+(const Vec3d& v) const { return { x + v.x, y + v.y, z + v.z }; }  // Addition operator
        inline Vec3d operator-(const Vec3d& v) const { return { x - v.x, y - v.y, z - v.z }; }  // Subtraction operator
        inline Vec3d operator*(double s) const { return { x * s, y * s, z * s }; }              // Multiply operator

        inline double dot(const Vec3d& v) const { return x * v.x + y * v.y + z * v.z; } // dot product
        inline Vec3d cross(const Vec3d& v) const {
            return { y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x };         // cross product
        }

        inline double magnitude() const { return std::sqrt(x * x + y * y + z * z); } // calculate magnitude
        inline Vec3d normalized() const { double n = magnitude(); return n > 0 ? (*this) * (1.0 / n) : Vec3d(); }   // normalise vector using magnitude

        friend std::ostream& operator<<(std::ostream& os, const Vec3d& v) {
            return os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
        }
	};
}