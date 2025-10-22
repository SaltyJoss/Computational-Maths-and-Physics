#ifndef MAT3X3_H
#define MAT3X3_H

#include "Vec3D.hpp"
#include <iostream>

namespace mathlib {
	struct Mat3x3 {
		Vec3d rows[3];

		// Default Constructor
		constexpr Mat3x3() = default;
		// Constructor from Vec3d rows
		constexpr Mat3x3(const Vec3d& r0, const Vec3d& r1, const Vec3d& r2) {
			rows[0] = r0;
			rows[1] = r1;
			rows[2] = r2;
		}
		// Constructor from 9 scalars
		constexpr Mat3x3(double a00, double a01, double a02,
						 double a10, double a11, double a12,
						 double a20, double a21, double a22)
			: rows{ {a00, a01, a02}, {a10, a11, a12}, {a20, a21, a22} } {
		}

		/*
		// Transpose
		Mat3x3 transpose() const {	
			return Mat3x3(
				Vec3d(rows[0].x, rows[1].x, rows[2].x), 
				Vec3d(rows[0].y, rows[1].y, rows[2].y), 
				Vec3d(rows[0].z, rows[1].z, rows[2].z));
		}
		*/

		// Access Operators
		inline Vec3d& operator[](int i) { return rows[i]; }
		inline const Vec3d& operator[](int i) const { return rows[i]; }


		// ---< MATRIX ADDITIONS >---

		// Matrix-Scalar Addition
		inline Mat3x3 operator+(const double& s) const {
			Mat3x3 r;
			for (int i = 0; i < 3; ++i) {
				r[i] = rows[i].x + s, rows[i].y + s, rows[i].z + s;
			}
			return r;
		}

		// Matrix-Vector Addition
		inline Mat3x3 operator+(const Vec3d& v) const {
			Mat3x3 r;
			for (int i = 0; i < 3; ++i) {
				r[i] = row[i] + v;
			}
			return r;
		}

		// Matrix-Matrix Addition
		inline Mat3x3 operator+(const Mat3x3& m) const {
			Mat3x3 r;
			for (int i = 0; i < 3; ++i) {
				r[i] = row[i] + m[i];
			}
			return r;
		}


		// ---< MATRIX SUBTRACTIONS >---

		// Matrix-Scalar Subtraction
		inline Mat3x3 operator-(const double& s) const {
			Mat3x3 r;
			for (int i = 0; i < 3; ++i) {
				r[i] = rows[i].x - s, rows[i].y - s, rows[i].z - s;
			}
			return r;
		}

		// Matrix-Vector Subtraction
		inline Mat3x3 operator-(const Vec3d& v) const {
			Mat3x3 r;
			for (int i = 0; i < 3; ++i) {
				r[i] = row[i] + v;
			}
			return r;
		}

		// Matrix-Matrix Subtraction
		inline Mat3x3 operator-(const Mat3x3& m) const {
			Mat3x3 r;
			for (int i = 0; i < 3; ++i) {
				r[i] = row[i] - m[i];
			}
			return r;
		}


		// ---< MATRIX MULTIPLICATIONS >---

		// Matrix-Scalar Multiplication
		inline Mat3x3 operator*(const double& s) const {
			Mat3x3 r;
			for (int i = 0; i < 3; ++i) {
				r[i] = rows[i].x * s, rows[i].y * s, rows[i].z * s;
			}
			return r;
		}

		// Matrix-Vector multiplication
		inline Vec3d operator*(const Vec3d& v) const {
			return Vec3d(rows[0].dot(v), rows[1].dot(v), rows[2].dot(v));
		}

		// Matrix-Matrix multiplication
		inline Mat3x3 operator*(const Mat3x3& m) const {
			Mat3x3 r;
			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; j++) {
					r[i][j] = rows[i].x * m[0][j] + rows[i].y * m[1][j] + rows[i].z * m[2][j];
				}
			}
			return r;
		}
	};

	// Debug Output
	inline std::ostream& operator<<(std::ostream& os, const Mat3x3& m) {
		for (int i = 0; i < 3; i++) os << m.rows[i] << "\n";
		return os;
	}
}

#endif // MAT3X3_H