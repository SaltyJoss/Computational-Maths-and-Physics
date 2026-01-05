#include <gtest/gtest.h>
#include <iostream>
#include <cmath>
#include <functional>

#include "mathlib/LinearAlgebra/Matrix2x2.hpp"
using Vec2d = mathlib::Vec2<double>;
using Mat2x2d = mathlib::Mat2x2<double>;


// ---< CONTSTRUCTOR TESTS >---

// Default Constructor Test
TEST(test_Matrix2x2, DefaultConstructor) {
	mathlib::Mat2x2 m;

	EXPECT_DOUBLE_EQ(m.rows[0].x, 0.0) << "Default constructor failed: [1st row] x is not 0";
	EXPECT_DOUBLE_EQ(m.rows[1].x, 0.0) << "Default constructor failed: [2nd row] x is not 0";
	EXPECT_DOUBLE_EQ(m.rows[0].y, 0.0) << "Default constructor failed: [1st row] y is not 0";
	EXPECT_DOUBLE_EQ(m.rows[1].y, 0.0) << "Default constructor failed: [2nd row] y is not 0";

}

// Constructor with Vector Parameters Test
TEST(test_Matrix2x2, VectorParamConstructor) {
	mathlib::Vec2d v(1, 2);
	mathlib::Vec2d w(3, 4);

	mathlib::Mat2x2 m(v, w);

	EXPECT_DOUBLE_EQ(m.rows[0].x, 1.0) << "Vector Param constructor failed: [1st row] x mismatch";
	EXPECT_DOUBLE_EQ(m.rows[1].x, 3.0) << "Vector Param constructor failed: [2nd row] x mismatch";
	EXPECT_DOUBLE_EQ(m.rows[0].y, 2.0) << "Vector Param constructor failed: [1st row] y mismatch";
	EXPECT_DOUBLE_EQ(m.rows[1].y, 4.0) << "Vector Param constructor failed: [2nd row] y mismatch";
}

// Constructor with Scalar Parameters Test
TEST(test_Matrix2x2, ScalarParamConstructor) {
	mathlib::Mat2x2 m(4.0, 3.0, 2.0, 1.0);

	EXPECT_DOUBLE_EQ(m.rows[0].x, 4.0) << "Scalar Param constructor failed: [1st row] a00 is not 4";
	EXPECT_DOUBLE_EQ(m.rows[1].x, 2.0) << "Scalar Param constructor failed: [2nd row] a10 is not 2";
	EXPECT_DOUBLE_EQ(m.rows[0].y, 3.0) << "Scalar Param constructor failed: [1st row] a01 is not 3";
	EXPECT_DOUBLE_EQ(m.rows[1].y, 1.0) << "Scalar Param constructor failed: [2nd row] a11 is not 1";
}

// ---< MATRIX-SCALAR TESTS >---

// Matrix-Scalar Addition Test
TEST(test_Matrix2x2, ScalarAddition) {
	mathlib::Vec2d v(1, 2);
	mathlib::Vec2d w(3, 4);
	mathlib::Mat2x2 m1(v, w);

	mathlib::Mat2x2 m2 = m1 + 4;

	EXPECT_DOUBLE_EQ(m2.rows[0].x, 5.0) << "Matrix-Scalar Addition failed: [1st row] x-component incorrect";
	EXPECT_DOUBLE_EQ(m2.rows[1].x, 7.0) << "Matrix-Scalar Addition failed: [2nd row] x-component incorrect";
	EXPECT_DOUBLE_EQ(m2.rows[0].y, 6.0) << "Matrix-Scalar Addition failed: [1st row] y-component incorrect";
	EXPECT_DOUBLE_EQ(m2.rows[1].y, 8.0) << "Matrix-Scalar Addition failed: [2nd row] y-component incorrect";
}

// Matrix-Scalar Subtraction Test
TEST(test_Matrix2x2, ScalarSubtraction) {
	mathlib::Vec2d v(4, 3);
	mathlib::Vec2d w(2, 1);
	mathlib::Mat2x2 m1(v, w);

	mathlib::Mat2x2 m2 = m1 - 1;

	EXPECT_DOUBLE_EQ(m2.rows[0].x, 3.0) << "Matrix-Scalar Subtraction failed: [1st row] x-component incorrect";
	EXPECT_DOUBLE_EQ(m2.rows[1].x, 1.0) << "Matrix-Scalar Subtraction failed: [2nd row] x-component incorrect";
	EXPECT_DOUBLE_EQ(m2.rows[0].y, 2.0) << "Matrix-Scalar Subtraction failed: [1st row] y-component incorrect";
	EXPECT_DOUBLE_EQ(m2.rows[1].y, 0.0) << "Matrix-Scalar Subtraction failed: [2nd row] y-component incorrect";
}

// Matrix-Scalar Multiplication Test
TEST(test_Matrix2x2, ScalarMultiplication) {
	mathlib::Vec2d v(12.2, 34);
	mathlib::Vec2d w(-2.8, 4.3);
	mathlib::Mat2x2 m1(v, w);

	mathlib::Mat2x2 m2 = m1 * 1.345;

	EXPECT_NEAR(m2.rows[0].x, m1.rows[0].x * 1.345, 1e-9) << "Matrix-Scalar Subtraction failed: [1st row] x-component incorrect";
	EXPECT_NEAR(m2.rows[1].x, m1.rows[1].x * 1.345, 1e-9) << "Matrix-Scalar Subtraction failed: [2nd row] x-component incorrect";
	EXPECT_NEAR(m2.rows[0].y, m1.rows[0].y * 1.345, 1e-9) << "Matrix-Scalar Subtraction failed: [1st row] y-component incorrect";
	EXPECT_NEAR(m2.rows[1].y, m1.rows[1].y * 1.345, 1e-9) << "Matrix-Scalar Subtraction failed: [2nd row] y-component incorrect";
}

// ---< MATRIX-VECTOR TESTS >---

// Matrix-Scalar Addition Test
TEST(test_Matrix2x2, VectorAddition) {
	mathlib::Vec2d v(1, 2);
	mathlib::Vec2d w(3, 4);
	mathlib::Mat2x2 m1(v, w);

	mathlib::Vec2d u(2, 1);

	mathlib::Mat2x2 m2 = m1 + u;

	EXPECT_DOUBLE_EQ(m2.rows[0].x, 3.0) << "Matrix-Vector Addition failed: [1st row] x-component incorrect";
	EXPECT_DOUBLE_EQ(m2.rows[1].x, 5.0) << "Matrix-Vector Addition failed: [2nd row] x-component incorrect";
	EXPECT_DOUBLE_EQ(m2.rows[0].y, 3.0) << "Matrix-Vector Addition failed: [1st row] y-component incorrect";
	EXPECT_DOUBLE_EQ(m2.rows[1].y, 5.0) << "Matrix-Vector Addition failed: [2nd row] y-component incorrect";
}

// Matrix-Scalar Subtraction Test
TEST(test_Matrix2x2, VectorSubtraction) {
	mathlib::Vec2d v(4, 3);
	mathlib::Vec2d w(2, 1);
	mathlib::Mat2x2 m1(v, w);

	mathlib::Vec2d u(1, -2);

	mathlib::Mat2x2 m2 = m1 - u;

	EXPECT_DOUBLE_EQ(m2.rows[0].x, 3.0) << "Matrix-Vector Subtraction failed: [1st row] x-component incorrect";
	EXPECT_DOUBLE_EQ(m2.rows[1].x, 5.0) << "Matrix-Vector Subtraction failed: [2nd row] x-component incorrect";
	EXPECT_DOUBLE_EQ(m2.rows[0].y, 1.0) << "Matrix-Vector Subtraction failed: [1st row] y-component incorrect";
	EXPECT_DOUBLE_EQ(m2.rows[1].y, 3.0) << "Matrix-Vector Subtraction failed: [2nd row] y-component incorrect";
}

// Matrix-Scalar Multiplication Test
TEST(test_Matrix2x2, VectorMultiplication) {
	mathlib::Vec2d v(1.234, 0.34);
	mathlib::Vec2d w(2.1, -0.742);
	mathlib::Mat2x2 m1(v, w);

	mathlib::Vec2d u(-5, 1.5);

	mathlib::Vec2d w = m1 * u;

	EXPECT_NEAR(w.x, (m1.rows[0].x * -5) + (m1.rows[0].y * 1.5), 1e-9) << "Matrix-Vector Multiplication failed: x-component incorrect";
	EXPECT_NEAR(w.x, (m1.rows[1].x * -5) + (m1.rows[1].y * 1.5), 1e-9) << "Matrix-Vector Multiplication failed: y-component incorrect";
}

// ---< MATRIX-MATRIX TESTS >---

// Matrix-Scalar Addition Test
TEST(test_Matrix2x2, MatrixAddition) {
	mathlib::Vec2d v(1, 2);
	mathlib::Vec2d w(3, 4);

	mathlib::Mat2x2 A(v, w);
	mathlib::Mat2x2 B(w, v);

	mathlib::Mat2x2 C = A + B; // 4,6,4,6

	EXPECT_DOUBLE_EQ(C.rows[0].x, 4.0) << "Matrix-Matrix Addition failed: [1st row] x-component incorrect";
	EXPECT_DOUBLE_EQ(C.rows[1].x, 6.0) << "Matrix-Matrix Addition failed: [2nd row] x-component incorrect";
	EXPECT_DOUBLE_EQ(C.rows[0].y, 4.0) << "Matrix-Matrix Addition failed: [1st row] y-component incorrect";
	EXPECT_DOUBLE_EQ(C.rows[1].y, 6.0) << "Matrix-Matrix Addition failed: [2nd row] y-component incorrect";
}

// Matrix-Scalar Subtraction Test
TEST(test_Matrix2x2, MatrixSubtraction) {
	mathlib::Vec2d v(3, 6);
	mathlib::Vec2d w(2, -1);

	mathlib::Mat2x2 A(v, w);
	mathlib::Mat2x2 B(w, v);

	mathlib::Mat2x2 C = A - B; // 1,7,-1,-7

	EXPECT_DOUBLE_EQ(C.rows[0].x, 1.0) << "Matrix-Matrix Subtraction failed: [1st row] x-component incorrect";
	EXPECT_DOUBLE_EQ(C.rows[1].x, 7.0) << "Matrix-Matrix Subtraction failed: [2nd row] x-component incorrect";
	EXPECT_DOUBLE_EQ(C.rows[0].y, -1.0) << "Matrix-Matrix Subtraction failed: [1st row] y-component incorrect";
	EXPECT_DOUBLE_EQ(C.rows[1].y, -7.0) << "Matrix-Matrix Subtraction failed: [2nd row] y-component incorrect";
}

// Matrix-Scalar Multiplication Test
TEST(test_Matrix2x2, MatrixMultiplication) {
	mathlib::Vec2d v(3, 6);
	mathlib::Vec2d w(2, -1);

	mathlib::Mat2x2 A(v, w);
	mathlib::Mat2x2 B(w, v);

	mathlib::Mat2x2 C = A * B; // 1,7,-1,-7

	double c00 = (A.rows[0].x * B.rows[0].x) + (A.rows[0].y * B.rows[1].x); // a00b00 + a01b10
	double c10 = (A.rows[1].x * B.rows[0].x) + (A.rows[1].y * B.rows[1].x);	// a10b00 + a11b10
	double c01 = (A.rows[0].x * B.rows[0].y) + (A.rows[0].y * B.rows[1].y);	// a00b01 + a01b11
	double c11 = (A.rows[1].x * B.rows[0].y) + (A.rows[1].y * B.rows[1].y);	// a10b01 + a11b11


	EXPECT_NEAR(C.rows[0].x, c00, 1e-9) << "Matrix-Matrix Multiplication failed: [1st row] x-component incorrect";
	EXPECT_NEAR(C.rows[1].x, c10, 1e-9) << "Matrix-Matrix Multiplication failed: [2nd row] x-component incorrect";
	EXPECT_NEAR(C.rows[0].y, c01, 1e-9) << "Matrix-Matrix Multiplication failed: [1st row] y-component incorrect";
	EXPECT_NEAR(C.rows[1].y, c11, 1e-9) << "Matrix-Matrix Multiplication failed: [2nd row] y-component incorrect";
}