/*
 * File: PhysLib/include/collision/EPA.h
 * Implementation of the EPA (Expanding Polytope Algorithm) for computing penetration depth and contact normals between convex shapes.
 * Created by: Joss Salton, 03-08-2026
 */
#pragma once

#include "GJK.h"
#include "contact.h"
#include <vector>

namespace physlib::collision {
    inline bool epaPenetration(const ConvexHull& A, const ConvexHull& B, Simplex& simplex, mathlib::Vec3& normal_out, double& depth_out) {
        std::vector<mathlib::Vec3> poly(simplex.pts.begin(), simplex.pts.begin() + simplex.count);
        if (poly.size() < 4) { return false; } // EPA only works with tetrahedra

        auto tetVolume = [&](const std::vector<mathlib::Vec3>& p) -> double {
            if (p.size() < 4) { return 0.0; }
            return std::abs((p[1]-p[0]).dot((p[2]-p[0]).cross(p[3]-p[0]))) / 6.0; // Volume of tetrahedron
        };
        if (tetVolume(poly) < 1e-10) {
            const mathlib::Vec3 dirs[6] = {{1,0,0}, {-1,0,0}, {0,1,0}, {0,-1,0}, {0,0,1}, {0,0,-1}};
            for (int k = 0; k < 6; ++k) {
                mathlib::Vec3 p = supportCSO(A, B, dirs[k]);
                std::vector<mathlib::Vec3> test = { poly[0], poly[1], poly[2], p };
                if (tetVolume(test) > 1e-10) { poly = test; break; }
            }
            if (tetVolume(poly) < 1e-10) { return false; } // Still degenerate
        }

        struct Face {
            int a, b, c;
            mathlib::Vec3 n;
            double dist;
        };
        auto polyCentroid = [&]() {
            mathlib::Vec3 c = mathlib::Vec3::Zero();
            for (auto& p : poly) { c += p; }
            return c / double(poly.size());
        };
        auto makeFace = [&](int a, int b, int c) {
            mathlib::Vec3 n = (poly[b] - poly[a]).cross(poly[c] - poly[a]);
            if (n.norm() < 1e-12) { n = mathlib::Vec3(0.0, 0.0, 1.0); }
            else { n.normalize(); }
            double d = n.dot(poly[a]);
            const mathlib::Vec3 centre = polyCentroid();
            if (n.dot(centre) - d > 0) {
                n = -n;
                d = -d;
                std::swap(b, c);
            }
            return Face{a, b, c, n, d};
        };
        std::vector<Face> faces = {
            makeFace(0, 1, 2),
            makeFace(0, 2, 3),
            makeFace(0, 3, 1),
            makeFace(1, 3, 2)
        };
        for (int iter = 0; iter < 64; ++iter) {
            int closest = 0;
            for (int i = 1; i < faces.size(); ++i) {
                if (faces[i].dist < faces[closest].dist) { closest = i; }
            }
            const mathlib::Vec3 n = faces[closest].n;
            const mathlib::Vec3 sup = supportCSO(A, B, n);
            const double d = sup.dot(n);
            if (d - faces[closest].dist < 1e-4) {
                normal_out = n;
                depth_out = faces[closest].dist;
                return true;
            }
            std::vector<std::pair<int, int>> edges;
            auto addEdge = [&](int a, int b) {
                auto it = std::find(edges.begin(), edges.end(), std::make_pair(b, a));
                if (it != edges.end()) { edges.erase(it); }
                else { edges.emplace_back(a, b); }
            };
            for (int i = (int)faces.size() - 1; i >= 0; --i) {
                if (faces[i].n.dot(sup - poly[faces[i].a]) > 0) {
                    addEdge(faces[i].a, faces[i].b);
                    addEdge(faces[i].b, faces[i].c);
                    addEdge(faces[i].c, faces[i].a);
                    faces.erase(faces.begin() + i);
                }
            }
            int newIdx = (int)poly.size();
            poly.push_back(sup);
            for (auto& e : edges) {
                faces.push_back(makeFace(e.first, e.second, newIdx));
            }
        }
        if (faces.empty()) {
            normal_out - mathlib::Vec3(0, 1, 0);
            depth_out = 0.0;
            return false;
        }
        int closest = 0;
        for (int i = 1; i < faces.size(); ++i) {
            if (faces[i].dist < faces[closest].dist) { closest = i; }
        }
        normal_out = faces[closest].n;
        depth_out = faces[closest].dist;
        return true;
    }
    //
    inline bool convexConvex(const ConvexHull& A, const ConvexHull& B, ContactManifold& m) {
        Simplex s;
        if (!gjkIntersect(A, B, s)) { return false; }
        mathlib::Vec3 n;
        double depth;
        if (!epaPenetration(A, B, s, n, depth)) { return false; }
        m.hit = true;
        m.normal = n;
        const mathlib::Vec3 contact = B.support(-n);
        m.addPoint(contact, depth);
        return true;
    }
} // namespace physlib::collision