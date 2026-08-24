/*
 * File: PhysLib/include/collision/GJK.h
 * Implementation of the GJK (Gilbert-Johnson-Keerthi) algorithm for collision detection between convex shapes.
 * Created by: Joss Salton, 03-08-2026
 */
#pragma once

#include "convex_hull.h"
#include <array>

namespace physlib::collision {
    //
    struct Simplex {
        std::array<mathlib::Vec3, 4> pts;
        int count = 0;
        void push_front(const mathlib::Vec3& p) {
            for (int i = count; i > 0; --i) { pts[i] = pts[i - 1]; }
            pts[0] = p;
            count = std::min(count + 1, 4);
        }
    };
    //
    inline bool sameDirection(const mathlib::Vec3& a, const mathlib::Vec3& b) { return a.dot(b) > 0.0; }
    //
    inline bool doLine(Simplex& s, mathlib::Vec3& dir) {
        const mathlib::Vec3 a = s.pts[0], b = s.pts[1];
        const mathlib::Vec3 ab = b - a, ao = -a;
        if (sameDirection(ab, ao)) { dir = ab.cross(ao).cross(ab); }
        else {
            s = {};
            s.pts[0] = a;
            s.count = 1;
            dir = ao;
        }
    }
    //
    inline bool doTriangle(Simplex& s, mathlib::Vec3& dir) {
        const mathlib::Vec3 a = s.pts[0], b = s.pts[1], c = s.pts[2];
        const mathlib::Vec3 ab = b - a, ac = c - a, ao = -a;
        const mathlib::Vec3 abc = ab.cross(ac);
        if (sameDirection(abc.cross(ac), ao)) {
            if (sameDirection(ac, ao)) {
                s = {a, c};
                s.count = 2;
                dir = ac.cross(ao).cross(ac);
            } else {
                s = {a, b};
                s.count = 2;
                return doLine(s, dir);
            }
        } else if (sameDirection(ab.cross(abc), ao)) {
            s.pts = {a, b};
            s.count = 2;
            return doLine(s, dir);
        } else if (sameDirection(abc, ao)) {
            dir = abc;
        } else {
            s = {a, c, b};
            s.count = 3;
            dir = -abc;
        }
        return false;
    }
    // 
    inline bool doTetrahedron(Simplex& s, mathlib::Vec3& dir) {
        const mathlib::Vec3 a = s.pts[0], b = s.pts[1], c = s.pts[2], d = s.pts[3];
        const mathlib::Vec3 ab = b - a, ac = c - a, ad = d - a, ao = -a;
        const mathlib::Vec3 abc = ab.cross(ac), acd = ac.cross(ad), adb = ad.cross(ab);
        if (sameDirection(abc, ao)) {
            s.pts = {a, b, c};
            s.count = 3;
            return doTriangle(s, dir);
        }
        if (sameDirection(acd, ao)) {
            s.pts = {a, c, d};
            s.count = 3;
            return doTriangle(s, dir);
        }
        if (sameDirection(adb, ao)) {
            s.pts = {a, d, b};
            s.count = 3;
            return doTriangle(s, dir);
        }
    }
    // The next simplex function updates the simplex and direction based on the current simplex configuration.
    inline bool nextSimplex(Simplex& s, mathlib::Vec3& dir) {
        switch (s.count) {
            case 2: return doLine(s, dir);
            case 3: return doTriangle(s, dir);
            case 4: return doTetrahedron(s, dir);
        }
        return false;
    }
    // Intersection test using GJK algorithm. Returns true if the convex hulls A and B intersect, false otherwise. If they intersect, the simplex is returned in out.
    inline bool gjkIntersect(const ConvexHull& A, const ConvexHull& B, Simplex& out) {
        mathlib::Vec3 dir (1, 0, 0);
        mathlib::Vec3 sup = supportCSO(A, B, dir);
        Simplex s;
        s.push_front(sup);
        dir = -sup;
        for (int iter = 0; iter < 64; ++iter) {
            sup = supportCSO(A, B, dir);
            if (sup.dot(dir) < 0.0) { return false; } // zero intersection
            s.push_front(sup);
            if (nextSimplex(s, dir)) { out = s; return true; } // intersection
        }
        out = s;
        return false;
    }
} // namespace physlib::collision