/*
 * File: PhysLib/include/collision/convex_hull_build.h
 * Implementation of the convex hull building algorithm for collision detection. Uses incremental quickhull algorithm to construct the convex hull from a set of points in 3D space.
 * Created by: Joss Salton, 03-08-2026
 */
#pragma once

#include "convex_hull.h"
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>

namespace physlib::collision {
    //
    namespace qh_detail {

        struct Face {
            std::array<int, 3> v;        // vertex indices (into the working point list), CCW seen from outside
            mathlib::Vec3 normal;        // outward unit normal
            double offset;               // normal.dot(v0)  (plane: normal.x = offset)
            std::vector<int> outside;    // indices of points in front of this face
            bool dead = false;           // marked for removal
        };

        inline double pointFaceDist(const mathlib::Vec3& p, const Face& f) {
            return f.normal.dot(p) - f.offset;   // >0 => in front (outside)
        }

        // Build a face from 3 point indices, orienting the normal AWAY from an interior reference point.
        inline Face makeFace(int a, int b, int c,
                             const std::vector<mathlib::Vec3>& pts,
                             const mathlib::Vec3& interior) {
            Face f; f.v = {a, b, c};
            mathlib::Vec3 n = (pts[b] - pts[a]).cross(pts[c] - pts[a]);
            const double len = n.norm();
            n = (len > 1e-20) ? (n / len) : mathlib::Vec3(0, 0, 1);
            double off = n.dot(pts[a]);
            // flip so the interior point is BEHIND the face (dist < 0)
            if (n.dot(interior) - off > 0.0) { n = -n; off = -off; std::swap(f.v[1], f.v[2]); }
            f.normal = n; f.offset = off;
            return f;
        }

    } // namespace qh_detail

    // Build a convex hull from arbitrary mesh vertices.
    inline ConvexHull buildHull(const std::vector<mathlib::Vec3>& meshVerts) {
        using namespace qh_detail;
        ConvexHull result;
        const int N = (int)meshVerts.size();
        if (N < 4) { result.verts = meshVerts; return result; }   // degenerate: return as-is

        const std::vector<mathlib::Vec3>& P = meshVerts;

        // --- 1. Initial tetrahedron: extreme points along x, then farthest from line, then from plane ---
        int i0 = 0, i1 = 0;
        {
            int minx = 0, maxx = 0;
            for (int i = 1; i < N; ++i) {
                if (P[i].x() < P[minx].x()) minx = i;
                if (P[i].x() > P[maxx].x()) maxx = i;
            }
            i0 = minx; i1 = maxx;
            if (i0 == i1) { result.verts = meshVerts; return result; }   // all coincident in x
        }
        // farthest point from line i0-i1
        int i2 = -1; { double best = -1; mathlib::Vec3 e = (P[i1] - P[i0]);
            double el = e.norm(); if (el < 1e-20) { result.verts = meshVerts; return result; } e /= el;
            for (int i = 0; i < N; ++i) {
                double d = ((P[i] - P[i0]) - e * (P[i] - P[i0]).dot(e)).norm();
                if (d > best) { best = d; i2 = i; }
            }
            if (best < 1e-12) { result.verts = meshVerts; return result; }   // colinear
        }
        // farthest point from plane (i0,i1,i2)
        int i3 = -1; { mathlib::Vec3 n = (P[i1]-P[i0]).cross(P[i2]-P[i0]);
            double nl = n.norm(); if (nl < 1e-20) { result.verts = meshVerts; return result; } n /= nl;
            double best = -1;
            for (int i = 0; i < N; ++i) {
                double d = std::abs(n.dot(P[i] - P[i0]));
                if (d > best) { best = d; i3 = i; }
            }
            if (best < 1e-12) { result.verts = meshVerts; return result; }   // coplanar
        }

        const mathlib::Vec3 interior = 0.25 * (P[i0] + P[i1] + P[i2] + P[i3]);

        std::vector<Face> faces;
        faces.push_back(makeFace(i0, i1, i2, P, interior));
        faces.push_back(makeFace(i0, i1, i3, P, interior));
        faces.push_back(makeFace(i0, i2, i3, P, interior));
        faces.push_back(makeFace(i1, i2, i3, P, interior));

        // assign each point to the first face it's outside of
        auto assignOutside = [&](std::vector<Face>& fs) {
            for (int i = 0; i < N; ++i) {
                for (auto& f : fs) {
                    if (f.dead) continue;
                    if (pointFaceDist(P[i], f) > 1e-10) { f.outside.push_back(i); break; }
                }
            }
        };
        assignOutside(faces);

        // --- 2. Iteratively add the farthest outside point, re-triangulate the horizon ---
        for (int guard = 0; guard < 100000; ++guard) {
            // find a face with outside points; pick its farthest point
            int fIdx = -1, apex = -1; double bestDist = 1e-10;
            for (int fi = 0; fi < (int)faces.size(); ++fi) {
                if (faces[fi].dead || faces[fi].outside.empty()) continue;
                for (int pi : faces[fi].outside) {
                    double d = pointFaceDist(P[pi], faces[fi]);
                    if (d > bestDist) { bestDist = d; fIdx = fi; apex = pi; }
                }
            }
            if (fIdx < 0) break;   // no point outside any face -> done

            // 2a. find all faces visible from apex (dist > 0); collect horizon edges
            std::vector<int> visible;
            for (int fi = 0; fi < (int)faces.size(); ++fi) {
                if (faces[fi].dead) continue;
                if (pointFaceDist(P[apex], faces[fi]) > 1e-10) { visible.push_back(fi); }
            }
            // horizon = edges shared by exactly one visible face
            std::vector<std::pair<int,int>> horizon;
            auto edgeShared = [&](int a, int b, int selfFace) {
                for (int fi : visible) {
                    if (fi == selfFace) continue;
                    const auto& fv = faces[fi].v;
                    for (int e = 0; e < 3; ++e) {
                        int x = fv[e], y = fv[(e+1)%3];
                        if ((x==a&&y==b) || (x==b&&y==a)) return true;
                    }
                }
                return false;
            };
            for (int fi : visible) {
                const auto& fv = faces[fi].v;
                for (int e = 0; e < 3; ++e) {
                    int a = fv[e], b = fv[(e+1)%3];
                    if (!edgeShared(a, b, fi)) { horizon.emplace_back(a, b); }
                }
            }

            // collect the outside points of all visible faces (to reassign), then kill them
            std::vector<int> orphan;
            for (int fi : visible) {
                for (int pi : faces[fi].outside) { if (pi != apex) orphan.push_back(pi); }
                faces[fi].dead = true;
            }

            // 2b. build new faces from horizon edges to apex
            std::vector<int> newFaces;
            for (auto& e : horizon) {
                Face nf = makeFace(e.first, e.second, apex, P, interior);
                newFaces.push_back((int)faces.size());
                faces.push_back(std::move(nf));
            }

            // 2c. reassign orphaned points to the new faces
            for (int pi : orphan) {
                for (int nfi : newFaces) {
                    if (faces[nfi].dead) { continue; }
                    if (pointFaceDist(P[pi], faces[nfi]) > 1e-10) { faces[nfi].outside.push_back(pi); break; }
                }
            }
        }

        // --- 3. Gather unique hull vertices ---
        std::vector<int> used;
        for (const auto& f : faces) {
            if (f.dead) continue;
            for (int idx : f.v) { used.push_back(idx); }
        }
        std::sort(used.begin(), used.end());
        used.erase(std::unique(used.begin(), used.end()), used.end());

        result.verts.reserve(used.size());
        for (int idx : used) { result.verts.push_back(P[idx]); }
        return result;
    }
} // namespace physlib::collision