#pragma once
#include <cmath>
#include <iostream>

namespace mathlib {
	template<typename T>
	struct Vec2 {
		T x, y;

		constexpr Vec2() : x(0), y(0) {}
		constexpr Vec2(T x, T y) : x(x), y(y) {}

		inline Vec2 operator+(const Vec2& v) const { return {x + v.x, y + v.y}; }	// Addition operator
		inline Vec2 operator-(const Vec2& v) const { return {x - v.x, y - v.y}; }	// Subtraction operator
		inline Vec2 operator*(double s) const { return {x * s, y * s}; }			// Multiply operator

		inline double dot(const Vec2& v) const { return {x*v.x + y*v.y}; }	// dot product

		inline double magnitude() const { return std::sqrt(x*x + y*y); } // magnitude
		inline Vec2 normalised() const { double n = magnitude(); return n > 0 ? (*this) * (1.0 / n) : Vec2(); }	// normalise

		friend std::ostream& operator<<(std::ostream& os, const Vec2& v) {
			return os << "[" << v.x << ", " << v.y << "]";
		}
	};

	using Vec2d = Vec2<double>;
	using Vec2f = Vec2<float>;
	using Vec2i = Vec2<int>;
}