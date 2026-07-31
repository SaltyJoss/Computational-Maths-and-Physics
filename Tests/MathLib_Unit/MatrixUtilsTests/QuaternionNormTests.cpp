/*
 * File: Tests/MathLib_Unit/MatrixUtilsTests/QuaternionNormTests.cpp
 * Project: PxM-Lib
 * Author: Joss Salton, 31/07/2026
 */
#include "TestHarness.h"
#include <core/MathLib.h>
#include <cmath>
#include <functional>

/*
 * Test safe normalisation of Matrices.
 */
TEST("Quaternion Safe Normalisation (double)", QuatSafeNorm_D) {
    mathlib::Quat_T<double> q(1.0, 2.0, 3.0, 4.0);   // w,x,y,z — non-unit
	auto qn = mathlib::safeNormalised(q);
	ASSERT_TRUE(std::abs(qn.norm() - 1.0) < 1e-12, "not unit");
	// direction preserved: qn proportional to q
	ASSERT_TRUE(std::abs(qn.w() - 1.0/std::sqrt(30.0)) < 1e-12, "w wrong");
}

TEST("Quaternion Safe Normalisation (dual)", QuatSafeNorm_Dual) {
	using Dual = mathlib::DualNumber_T<double,1>;
	Eigen::Quaternion<Dual> q(Dual(1.0,{1.0}), Dual(0.0), Dual(0.0), Dual(0.0));
	auto qn = mathlib::safeNormalised(q);
	ASSERT_TRUE(mathlib::abs(mathlib::real(qn.w()) - 1.0) < 1e-12, "dual real wrong");
	ASSERT_TRUE(std::isfinite(qn.w().dual[0]), "dual deriv not finite");
}

TEST("Zero Quaternion -> identity", QuatSafeNorm_Zero) {
	mathlib::Quat_T<double> q(0,0,0,0);
	auto qn = mathlib::safeNormalised(q);
	ASSERT_TRUE(std::abs(qn.w() - 1.0) < 1e-12 && std::abs(qn.x()) < 1e-12, "zero should give identity");
}