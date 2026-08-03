/*
 * File: Tests/PhysLib_Unit/CollisionTests/ContactTests.cpp
 * Unit tests for the Contact Manifold and contact point generation.
 * Created by: Joss Salton, 03-08-2026
 */
#include "TestHarness.h"
#include "collision/contact.h"

TEST("ContactManifold_addPoint", contactManifold_addPoint) {
    physlib::collision::ContactManifold manifold;
    manifold.addPoint(mathlib::Vec3(1.0, 2.0, 3.0), 0.5);
    ASSERT_TRUE(manifold.pointCount == 1, "Manifold point count should be 1 after adding a point");
    ASSERT_TRUE(manifold.points[0].pos == mathlib::Vec3(1.0, 2.0, 3.0), "Manifold contact point position should match the added point");
    ASSERT_TRUE(manifold.points[0].depth == 0.5, "Manifold contact point depth should match the added point");
}

TEST("ContactManifold_addPoint_limit", contactManifold_addPoint_limit) {
    physlib::collision::ContactManifold manifold;
    for (int i = 0; i < 5; ++i) {
        manifold.addPoint(mathlib::Vec3(i, i, i), 0.1 * i);
    }
    ASSERT_TRUE(manifold.pointCount == 4, "Manifold point count should be capped at 4");
    for (int i = 0; i < 4; ++i) {
        ASSERT_TRUE(manifold.points[i].pos == mathlib::Vec3(i, i, i), "Manifold contact point position should match the added points");
        ASSERT_TRUE(manifold.points[i].depth == 0.1 * i, "Manifold contact point depth should match the added points");
    }
}