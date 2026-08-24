/*
 * File: PhysLib/include/collision/convex_hull.h
 * Convex hull representation for collision detection.
 * Created by: Joss Salton, 03-08-2026
 */
#pragma once

#include <MathLib>
#include <vector>

namespace physlib::collision {
    // Convex Hull struct
    struct ConvexHull {
        std::vector<mathlib::Vec3> verts;
        mathlib::Vec3 support(const mathlib::Vec3& d) const {
            double best = -std::numeric_limits<double>::infinity();
            mathlib::Vec3 bestV = mathlib::Vec3::Zero();
            for (const auto& v : verts) {
                const double p = v.dot(d);
                if (p > best) { best = p; bestV = v; }
            }
            return bestV;
        }
        // Compute the centroid of the convex hull
        mathlib::Vec3 centroid() const {
            mathlib::Vec3 c = mathlib::Vec3::Zero();
            for (const auto& v : verts) { c += v; }
            return verts.empty() ? c : (c / double(verts.size()));
        }
    };
    // Minkowski-difference support (A - B) along d: support of the CSO GJK walks
    inline mathlib::Vec3 supportCSO(const ConvexHull& A, const ConvexHull& B, const mathlib::Vec3& d) {
        return A.support(d) - B.support(-d);
    }
} // namespace physlib::collision
