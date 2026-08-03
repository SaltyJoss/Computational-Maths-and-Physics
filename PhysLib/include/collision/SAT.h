/*
 * File: PhysLib/include/collision/SAT.h
 * Separating Axis Theorem (SAT) for collision detection.
 * Created by: Joss Salton, 03-08-2026
 */
#ifndef PHYSICS_COLLISION_SAT_H
#define PHYSICS_COLLISION_SAT_H

#pragma once
#include "collision/OBB.h"
#include "collision/contact.h"
#include <limits>
#include <cmath>

namespace physlib::collision {
    // Project OBB onto a world-space unit axis -> radius of the projection (half-width of shadow)
    inline double projectRadius(const OBB& b, const mathlib::Vec3& axis) {
        return std::abs(b.halfExtents.x() * mathlib::dot(axis, b.axis(0))) +
               std::abs(b.halfExtents.y() * mathlib::dot(axis, b.axis(1))) +
               std::abs(b.halfExtents.z() * mathlib::dot(axis, b.axis(2)));
    }
    // Separating Axis Theorem (SAT) for OBB-OBB collision detection
    inline bool SAT_OBB(const OBB& a, const OBB& b, ContactManifold& manifold) {
        mathlib::Vec3 d = b.centre - a.centre; // Vector from A to B
        double minPen = std::numeric_limits<double>::max();
        mathlib::Vec3 minAxis;
        bool hasAxis = false;
        
        auto testAxis = [&](mathlib::Vec3 axis) -> bool {
            const double len2 = axis.squaredNorm();
            if (len2 < 1e-12) { return true; } // Skip near-zero
            axis /= mathlib::sqrt(len2); // Normalize axis
            double r_a = projectRadius(a, axis);
            double r_b = projectRadius(b, axis);
            double dist = std::abs(mathlib::dot(d, axis));
            double pen = (r_a + r_b) - dist; // 
            if (pen < 0) { return false; } // Found a separating axis
            if (pen < minPen) {
                minPen = pen;
                minAxis = (d.dot(axis) < 0.0) ? -axis : axis; // Ensure normal points from A to B
                hasAxis = true;
            }
            return true;
        };

        for (int i = 0; i < 3; ++i) { if (!testAxis(a.axis(i))) { return false; } }
        for (int i = 0; i < 3; ++i) { if (!testAxis(b.axis(i))) { return false; } }
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (!testAxis(a.axis(i).cross(b.axis(j)))) { return false; }
            }
        }
        if (!hasAxis) { return false; }
        manifold.hit = true;
        manifold.normal = minAxis;
        manifold.toi = 0.0;
        // This is for the first cube-cube resolution (so a single representative point at the overlap centroiud is enough)
        return true;
    }
} // namespace physlib::collision

#endif