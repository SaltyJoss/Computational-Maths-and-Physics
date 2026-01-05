#include <gtest/gtest.h>
#include <iostream>
#include <cmath>
#include <functional>

#include "mathlib/LinearAlgebra/Vec3d.hpp"

// Default Constructor Test
TEST(test_Vec3d, DefaultConstructor) {
	mathlib::Vec3d v;
	EXPECT_DOUBLE_EQ(v.x, 0.0) << "Default constructor failed: x is not 0";
	EXPECT_DOUBLE_EQ(v.y, 0.0) << "Default constructor failed: y is not 0";
	EXPECT_DOUBLE_EQ(v.z, 0.0) << "Default constructor failed: z is not 0";
}

// Construct with Parameters Test
TEST(test_Vec3d, ParamConstructor) {
	mathlib::Vec3d v(1.0, 2.0, 3.0);
	EXPECT_DOUBLE_EQ(v.x, 1.0) << "Parameterized constructor failed: x mismatch";
	EXPECT_DOUBLE_EQ(v.y, 2.0) << "Parameterized constructor failed: y mismatch";
	EXPECT_DOUBLE_EQ(v.z, 3.0) << "Parameterized constructor failed: z mismatch";
}

// Vector Addition Test
TEST(test_Vec3d, AdditionTest) {
	mathlib::Vec3d a(1, 2, 3);
	mathlib::Vec3d b(4, 5, 6);
	mathlib::Vec3d c = a + b;
	EXPECT_DOUBLE_EQ(c.x, 5.0) << "Vector addition failed: x-component incorrect";
	EXPECT_DOUBLE_EQ(c.y, 7.0) << "Vector addition failed: y-component incorrect";
	EXPECT_DOUBLE_EQ(c.z, 9.0) << "Vector addition failed: z-component incorrect";
}

// Vector Subtraction Test
TEST(test_Vec3d, SubtractionTest) {
	mathlib::Vec3d a(5, 7, 9);
	mathlib::Vec3d b(1, 2, 3);
	mathlib::Vec3d c = a - b;
	EXPECT_DOUBLE_EQ(c.x, 4.0) << "Vector subtraction failed: x-component incorrect";
	EXPECT_DOUBLE_EQ(c.y, 5.0) << "Vector subtraction failed: y-component incorrect";
	EXPECT_DOUBLE_EQ(c.z, 6.0) << "Vector subtraction failed: z-component incorrect";
}

// Vector Multiplication Test
TEST(test_Vec3d, ScalarMultiplicationTest) {
	mathlib::Vec3d v(1, 2, 3);
	mathlib::Vec3d w = v * 2.0;
	EXPECT_DOUBLE_EQ(w.x, 2.0) << "Scalar multiplication failed: x-component incorrect";
	EXPECT_DOUBLE_EQ(w.y, 4.0) << "Scalar multiplication failed: y-component incorrect";
	EXPECT_DOUBLE_EQ(w.z, 6.0) << "Scalar multiplication failed: z-component incorrect";
}

// Dot Product Test
TEST(test_Vec3d, DotProductTest) {
	mathlib::Vec3d a(1, 2, 3);
	mathlib::Vec3d b(4, 5, 6);
	double dot = a.dot(b);
	EXPECT_DOUBLE_EQ(dot, 32.0) << "Dot product failed: expected 32.0";
}

// Cross Product Test
TEST(test_Vec3d, CrossProductTest) {
	mathlib::Vec3d a(1.0, 0.0, 0.0);
	mathlib::Vec3d b(0.0, 1.0, 0.0);
	mathlib::Vec3d c = a.cross(b);

	EXPECT_NEAR(c.x, 0.0, 1e-9);
	EXPECT_NEAR(c.y, 0.0, 1e-9);
	EXPECT_NEAR(c.z, 1.0, 1e-9);

	EXPECT_NEAR(c.dot(a), 0.0, 1e-9);
	EXPECT_NEAR(c.dot(b), 0.0, 1e-9);

	EXPECT_NEAR(c.magnitude(), 1.0, 1e-9);

	EXPECT_GT(c.z, 0.0) << "Cross product direction is incorrect (should follow right-hand rule)";
}

// Normalise Test
TEST(test_Vec3d, NormalisetTest) {
	mathlib::Vec3d v(1.3553, 4.23123, 14.3452);
	mathlib::Vec3d n = v.normalised();

	EXPECT_NEAR(n.magnitude(), 1.0, 1e-9)
		<< "Normalisation failed: 3D-Vector " << v
		<< " did not produce unit length Vector " << n;

	double scale = 0.0;
	if (v.x != 0) scale = n.x / v.x;
	else if (v.y != 0) scale = n.y / v.y;
	else if (v.z != 0) scale = n.z / v.z;
	else FAIL() << "Cannot normalise a zero vector: " << v;

	EXPECT_NEAR(n.x, v.x * scale, 1e-9)
		<< "x-component mismatch after normalisation: v= " << v << ", n=" << n;
	EXPECT_NEAR(n.y, v.y * scale, 1e-9)
		<< "y-component mismatch after normalisation: v= " << v << ", n=" << n;
	EXPECT_NEAR(n.z, v.z * scale, 1e-9)
		<< "z-component mismatch after normalisation: v= " << v << ", n=" << n;
}