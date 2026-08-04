/*
 * File: PhysLib/include/collision/contact_solver.h
 * Contact solver for collision resolution.
 * Created by: Joss Salton, 03-08-2026
 */
#ifndef PHYSICS_COLLISION_CONTACT_SOLVER_H
#define PHYSICS_COLLISION_CONTACT_SOLVER_H

#pragma once
#include <MathLib>
#include <algorithm>
#include <cmath>

namespace mathlib::collision {
    // Contact Impulse struct to store normal and tangent impulses
    struct ContactImpulse {
        double normalImpulse = 0.0;
        mathlib::Vec3 tangentImpulse = mathlib::Vec3::Zero();
    };
    // Solve Normal Impulse using the effective mass and restitution
    inline double solveNormalImpulse(
        const mathlib::Vec3& normal,
        const mathlib::Vec3& relVelAtContract,
        double effectiveMass, // = n^T * M^-1 * n -> where M^-1 = (K_a + K_b)
        double restitution
    ) {
        const double vRelN = relVelAtContract.dot(normal);
        if (vRelN > 0.0) { return 0.0; } // Already separating
        if (effectiveMass < 1e-12) { return 0.0; } // Avoid division by zero
        const double desiredDeltaV = -(1.0 + restitution) * vRelN; // target post-impulse normal velocity = -restitution * approach
        double j = desiredDeltaV / effectiveMass;
        return std::max(0.0, j); // Impulse cannot be negative
    }
    // Solve Friction Impulse using Coulomb's law: |jt| <= mu * jn
    inline mathlib::Vec3 solveFrictionImpulse(
        const mathlib::Vec3& tangentDir,
        const mathlib::Vec3& relVelAtContact,
        double effectiveMassT, // n^T(K)n along tangent
        double normalImpulse,
        double mu
    ) {
        if (effectiveMassT < 1e-12) { return mathlib::Vec3::Zero(); }
        if (mu <= 0.0 || normalImpulse <= 0.0) { return mathlib::Vec3::Zero(); }  // no friction cone
        const double vRelT = relVelAtContact.dot(tangentDir);
        double jt = -vRelT / effectiveMassT;
        const double jt_max = mu * normalImpulse;   // now guaranteed >= 0
        jt = std::clamp(jt, -jt_max, jt_max);
        return jt * tangentDir;
    }
} // namespace mathlib::collision

#endif