/*
 * File: PhysLib/include/collision/capsule.h
 * Capsule primitive (meaning segment & radius) for collision detection. -> PURELY geometrical
 * Created by: Joss Salton, 10-08-2026 
 */
#pragma once

#ifndef PHYSICS_COLLISION_CAPSULE_H
#define PHYSICS_COLLISION_CAPSULE_H

#include <MathLib>
#include "collision/contact.h"

namespace physlib::collision {
    // Capsule struct to represent a capsule primitive in 3D space
    struct Capsule {
        mathlib::Vec3 a; // One end of the capsule segment
        mathlib::Vec3 b; // Other end of the capsule segment
        double radius;    // Radius of the capsule

        mathlib::Vec3 axis()  const { return b - a; } // spine direction (b - a)
        mathlib::Vec3 centre() const { return 0.5 * (a + b); } // centre of the capsule
    };
    
    // Computes the closest points between two segments (p1, q1) and (p2, q2)
    inline double closestPtSegmentSegment(
        const mathlib::Vec3& p1, const mathlib::Vec3& q1,
        const mathlib::Vec3& p2, const mathlib::Vec3& q2,
        double& s, double& t, mathlib::Vec3& c1, mathlib::Vec3& c2
    ) {
        // Compute the direction vectors of the segments
        const mathlib::Vec3 d1 = q1 - p1; // Direction vector of segment S1
        const mathlib::Vec3 d2 = q2 - p2; // Direction vector of segment S2
        const mathlib::Vec3 r  = p1 - p2; // Vector from S2 to S1
        const double a = d1.dot(d1);
        const double e = d2.dot(d2);
        const double f = d2.dot(r);
        constexpr double eps = 1e-12;
        // Check if either segment is degenerate (length is zero)
        if (a <= eps && e <= eps) {
            s=t=0.0; c1=p1; c2=p2; return (c1 - c2).squaredNorm();
        }
        if (a <= eps) {
            s = 0.0;
            t = std::clamp(f / e, 0.0, 1.0);
        } else {
            const double c = d1.dot(r);
            if (e <= eps) {
                t = 0.0;
                s = std::clamp(-c / a, 0.0, 1.0);
            } else {
                const double b = d1.dot(d2);
                const double denom = a * e - b * b;
                if (denom > eps) { s = std::clamp((b * f - c * e) / denom, 0.0, 1.0); } // Compute s to minimize the distance
                else { s = 0.0; /* Parallel segments */ }
                t = (b * s + f) / e; // Compute t to minimize the distance
                if (t < 0.0) { t = 0.0; s = std::clamp(-c / a, 0.0, 1.0); } // Clamp t to [0,1]
                else if (t > 1.0) { t = 1.0; s = std::clamp((b - c) / a, 0.0, 1.0); } // Clamp t to [0,1]
            }
        }
        c1 = p1 + d1 * s; // Closest point on segment S1
        c2 = p2 + d2 * t; // Closest point on segment S
        return (c1 - c2).squaredNorm(); // Return the squared distance between the closest points
    }
    // Computes the contact manifold between two capsules A and B
    inline bool capsuleCapsule(const Capsule& A, const Capsule& B, ContactManifold& m) {
        double s, t;
        mathlib::Vec3 c1, c2;
        // Compute the squared distance between the closest points on the capsule segments
        double d2 = closestPtSegmentSegment(A.a, A.b, B.a, B.b, s, t, c1, c2);
        double rSum = A.radius + B.radius;
        if (d2 > rSum * rSum) { return false; }
        const double d = std::sqrt(d2);
        // Compute the contact normal and penetration depth
        mathlib::Vec3 norm;
        if (d > 1e-9) { norm = (c2 - c1) / d; } // A -> B
        else { norm = mathlib::Vec3(0, 1, 0); } // Arbitrary normal if the capsules are overlapping
        m.hit = true;
        m.normal = norm;
        m.toi = 0.0;
        const double depth = rSum - d;
        // Contact point on capsule A
        const mathlib::Vec3 contact = c1 + norm * A.radius;
        m.addPoint(contact, depth); // Add the contact point to the manifold
        return true;
    }

} // namespace physlib::collision

#endif 