#ifndef MAT2X2_H
#define MAT2X2_H

#include "Vec2D.hpp"
#include <iostream>

namespace mathlib {
	struct Mat2x2 {
		Vec2d rows[2];

		// Default Constructor
		constexpr Mat2x2() = default;
		// Constructor from Vec2d rows
		constexpr Mat2x2(const Vec2d& r0, const Vec2d& r1) {
			rows[0] = r0;
			rows[1] = r1;
		}
		// Constructor from 9 scalars
		constexpr Mat2x2(double a00, double a01,
			double a10, double a11)
			: rows{ {a00, a01}, {a10, a11} } {
		}

		/*
		// Transpose
		Mat2x2 transpose() const {
			return Mat2x2(
				Vec2d(rows[0].x, rows[1].x, rows[2].x),
				Vec2d(rows[0].y, rows[1].y, rows[2].y);
		}
		*/

		// Access Operators
		inline Vec2d& operator[](int i) { return rows[i]; }
		inline const Vec2d& operator[](int i) const { return rows[i]; }


		// ---< MATRIX ADDITIONS >---

		// Matrix-Scalar Addition
		inline Mat2x2 operator+(const double& s) const {
			Mat2x2 r;
			for (int i = 0; i < 2; ++i) {
				r[i] = rows[i].x + s, rows[i].y + s;
			}
			return r;
		}

		// Matrix-Vector Addition
		inline Mat2x2 operator+(const Vec2d& v) const {
			Mat2x2 r;
			for (int i = 0; i < 2; ++i) {
				r[i] = row[i] + v;
			}
			return r;
		}

		// Matrix-Matrix Addition
		inline Mat2x2 operator+(const Mat2x2& m) const {
			Mat2x2 r;
			for (int i = 0; i < 2; ++i) {
				r[i] = row[i] + m[i];
			}
			return r;
		}


		// ---< MATRIX SUBTRACTIONS >---

		// Matrix-Scalar Subtraction
		inline Mat2x2 operator-(const double& s) const {
			Mat2x2 r;
			for (int i = 0; i < 2; ++i) {
				r[i] = rows[i].x - s, rows[i].y - s;
			}
			return r;
		}

		// Matrix-Vector Subtraction
		inline Mat2x2 operator-(const Vec2d& v) const {
			Mat2x2 r;
			for (int i = 0; i < 2; ++i) {
				r[i] = row[i] + v;
			}
			return r;
		}

		// Matrix-Matrix Subtraction
		inline Mat2x2 operator-(const Mat2x2& m) const {
			Mat2x2 r;
			for (int i = 0; i < 2; ++i) {
				r[i] = row[i] - m[i];
			}
			return r;
		}


		// ---< MATRIX MULTIPLICATIONS >---

		// Matrix-Scalar Multiplication
		inline Mat2x2 operator*(const double& s) const {
			Mat2x2 r;
			for (int i = 0; i < 2; ++i) {
				r[i] = rows[i].x * s, rows[i].y* s;
			}
			return r;
		}

		// Matrix-Vector multiplication
		inline Vec2d operator*(const Vec2d& v) const {
			return Vec2d(rows[0].dot(v), rows[1].dot(v), rows[2].dot(v));
		}

		// Matrix-Matrix multiplication
		inline Mat2x2 operator*(const Mat2x2& m) const {
			Mat2x2 r;
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 2; j++) {
					r[i][j] = rows[i].x * m[0][j] + rows[i].y * m[1][j];
				}
			}
			return r;
		}
	};

	// Debug Output
	inline std::ostream& operator<<(std::ostream& os, const Mat2x2& m) {
		for (int i = 0; i < 2; i++) os << m.rows[i] << "\n";
		return os;
	}
}

#endif // MAT2X2_H