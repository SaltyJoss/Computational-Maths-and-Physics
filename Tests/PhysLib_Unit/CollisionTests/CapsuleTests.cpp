/* 
 * File: Tests/PhysLib_Unit/CollisionTests/CapsuleTests.cpp
 * Unit tests for the Capsule primitive and its collision detection functions.
 * Created by: Joss Salton, 10-08-2026
 */
#include "TestHarness.h"
#include "collision/capsule.h"

// Test for the Capsule struct's axis and centre methods
TEST("Capsule_axis_and_centre", capsule_axis_and_centre) {
    physlib::collision::Capsule capsule{mathlib::Vec3(0.0, 0.0, 0.0), mathlib::Vec3(1.0, 1.0, 1.0), 0.5};
    ASSERT_TRUE(capsule.axis() == mathlib::Vec3(1.0, 1.0, 1.0), "Capsule axis should be the vector from a to b");
    ASSERT_TRUE(capsule.centre() == mathlib::Vec3(0.5, 0.5, 0.5), "Capsule centre should be the midpoint of a and b");
}
// Test for closestPtSegmentSegment function
TEST("Capsule_closestPtSegmentSegment", capsule_closestPtSegmentSegment) {
    double s, t;
    mathlib::Vec3 c1, c2;
    double distSq = physlib::collision::closestPtSegmentSegment(
        mathlib::Vec3(0.0, 0.0, 0.0), mathlib::Vec3(1.0, 0.0, 0.0),
        mathlib::Vec3(0.5, 1.0, 0.0), mathlib::Vec3(0.5, -1.0, 0.0),
        s, t, c1, c2
    );
    ASSERT_TRUE(distSq >= 0.0, "Distance squared should be non-negative");
    ASSERT_TRUE(c1 == mathlib::Vec3(0.5, 0.0, 0.0), "Closest point on first segment should be (0.5, 0.0, 0.0)");
    ASSERT_TRUE(c2 == mathlib::Vec3(0.5, 1.0, 0.0), "Closest point on second segment should be (0.5, 1.0, 0.0)");
}
// Test for parallel segments
TEST("Capsule_closestPtSegmentSegment_parallel", capsule_closestPtSegmentSegment_parallel) {
    double s, t;
    mathlib::Vec3 c1, c2;
    double distSq = physlib::collision::closestPtSegmentSegment(
        mathlib::Vec3(0.0, 0.0, 0.0), mathlib::Vec3(1.0, 0.0, 0.0),
        mathlib::Vec3(0.0, 1.0, 0.0), mathlib::Vec3(1.0, 1.0, 0.0),
        s, t, c1, c2
    );
    ASSERT_TRUE(distSq >= 0.0, "Distance squared should be non-negative for parallel segments");
    ASSERT_TRUE(c1 == mathlib::Vec3(0.5, 0.0, 0.0), "Closest point on first segment should be (0.5, 0.0, 0.0)");
    ASSERT_TRUE(c2 == mathlib::Vec3(0.5, 1.0, 0.0), "Closest point on second segment should be (0.5, 1.0, 0.0)");
}
// Test for degenerate segments
TEST("Capsule_closestPtSegmentSegment_degenerate", capsule_closestPtSegmentSegment_degenerate) {
    double s, t;
    mathlib::Vec3 c1, c2;
    double distSq = physlib::collision::closestPtSegmentSegment(
        mathlib::Vec3(0.0, 0.0, 0.0), mathlib::Vec3(0.0, 0.0, 0.0), // Degenerate segment
        mathlib::Vec3(1.0, 1.0, 1.0), mathlib::Vec3(2.0, 2.0, 2.0),
        s, t, c1, c2
    );
    ASSERT_TRUE(distSq >= 0.0, "Distance squared should be non-negative for degenerate segment");
    ASSERT_TRUE(c1 == mathlib::Vec3(0.0, 0.0, 0.0), "Closest point on degenerate segment should be its single point");
}
// Test for both segments being degenerate
TEST("Capsule_closestPtSegmentSegment_both_degenerate", capsule_closestPtSegmentSegment_both_degenerate) {
    double s, t;
    mathlib::Vec3 c1, c2;
    double distSq = physlib::collision::closestPtSegmentSegment(
        mathlib::Vec3(0.0, 0.0, 0.0), mathlib::Vec3(0.0, 0.0, 0.0), // Degenerate segment
        mathlib::Vec3(1.0, 1.0, 1.0), mathlib::Vec3(1.0, 1.0, 1.0), // Degenerate segment
        s, t, c1, c2
    );
    ASSERT_TRUE(distSq >= 0.0, "Distance squared should be non-negative for both degenerate segments");
    ASSERT_TRUE(c1 == mathlib::Vec3(0.0, 0.0, 0.0), "Closest point on first degenerate segment should be its single point");
    ASSERT_TRUE(c2 == mathlib::Vec3(1.0, 1.0, 1.0), "Closest point on second degenerate segment should be its single point");
}

// Test for capsule vs capsule closest points
TEST("Capsule_closestPtSegmentSegment_capsules", capsule_closestPtSegmentSegment_capsules) {
    physlib::collision::Capsule A{mathlib::Vec3(0.0, 0.0, 0.0), mathlib::Vec3(1.0, 0.0, 0.0), 0.5};
    physlib::collision::Capsule B{mathlib::Vec3(0.5, 1.0, 0.0), mathlib::Vec3(1.5, 1.0, 0.0), 0.5};
    physlib::collision::ContactManifold m;
    bool collision = physlib::collision::capsuleCapsule(A, B, m);
    ASSERT_TRUE(collision == true, "Capsules should be colliding");
    ASSERT_TRUE(m.hit == true, "Contact manifold should indicate a hit");
    ASSERT_TRUE(m.pointCount > 0, "Contact manifold should have at least one contact point");
    for (int i = 0; i < m.pointCount; ++i) {
        ASSERT_TRUE(m.points[i].depth > 0.0, "Contact point depth should be positive");
    }
}
// Test for non-colliding capsules
TEST("Capsule_closestPtSegmentSegment_capsules_no_collision", capsule_closestPtSegmentSegment_capsules_no_collision) {
    physlib::collision::Capsule A{mathlib::Vec3(0.0, 0.0, 0.0), mathlib::Vec3(1.0, 0.0, 0.0), 0.5};
    physlib::collision::Capsule B{mathlib::Vec3(2.0, 2.0, 0.0), mathlib::Vec3(3.0, 2.0, 0.0), 0.5};
    physlib::collision::ContactManifold m;
    bool collision = physlib::collision::capsuleCapsule(A, B, m);
    ASSERT_TRUE(collision == false, "Capsules should not be colliding");
    ASSERT_TRUE(m.hit == false, "Contact manifold should indicate no hit");
    ASSERT_TRUE(m.pointCount == 0, "Contact manifold should have no contact points");
}
// Test for overlapping capsules
TEST("Capsule_closestPtSegmentSegment_capsules_overlap", capsule_closestPtSegmentSegment_capsules_overlap) {
    physlib::collision::Capsule A{mathlib::Vec3(0.0, 0.0, 0.0), mathlib::Vec3(1.0, 0.0, 0.0), 1.0};
    physlib::collision::Capsule B{mathlib::Vec3(0.5, 0.5, 0.0), mathlib::Vec3(1.5, 0.5, 0.0), 1.0};
    physlib::collision::ContactManifold m;
    bool collision = physlib::collision::capsuleCapsule(A, B, m);
    ASSERT_TRUE(collision == true, "Capsules should be colliding (overlapping)");
    ASSERT_TRUE(m.hit == true, "Contact manifold should indicate a hit");
    ASSERT_TRUE(m.pointCount > 0, "Contact manifold should have at least one contact point");
    for (int i = 0; i < m.pointCount; ++i) {
        ASSERT_TRUE(m.points[i].depth > 0.0, "Contact point depth should be positive for overlapping capsules");
    }
}
// Test for capsules with one degenerate segment
TEST("Capsule_closestPtSegmentSegment_capsules_degenerate", capsule_closestPtSegmentSegment_capsules_degenerate) {
    physlib::collision::Capsule A{mathlib::Vec3(0.0, 0.0, 0.0), mathlib::Vec3(0.0, 0.0, 0.0), 1.0}; // Degenerate capsule
    physlib::collision::Capsule B{mathlib::Vec3(1.0, 1.0, 1.0), mathlib::Vec3(2.0, 2.0, 2.0), 1.0};
    physlib::collision::ContactManifold m;
    bool collision = physlib::collision::capsuleCapsule(A, B, m);
    ASSERT_TRUE(collision == true, "Degenerate capsule should collide with non-degenerate capsule");
    ASSERT_TRUE(m.hit == true, "Contact manifold should indicate a hit for degenerate capsule");
    ASSERT_TRUE(m.pointCount > 0, "Contact manifold should have at least one contact point for degenerate capsule");
    for (int i = 0; i < m.pointCount; ++i) {
        ASSERT_TRUE(m.points[i].depth > 0.0, "Contact point depth should be positive for degenerate capsule collision");
    }
}
// Test for capsules with both degenerate segments
TEST("Capsule_closestPtSegmentSegment_capsules_both_degenerate", capsule_closestPtSegmentSegment_capsules_both_degenerate) {
    physlib::collision::Capsule A{mathlib::Vec3(0.0, 0.0, 0.0), mathlib::Vec3(0.0, 0.0, 0.0), 1.0}; // Degenerate capsule
    physlib::collision::Capsule B{mathlib::Vec3(1.0, 1.0, 1.0), mathlib::Vec3(1.0, 1.0, 1.0), 1.0}; // Degenerate capsule
    physlib::collision::ContactManifold m;
    bool collision = physlib::collision::capsuleCapsule(A, B, m);
    ASSERT_TRUE(collision == true, "Both degenerate capsules should collide");
    ASSERT_TRUE(m.hit == true, "Contact manifold should indicate a hit for both degenerate capsules");
    ASSERT_TRUE(m.pointCount > 0, "Contact manifold should have at least one contact point for both degenerate capsules");
    for (int i = 0; i < m.pointCount; ++i) {
        ASSERT_TRUE(m.points[i].depth > 0.0, "Contact point depth should be positive for both degenerate capsules collision");
    }
}
// Test for capsules with zero radius
TEST("Capsule_closestPtSegmentSegment_capsules_zero_radius", capsule_closestPtSegmentSegment_capsules_zero_radius) {
    physlib::collision::Capsule A{mathlib::Vec3(0.0, 0.0, 0.0), mathlib::Vec3(1.0, 0.0, 0.0), 0.0}; // Zero radius capsule
    physlib::collision::Capsule B{mathlib::Vec3(0.5, 1.0, 0.0), mathlib::Vec3(1.5, 1.0, 0.0), 0.0}; // Zero radius capsule
    physlib::collision::ContactManifold m;
    bool collision = physlib::collision::capsuleCapsule(A, B, m);
    ASSERT_TRUE(collision == false, "Zero radius capsules should not collide");
    ASSERT_TRUE(m.hit == false, "Contact manifold should indicate no hit for zero radius capsules");
    ASSERT_TRUE(m.pointCount == 0, "Contact manifold should have no contact points for zero radius capsules");
}
// Test for capsules with one zero radius and one non-zero radius
TEST("Capsule_closestPtSegmentSegment_capsules_one_zero_radius", capsule_closestPtSegmentSegment_capsules_one_zero_radius) {
    physlib::collision::Capsule A{mathlib::Vec3(0.0, 0.0, 0.0), mathlib::Vec3(1.0, 0.0, 0.0), 0.0}; // Zero radius capsule
    physlib::collision::Capsule B{mathlib::Vec3(0.5, 1.0, 0.0), mathlib::Vec3(1.5, 1.0, 0.0), 1.0}; // Non-zero radius capsule
    physlib::collision::ContactManifold m;
    bool collision = physlib::collision::capsuleCapsule(A, B, m);
    ASSERT_TRUE(collision == true, "Zero radius capsule should collide with non-zero radius capsule");
    ASSERT_TRUE(m.hit == true, "Contact manifold should indicate a hit for zero and non-zero radius capsules");
    ASSERT_TRUE(m.pointCount > 0, "Contact manifold should have at least one contact point for zero and non-zero radius capsules");
    for (int i = 0; i < m.pointCount; ++i) {
        ASSERT_TRUE(m.points[i].depth > 0.0, "Contact point depth should be positive for zero and non-zero radius capsules collision");
    }
}