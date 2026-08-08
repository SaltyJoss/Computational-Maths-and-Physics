/*
 * File: PhysLib/include/collision/contact.h
 * Contact manifold produced by narrowphase.
 * Created by: Joss Salton, 03-08-2026
 */
#pragma once

#ifndef PHYSICS_COLLISION_CONTACT_H
#define PHYSICS_COLLISION_CONTACT_H

#include <MathLib>
#include <array>
#include <cstdint>

namespace physlib::collision {
    // Contact point struct
    struct ContactPoint {
        mathlib::Vec3 pos; // World-space contact point
        double depth; // penetration depth
    };
    // Contact Manifold struct 
    struct ContactManifold {
        bool hit = false;
        mathlib::Vec3 normal;
        double toi = 0.0;
        int pointCount = 0;
        std::array<ContactPoint, 4> points; // up to 4 contact points (for box-box collisions)
        // Add a contact point to the manifold (up to 4 points)
        void addPoint(const mathlib::Vec3& p, double d) {
            if (pointCount < 4) { points[pointCount++] = { p, d }; }
        }
    };
} // namespace physlib::collision

#endif