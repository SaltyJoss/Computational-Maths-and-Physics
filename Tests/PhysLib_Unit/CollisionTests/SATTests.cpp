/*
 * File: Tests/PhysLib_Unit/CollisionTests/SATTests.cpp
 * Unit tests for the Separating Axis Theorem (SAT) collision detection.
 * Created by: Joss Salton, 03-08-2026
 */
#include "TestHarness.h"
#include "collision/SAT.h"
#include <constants>

using namespace constants;

TEST("SAT_OBB_no_collision", sat_obb_no_collision) {
    physlib::collision::OBB a{ { 0.0, 0.0, 0.0 }, { 1.0, 1.0, 1.0 }, mathlib::Mat3::Identity() };
    physlib::collision::OBB b{ { 3.0, 3.0, 3.0 }, { 1.0, 1.0, 1.0 }, mathlib::Mat3::Identity() };
    physlib::collision::ContactManifold manifold;
    bool result = physlib::collision::SAT_OBB(a, b, manifold);
    ASSERT_TRUE(!result, "OBBs should not collide");
}

TEST("SAT_OBB_collision", sat_obb_collision) {
    physlib::collision::OBB a{ { 0.0, 0.0, 0.0 }, { 1.0, 1.0, 1.0 }, mathlib::Mat3::Identity() };
    physlib::collision::OBB b{ { 0.5, 0.5, 0.5 }, { 1.0, 1.0, 1.0 }, mathlib::Mat3::Identity() };
    physlib::collision::ContactManifold manifold;
    bool result = physlib::collision::SAT_OBB(a, b, manifold);
    ASSERT_TRUE(result, "OBBs should collide");
    ASSERT_TRUE(manifold.hit, "Manifold should indicate a hit");
    ASSERT_TRUE(manifold.normal.squaredNorm() > 0.0, "Manifold normal should be non-zero");
    ASSERT_TRUE(manifold.toi == 0.0, "Manifold time of impact should be zero for overlapping OBBs");
}

TEST("SAT_OBB_edge_case", sat_obb_edge_case) {
    physlib::collision::OBB a{ { 0.0, 0.0, 0.0 }, { 1.0, 1.0, 1.0 }, mathlib::Mat3::Identity() };
    physlib::collision::OBB b{ { 2.0, 0.0, 0.0 }, { 1.0, 1.0, 1.0 }, mathlib::Mat3::Identity() };
    physlib::collision::ContactManifold manifold;
    bool result = physlib::collision::SAT_OBB(a, b, manifold);
    ASSERT_TRUE(!result, "OBBs should not collide at edge case");
}

TEST("SAT_OBB_rotated_collision", sat_obb_rotated_collision) {
    physlib::collision::OBB a{ { 0.0, 0.0, 0.0 }, { 1.0, 1.0, 1.0 }, mathlib::Mat3::Identity() };
    physlib::collision::OBB b{ { 0.5, 0.5, 0.5 }, { 1.0, 1.0, 1.0 }, Eigen::AngleAxisd(PI_d / 4, mathlib::Vec3(0, 1, 0)).toRotationMatrix() };
    physlib::collision::ContactManifold manifold;
    bool result = physlib::collision::SAT_OBB(a, b, manifold);
    ASSERT_TRUE(result, "Rotated OBBs should collide");
    ASSERT_TRUE(manifold.hit, "Manifold should indicate a hit for rotated OBBs");
}