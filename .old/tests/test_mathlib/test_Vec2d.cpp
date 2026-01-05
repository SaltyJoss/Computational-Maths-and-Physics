#include <gtest/gtest.h>
#include <iostream>
#include <cmath>
#include <functional>

#include "mathlib/LinearAlgebra/Vec2d.hpp"

// Default Constructor Test
TEST(test_Vec2d, DefaultConstructor) {
	mathlib::Vec2d v;
	EXPECT_DOUBLE_EQ(v.x, 0.0) << "Default constructor failed: x is not 0";
	EXPECT_DOUBLE_EQ(v.y, 0.0) << "Default constructor failed: y is not 0";
}

// Construct with Parameters Test
TEST(test_Vec2d, ParamConstructor) {
	mathlib::Vec2d v(1.0, 2.0);
	EXPECT_DOUBLE_EQ(v.x, 1.0) << "Parameterized constructor failed: x mismatch";
	EXPECT_DOUBLE_EQ(v.y, 2.0) << "Parameterized constructor failed: y mismatch";
}

// Vector Addition Test
TEST(test_Vec2d, AdditionTest) {
	mathlib::Vec2d a(2.0, 2.0);
	mathlib::Vec2d b(5.0, 4.0);
	mathlib::Vec2d c = a + b;
	EXPECT_DOUBLE_EQ(c.x, 7.0) << "Vector addition failed: x-component incorrect";
	EXPECT_DOUBLE_EQ(c.y, 6.0) << "Vector addition failed: y-component incorrect";
}

// Vector Subtraction Test
TEST(test_Vec2d, SubtractionTest) {
	mathlib::Vec2d a(2.0, 2.0);
	mathlib::Vec2d b(5.0, 4.0);
	mathlib::Vec2d c = a - b;
	EXPECT_DOUBLE_EQ(c.x, -3.0) << "Scalar substraction failed: x-component incorrect";
	EXPECT_DOUBLE_EQ(c.y, -2.0) << "Scalar substraction failed: y-component incorrect";
}

// Vector Multiplication Test
TEST(test_Vec2d, ScalarMultiplicationTest) {
	mathlib::Vec2d v(1.0, 6.0);
	mathlib::Vec2d w = v * 3;
	EXPECT_DOUBLE_EQ(w.x, 3.0) << "Scalar multiplication failed: x-component incorrect";
	EXPECT_DOUBLE_EQ(w.y, 18.0) << "Scalar multiplication failed: y-component incorrect";
}

// Dot Product Test
TEST(test_Vec2d, DotProductTest) {
	mathlib::Vec2d a(1.0, 6.0);
	mathlib::Vec2d b(3.2, 0.5);
	double dot = a.dot(b);
	EXPECT_DOUBLE_EQ(dot, 6.2) << "Dot product failed: expected 6.2";
}


// Normalise Test
TEST(test_Vec2d, NormalisetTest) {
	mathlib::Vec2d v(1.32, 6.121);
	mathlib::Vec2d n = v.normalised();
	
	EXPECT_NEAR(n.magnitude(), 1.0, 1e-9) << "Normalisation failed: 2D-Vector " << v << " did not produce unit length Vector " << n;

	double scaleX = (v.x != 0) ? n.x / v.x : n.y / v.y;
	EXPECT_NEAR(n.x, v.x * scaleX, 1e-9)
		<< "x-component mismatch after normalisation: v= " << v << ", n=" << n;
	EXPECT_NEAR(n.y, v.y * scaleX, 1e-9)
		<< "y-component mismatch after normalisation: v= " << v << ", n=" << n;
}