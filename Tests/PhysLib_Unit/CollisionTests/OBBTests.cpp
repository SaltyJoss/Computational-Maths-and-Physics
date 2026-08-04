/*
 * File: Tests/PhysLib_Unit/CollisionTests/OBBTests.cpp
 * Unit tests for the Oriented Bounding Box (OBB) collision detection.
 * Created by: Joss Salton, 03-08-2026
 */
#include "TestHarness.h"
#include "collision/OBB.h"

TEST("OBB_fromAABB", obb_fromAABB) {
    physlib::collision::AABB aabb{ { -1.0, -1.0, -1.0 }, { 1.0, 1.0, 1.0 } };
    physlib::collision::OBB obb = physlib::collision::OBB::fromAABB(aabb, mathlib::Mat3::Identity(), mathlib::Vec3(0.0, 0.0, 0.0));
    ASSERT_TRUE(obb.centre == mathlib::Vec3(0.0, 0.0, 0.0), "OBB centre should be at origin");
    ASSERT_TRUE(obb.halfExtents == mathlib::Vec3(1.0, 1.0, 1.0), "OBB half extents should be (1,1,1)");
    ASSERT_TRUE(obb.orientation == mathlib::Mat3::Identity(), "OBB orientation should be identity");
}

TEST("OBB_axis", obb_axis) {
    physlib::collision::OBB obb;
    obb.orientation = mathlib::Mat3::Identity();
    ASSERT_TRUE(obb.axis(0) == mathlib::Vec3(1.0, 0.0, 0.0), "OBB axis 0 should be (1,0,0)");
    ASSERT_TRUE(obb.axis(1) == mathlib::Vec3(0.0, 1.0, 0.0), "OBB axis 1 should be (0,1,0)");
    ASSERT_TRUE(obb.axis(2) == mathlib::Vec3(0.0, 0.0, 1.0), "OBB axis 2 should be (0,0,1)");
}