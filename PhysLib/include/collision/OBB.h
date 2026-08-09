/*
 * File: PhysLib/include/collision/OBB.h
 * Oriented Bounding Box (OBB) AND axis-Aligned Bounding Box (AABB) class for collision detection.
 * Current state is PURE geometry, double-only (collision detection is NOT differentiated)
 * Created by: Joss Salton, 03-08-2026
 */
#pragma once

#ifndef PHYSICS_COLLISION_OBB_H
#define PHYSICS_COLLISION_OBB_H

#include <MathLib>

namespace physlib::collision {
    // Axis-Aligned Bounding Box (AABB) in some frame (local OR world). Min/max corners
    struct AABB {
        mathlib::Vec3 min;
        mathlib::Vec3 max;
        mathlib::Vec3 centre() const { return 0.5 * (min + max); }
        mathlib::Vec3 halfExtents() const { return 0.5 * (max - min); }
    };

    struct OBB {
        mathlib::Vec3 centre; // centre of the box
        mathlib::Vec3 halfExtents; // half extents along each axis
        mathlib::Mat3 orientation; // rotation matrix representing the orientation of the box
        mathlib::Vec3 axis(int i) const { return orientation.col(i); } // get the i-th axis of the box
        // Create an OBB from an AABB, given a rotation matrix R and translation vector t
        static OBB fromAABB(const AABB& box, const mathlib::Mat3& R, const mathlib::Vec3& t) {
            OBB o;
            o.centre = t + R * box.centre(); // world centre = translation + rotated local centre
            o.halfExtents = box.halfExtents(); // half extents are a SIZE vector, never transformed or translated
            o.orientation = R; // Set the orientation of the OBB to the given rotation matrix
            return o;
        }
    };
} // namespace physlib::collision

#endif