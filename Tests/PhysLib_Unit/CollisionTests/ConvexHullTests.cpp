/*
 * File: Tests/PhysLib_Unit/CollisionTests/ConvexHullTests.cpp
 * Unit tests for the Convex Hull building algorithm and its support function.
    * Created by: Joss Salton, 05-09-2026
 */
#include "TestHarness.h"
#include "collision/convex_hull_build.h"
#include "collision/convex_hull.h"
#include "collision/GJK.h"
#include "collision/EPA.h"

using namespace physlib::collision;

namespace {
    static ConvexHull boxHull(const mathlib::Vec3& c, double h) {
        ConvexHull out;
        for (int i=0; i < 8; ++i) {
            out.verts.push_back(c + mathlib::Vec3(
                (i & 1)?h:-h,
                (i & 2)?h:-h,
                (i & 4)?h:-h
            ));
        }
        return out;
    }
}

// Unit test for GJK with overlapping boxes
TEST("GJK_overlapping_boxes_intersect", gjk_overlapping_boxes_intersect) {
    ConvexHull a = boxHull({0,0,0}, 1.0);
    ConvexHull b = boxHull({0.5,0,0}, 1.0); // overlappiong along x-axis
    Simplex s;
    CHECK(gjkIntersect(a, b, s), "GJK should detect intersection for overlapping boxes");
}
// Unit test for GJK with separated boxes
TEST("GJK_separated_boxes_no_intersect", gjk_separated_boxes_no_intersect) {
    ConvexHull a = boxHull({0,0,0}, 1.0);
    ConvexHull b = boxHull({3,0,0}, 1.0); // separated along x-axis
    Simplex s;
    CHECK(!gjkIntersect(a, b, s), "GJK should detect no intersection for separated boxes");
}
// Unit test for GJK with barely overlapping boxes
TEST("GJK_tiny_overlap_boxes_intersect", gjk_tiny_overlap_boxes_intersect) {
    ConvexHull a = boxHull({0,0,0}, 1.0);
    ConvexHull b = boxHull({1.9,0,0}, 1.0); // barely overlapping along x-axis
    Simplex s;
    CHECK(gjkIntersect(a, b, s), "GJK should detect intersection for barely overlapping boxes");
}

// Unit test for EPA with known overlapping boxes
TEST("EPA_penetration_depth_and_normal_for_known_overlap", epa_penetration_depth_and_normal_for_known_overlap) {
    ConvexHull a = boxHull({0,0,0}, 1.0);
    ConvexHull b = boxHull({1.5,0,0}, 1.0); // known overlap along x-axis
    ContactManifold m;
    bool hit = convexConvex(a, b, m);
    CHECK(hit, "EPA should detect intersection for known overlapping boxes");
    // Norm should be ~ (-1,0,0) and depth ~ 0.5
    CHECK(std::abs(std::abs(m.normal.x()) - 1.0) < 1e-2, "EPA normal x-component should be close to -1");
    double depth = (m.pointCount > 0) ? m.points[0].depth : -1.0;
    CHECK(std::abs(depth - 0.5) < 5e-2, "EPA penetration depth should be close to 0.5");
}

// Unit test for Convex Hull building with cube corners and interior points
TEST("ConvexHull_buildHull_8_cube_corners_and_interior_points", convexHull_buildHull_8_cube_corners_and_interior_points) {
    std::vector<mathlib::Vec3> pts;
    for (int i=0; i < 8; ++i) {
        pts.push_back(mathlib::Vec3(
            (i & 1)?1.0:-1.0,
            (i & 2)?1.0:-1.0,
            (i & 4)?1.0:-1.0
        ));
    }
    pts.push_back({0,0,0});
    pts.push_back({0.2,0.1,0});
    ConvexHull h = buildHull(pts);
    CHECK(h.verts.size() == 8, "Convex hull of cube corners and interior points should have 8 vertices");
}
// Unit test for Convex Hull building with degenerate colinear points (less than 4)
TEST("ConvexHull_buildHull_degenerate_colinear_points", convexHull_buildHull_degenerate_colinear_points) {
    std::vector<mathlib::Vec3> pts = {{0,0,0}, {1,0,0}, {0,1,0}};
    ConvexHull h = buildHull(pts);
    CHECK(h.verts.size() == 3, "Convex hull of 3 non-colinear points should have 3 vertices");
}
// Unit test for hull vs hull through built hulls (not just boxes)
TEST("ConvexHull_hull_vs_hull_through_built_hulls", convexHull_buildHull_hull_vs_hull_through_built_hulls) {
    std::vector<mathlib::Vec3> ca, cb;
    for (int i=0; i < 8; ++i) {
        ca.push_back(mathlib::Vec3(
            (i & 1)?1.0:-1.0,
            (i & 2)?1.0:-1.0,
            (i & 4)?1.0:-1.0
        ));
        cb.push_back(mathlib::Vec3(
            (i & 1)?1.0:-1.0,
            (i & 2)?1.0:-1.0,
            (i & 4)?1.0:-1.0
        ) + mathlib::Vec3(1.5,0,0));
    }
    ConvexHull ha = buildHull(ca), hb = buildHull(cb);
    ContactManifold m;
    CHECK(convexConvex(ha, hb, m), "Convex hulls of two cubes should intersect");
}