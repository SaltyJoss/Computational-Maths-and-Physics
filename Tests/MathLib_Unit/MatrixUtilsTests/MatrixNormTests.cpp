/*
 * File: Tests/MathLib_Unit/MatrixUtilsTests/MatrixNormTests.cpp
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

// Test safe normalisation of a Double type 3x3 Matrix
TEST("3x3 Matrix Safe Normalisation (double)", Mat3SafeNorm_D) {
    mathlib::Mat3_T<double> M;
    M << 1.0, 2.0, 3.0,
         4.0, 5.0, 6.0,
         7.0, 8.0, 9.0;
    mathlib::Mat3_T<double> M_norm = mathlib::safeNormalised(M);
    ASSERT_TRUE(mathlib::abs<double>(mathlib::safeNorm(M_norm) - 1.0) < 1e-12, "Safe normalisation of 3x3 matrix failed"); // Check norm is 1
    ASSERT_TRUE(mathlib::abs<double>(M_norm(0, 0) - 0.059234887775909) < 1e-12, "Safe normalisation of 3x3 matrix failed"); // Check first element
}
// Test safe normalisation of a Double type NxM Matrix
TEST("nxm Matrix Safe Normalisation  (double)", MatNMSafeNorm_D) {
    mathlib::MatX_T<double> M(2, 3);
    M << 1.0, 2.0, 3.0,
         4.0, 5.0, 6.0;
    mathlib::MatX_T<double> M_norm = mathlib::safeNormalised(M);
    ASSERT_TRUE(mathlib::abs<double>(mathlib::safeNorm(M_norm) - 1.0) < 1e-12, "Safe normalisation of NxM matrix failed"); // Check norm is 1
    ASSERT_TRUE(mathlib::abs<double>(M_norm(0, 0) - 0.104828483672192) < 1e-12, "Safe normalisation of NxM matrix failed"); // Check first element
}
// Test safe normalisation of a Dual type 3x3 Matrix
TEST("3x3 Matrix Safe Normalisation (dual)", Mat3SafeNorm_Dual) {
    using Dual = mathlib::DualNumber_T<double, 1>;
    mathlib::Mat3_T<Dual> M;
    M << Dual(1.0, {1.0}), Dual(2.0), Dual(3.0),
         Dual(4.0), Dual(5.0), Dual(6.0),
         Dual(7.0), Dual(8.0), Dual(9.0);
    mathlib::Mat3_T<Dual> M_norm = mathlib::safeNormalised(M);
    ASSERT_TRUE(mathlib::abs(mathlib::real(M_norm(0,0)) - 0.12309149097933272) < 1e-12, "Dual real part wrong");
    ASSERT_TRUE(std::isfinite(M_norm(0,0).dual[0]), "Dual derivative not finite");
}
// Test safe normalisation of a Dual type NxM Matrix
TEST("nxm Matrix Safe Normalisation (dual)", MatNMSafeNorm_Dual) {
    using Dual=mathlib::DualNumber_T<double, 1>;
    mathlib::MatX_T<Dual> M(2, 3);
    M << Dual(1.0, {1.0}), Dual(2.0), Dual(3.0),
         Dual(4.0), Dual(5.0), Dual(6.0);
    mathlib::MatX_T<Dual> M_norm = mathlib::safeNormalised(M);
    ASSERT_TRUE(mathlib::abs(mathlib::real(M_norm(0,0)) - 0.12309149097933272) < 1e-12, "Dual real part wrong");
    ASSERT_TRUE(std::isfinite(M_norm(0,0).dual[0]), "Dual derivative not finite");
}
// Test safe normalisation of a zero matrix returns a zero matrix, not NaN
TEST("Zero Matrix Safe Normalisation", MatZero_SafeNorm) {
    mathlib::Mat3 M = mathlib::Mat3::Zero();
    mathlib::Mat3 M_norm = safeNormalised(M);
    ASSERT_TRUE(M_norm.isZero(), "Zero matrix should normalise to zero, not NaN");
}



