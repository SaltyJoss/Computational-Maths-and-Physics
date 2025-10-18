#pragma once
#include <cmath>
#include <iostream>

namespace mathlib {
	template<typename T>
	struct Vec2d {
		T x, y;

		constexpr Vec2d() : x(0), y(0) {}
		constexpr Vec2d(T x, T y) : x(x), y(y) {}

		inline Vec2d operator+(const Vec2d& v) const { return {x + v.x, y + v.y}; }	// Addition operator
		inline Vec2d operator-(const Vec2d& v) const { return {x - v.x, y - v.y}; }	// Subtraction operator
		inline Vec2d operator*(double s) const { return {x * s, y * s}; }			// Multiply operator

		inline double dot(const Vec2d& v) const { return {x*v.x + y*v.y}; }	// dot product

		inline double magnitude() const { return std::sqrt(x*x + y*y); } // magnitude
		inline Vec2d normalised() const { double n = magnitude(); return n > 0 ? (*this) * (1.0 / n) : Vec2d(); }	// normalise

		friend std::ostream& operator<<(std::ostream& os, const Vec2d& v) {
			return os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
		}
	};
}