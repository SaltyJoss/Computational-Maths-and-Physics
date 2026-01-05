#ifndef MATHLIB_MATRIX2X2_HPP
#define MATHLIB_MATRIX2X2_HPP


#include "Vec2d.hpp"
#include <iostream>

namespace mathlib {
	template<typename T>
	struct Mat2x2 {
		Vec2<T> rows[2];

		// Default Constructor
		constexpr Mat2x2() : rows{ Vec2<T>(0.0, 0.0), Vec2<T>(0.0, 0.0) } {}
		
		// Constructor from Vec2<T> rows
		constexpr Mat2x2(const Vec2<T>& r0, const Vec2<T>& r1) : rows{ r0, r1 } {}
		
		// Constructor from 4 scalars
		constexpr Mat2x2(T a00, T a01, T a10, T a11)
			: rows{ Vec2<T>(a00, a01), Vec2<T>(a10, a11) } {}

		// Copy Constructor
		constexpr Mat2x2(const Mat2x2<T>& other) : rows{ other.rows[0], other.rows[1] } {}

		// Access Operators
		inline Vec2<T>& operator[](int i) { return rows[i]; }
		inline const Vec2<T>& operator[](int i) const { return rows[i]; }


		// ---< MATRIX ADDITIONS >---

		// Matrix-Scalar Addition
		inline Mat2x2<T> operator+(const T& s) const {
			Mat2x2<T> r;
			for (int i = 0; i < 2; ++i) {
				r[i].x = rows[i].x + s;
				r[i].y = rows[i].y + s;
			}
			return r;
		}

		// Matrix-Vector Addition
		inline Mat2x2<T> operator+(const Vec2<T>& v) const {
			Mat2x2<T> r;
			for (int i = 0; i < 2; ++i) {
				r[i] = rows[i] + v;
			}
			return r;
		}

		// Matrix-Matrix Addition
		inline Mat2x2<T> operator+(const Mat2x2<T>& m) const {
			Mat2x2<T> r;
			for (int i = 0; i < 2; ++i) {
				r[i] = rows[i] + m[i];
			}
			return r;
		}


		// ---< MATRIX SUBTRACTIONS >---

		// Matrix-Scalar Subtraction
		inline Mat2x2<T> operator-(const T& s) const {
			Mat2x2<T> r;
			for (int i = 0; i < 2; ++i) {
				r[i].x = rows[i].x - s;
				r[i].y = rows[i].y - s;
			}
			return r;
		}

		// Matrix-Vector Subtraction
		inline Mat2x2<T> operator-(const Vec2<T>& v) const {
			Mat2x2<T> r;
			for (int i = 0; i < 2; ++i) {
				r[i] = rows[i] - v;
			}
			return r;
		}

		// Matrix-Matrix Subtraction
		inline Mat2x2<T> operator-(const Mat2x2<T>& m) const {
			Mat2x2<T> r;
			for (int i = 0; i < 2; ++i) {
				r[i] = rows[i] - m[i];
			}
			return r;
		}


		// ---< MATRIX MULTIPLICATIONS >---

		// Matrix-Scalar Multiplication
		inline Mat2x2<T> operator*(const T& s) const {
			Mat2x2<T> r;
			for (int i = 0; i < 2; ++i) {
				r[i].x = rows[i].x * s;
				r[i].y = rows[i].y * s;
			}
			return r;
		}

		// Matrix-Vector multiplication
		inline Vec2<T> operator*(const Vec2<T>& v) const {
			return Vec2<T>(rows[0].dot(v), rows[1].dot(v));
		}

		// Matrix-Matrix multiplication
		inline Mat2x2<T> operator*(const Mat2x2<T>& m) const {
			Mat2x2<T> r;
			for (int i = 0; i < 2; ++i) {
				r[i].x = rows[i].x * m[0].x + rows[i].y * m[1].x;
				r[i].y = rows[i].x * m[0].y + rows[i].y * m[1].y;
			}
			return r;
		}
	};

	template<typename T>
	inline std::ostream& operator<<(std::ostream& os, const Mat2x2<T>& m) {
		for (int i = 0; i < 2; i++) os << m[i] << "\n";
		return os;
	}

	using Mat2x2d = Mat2x2<double>;
	using Mat2x2f = Mat2x2<float>;
	using Mat2x2i = Mat2x2<int>;
}

#endif // MAT2X2_H