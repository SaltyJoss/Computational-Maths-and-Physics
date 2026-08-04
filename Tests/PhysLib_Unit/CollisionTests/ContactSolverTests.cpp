/*
 * File: Tests/PhysLib_Unit/CollisionTests/ContactTests.cpp
 * Unit tests for the Contact Manifold and contact point generation.
 * Created by: Joss Salton, 03-08-2026
 */
#include "TestHarness.h"
#include "collision/contact_solver.h"

TEST("solveNormalImpulse_separating", solveNormalImpulse_separating) {
    mathlib::Vec3 normal(0.0, 1.0, 0.0);
    mathlib::Vec3 relVelAtContact(0.0, 1.0, 0.0); // Moving away
    double effectiveMass = 1.0;
    double restitution = 0.5;
    double impulse = mathlib::collision::solveNormalImpulse(normal, relVelAtContact, effectiveMass, restitution);
    ASSERT_TRUE(impulse == 0.0, "Impulse should be zero for separating contact");
}
TEST("solveNormalImpulse_approaching", solveNormalImpulse_approaching) {
    mathlib::Vec3 normal(0.0, 1.0, 0.0);
    mathlib::Vec3 relVelAtContact(0.0, -1.0, 0.0); // Approaching
    double effectiveMass = 2.0;
    double restitution = 0.5;
    double impulse = mathlib::collision::solveNormalImpulse(normal, relVelAtContact, effectiveMass, restitution);
    double expectedImpulse = (-(1.0 + restitution) * relVelAtContact.dot(normal)) / effectiveMass;
    ASSERT_TRUE(std::abs(impulse - expectedImpulse) < 1e-6, "Impulse should match expected value for approaching contact");
}
TEST("solveNormalImpulse_zero_effective_mass", solveNormalImpulse_zero_effective_mass) {
    mathlib::Vec3 normal(0.0, 1.0, 0.0);
    mathlib::Vec3 relVelAtContact(0.0, -1.0, 0.0); // Approaching
    double effectiveMass = 0.0; // Zero effective mass
    double restitution = 0.5;
    double impulse = mathlib::collision::solveNormalImpulse(normal, relVelAtContact, effectiveMass, restitution);
    ASSERT_TRUE(impulse == 0.0, "Impulse should be zero for zero effective mass");
}

TEST("solveFrictionImpulse_within_limit", solveFrictionImpulse_within_limit) {
    mathlib::Vec3 tangentDir(1.0, 0.0, 0.0);
    mathlib::Vec3 relVelAtContact(1.0, 0.0, 0.0); // Sliding along tangent
    double effectiveMassT = 2.0;
    double normalImpulse = 1.0;
    double mu = 0.5; // Friction coefficient
    mathlib::Vec3 frictionImpulse = mathlib::collision::solveFrictionImpulse(tangentDir, relVelAtContact, effectiveMassT, normalImpulse, mu);
    double jt = -relVelAtContact.dot(tangentDir) / effectiveMassT;
    double jt_max = mu * normalImpulse;
    jt = std::clamp(jt, -jt_max, jt_max);
    mathlib::Vec3 expectedImpulse = jt * tangentDir;
    ASSERT_TRUE((frictionImpulse - expectedImpulse).norm() < 1e-6, "Friction impulse should match expected value within limit");
}
TEST("solveFrictionImpulse_exceeds_limit", solveFrictionImpulse_exceeds_limit) {
    mathlib::Vec3 tangentDir(1.0, 0.0, 0.0);
    mathlib::Vec3 relVelAtContact(10.0, 0.0, 0.0); // High sliding velocity
    double effectiveMassT = 1.0;
    double normalImpulse = 1.0;
    double mu = 0.5; // Friction coefficient
    mathlib::Vec3 frictionImpulse = mathlib::collision::solveFrictionImpulse(tangentDir, relVelAtContact, effectiveMassT, normalImpulse, mu);
    double jt_max = mu * normalImpulse;
    mathlib::Vec3 expectedImpulse = -jt_max * tangentDir; // Should be clamped to max
    ASSERT_TRUE((frictionImpulse - expectedImpulse).norm() < 1e-6, "Friction impulse should be clamped to maximum limit");
}
TEST("solveFrictionImpulse_zero_effective_mass", solveFrictionImpulse_zero_effective_mass) {
    mathlib::Vec3 tangentDir(1.0, 0.0, 0.0);
    mathlib::Vec3 relVelAtContact(1.0, 0.0, 0.0); // Sliding along tangent
    double effectiveMassT = 0.0; // Zero effective mass
    double normalImpulse = 1.0;
    double mu = 0.5; // Friction coefficient
    mathlib::Vec3 frictionImpulse = mathlib::collision::solveFrictionImpulse(tangentDir, relVelAtContact, effectiveMassT, normalImpulse, mu);
    ASSERT_TRUE(frictionImpulse == mathlib::Vec3::Zero(), "Friction impulse should be zero for zero effective mass");
}
TEST("solveFrictionImpulse_zero_normal_impulse", solveFrictionImpulse_zero_normal_impulse) {
    mathlib::Vec3 tangentDir(1.0, 0.0, 0.0);
    mathlib::Vec3 relVelAtContact(1.0, 0.0, 0.0); // Sliding along tangent
    double effectiveMassT = 1.0;
    double normalImpulse = 0.0; // Zero normal impulse
    double mu = 0.5; // Friction coefficient
    mathlib::Vec3 frictionImpulse = mathlib::collision::solveFrictionImpulse(tangentDir, relVelAtContact, effectiveMassT, normalImpulse, mu);
    ASSERT_TRUE(frictionImpulse == mathlib::Vec3::Zero(), "Friction impulse should be zero for zero normal impulse");
}
TEST("solveFrictionImpulse_zero_relative_velocity", solveFrictionImpulse_zero_relative_velocity) {
    mathlib::Vec3 tangentDir(1.0, 0.0, 0.0);
    mathlib::Vec3 relVelAtContact(0.0, 0.0, 0.0); // No relative motion
    double effectiveMassT = 1.0;
    double normalImpulse = 1.0;
    double mu = 0.5; // Friction coefficient
    mathlib::Vec3 frictionImpulse = mathlib::collision::solveFrictionImpulse(tangentDir, relVelAtContact, effectiveMassT, normalImpulse, mu);
    ASSERT_TRUE(frictionImpulse == mathlib::Vec3::Zero(), "Friction impulse should be zero for zero relative velocity");
}
TEST("solveFrictionImpulse_negative_relative_velocity", solveFrictionImpulse_negative_relative_velocity) {
    mathlib::Vec3 tangentDir(1.0, 0.0, 0.0);
    mathlib::Vec3 relVelAtContact(-1.0, 0.0, 0.0); // Sliding in opposite direction
    double effectiveMassT = 2.0;
    double normalImpulse = 1.0;
    double mu = 0.5; // Friction coefficient
    mathlib::Vec3 frictionImpulse = mathlib::collision::solveFrictionImpulse(tangentDir, relVelAtContact, effectiveMassT, normalImpulse, mu);
    double jt = -relVelAtContact.dot(tangentDir) / effectiveMassT;
    double jt_max = mu * normalImpulse;
    jt = std::clamp(jt, -jt_max, jt_max);
    mathlib::Vec3 expectedImpulse = jt * tangentDir;
    ASSERT_TRUE((frictionImpulse - expectedImpulse).norm() < 1e-6, "Friction impulse should match expected value for negative relative velocity");
}
TEST("solveFrictionImpulse_zero_friction_coefficient", solveFrictionImpulse_zero_friction_coefficient) {
    mathlib::Vec3 tangentDir(1.0, 0.0, 0.0);
    mathlib::Vec3 relVelAtContact(1.0, 0.0, 0.0); // Sliding along tangent
    double effectiveMassT = 1.0;
    double normalImpulse = 1.0;
    double mu = 0.0; // Zero friction coefficient
    mathlib::Vec3 frictionImpulse = mathlib::collision::solveFrictionImpulse(tangentDir, relVelAtContact, effectiveMassT, normalImpulse, mu);
    ASSERT_TRUE(frictionImpulse == mathlib::Vec3::Zero(), "Friction impulse should be zero for zero friction coefficient");
}
TEST("solveFrictionImpulse_negative_friction_coefficient", solveFrictionImpulse_negative_friction_coefficient) {
    mathlib::Vec3 tangentDir(1.0, 0.0, 0.0);
    mathlib::Vec3 relVelAtContact(1.0, 0.0, 0.0); // Sliding along tangent
    double effectiveMassT = 1.0;
    double normalImpulse = 1.0;
    double mu = -0.5; // Negative friction coefficient (non-physical)
    mathlib::Vec3 frictionImpulse = mathlib::collision::solveFrictionImpulse(tangentDir, relVelAtContact, effectiveMassT, normalImpulse, mu);
    ASSERT_TRUE(frictionImpulse == mathlib::Vec3::Zero(), "Friction impulse should be zero for negative friction coefficient");
}
TEST("solveFrictionImpulse_large_relative_velocity", solveFrictionImpulse_large_relative_velocity) {
    mathlib::Vec3 tangentDir(1.0, 0.0, 0.0);
    mathlib::Vec3 relVelAtContact(100.0, 0.0, 0.0); // Very high sliding velocity
    double effectiveMassT = 1.0;
    double normalImpulse = 1.0;
    double mu = 0.5; // Friction coefficient
    mathlib::Vec3 frictionImpulse = mathlib::collision::solveFrictionImpulse(tangentDir, relVelAtContact, effectiveMassT, normalImpulse, mu);
    double jt_max = mu * normalImpulse;
    mathlib::Vec3 expectedImpulse = jt_max * tangentDir; // Should be clamped to max
    ASSERT_TRUE((frictionImpulse - expectedImpulse).norm() < 1e-6, "Friction impulse should be clamped to maximum limit for large relative velocity");
}