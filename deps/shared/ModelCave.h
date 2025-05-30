#pragma once

#include "BaseMath.h"
#include "Subgen.h"

#include "ModelForest1.h"

namespace ModelCave
{
    void Offset(vector<Vector3>& vs, Vector3 offset)
    {
        for (auto& x : vs) x += offset;
    }
    void RandOffset(Vector3& v)
    {
        float x = Subgen1Range(-1, +1);
        float z = Subgen1Range(-1, +1);
        Vector3 offset = { x, 0, z };
        offset = Vector3Normalize(offset);
        v += offset * 0.75f;
    }
    void RandOffset(Vector3& v, float max)
    {
        float x = Subgen1Range(-1, +1);
        float y = Subgen1Range(-1, +1);
        float z = Subgen1Range(-1, +1);
        v += Vector3Normalize({ x, y, z }) * Subgen1Range(0, max);
    }
    void RandOffset(vector<Vector3>& spline)
    {
        for (auto& v : spline)
        {
            float x = Subgen1Range(-1, +1);
            float z = Subgen1Range(-1, +1);
            Vector3 offset = { x, 0, z };
            offset = Vector3Normalize(offset);
            v += offset * 0.75f;
        }
    }
    void Subdivide(vector<Vector3>& path, float segmentLengthMax)
    {
        vector<Vector3> copy = path;
    
        path.clear();
    
        for (size_t i = 1; i < copy.size(); i++)
        {
            Vector3& v0 = copy[i-1];
            Vector3& v1 = copy[i];
    
            float distance = Vector3Distance(v0, v1);
    
            int divs = distance / segmentLengthMax;
    
            for (int i = 0; i < divs; i++)
            {
                float t = (float)i / divs;
                Vector3 v = Vector3Lerp(v0, v1, t);
                path.push_back(v);
            }
        }
    
        path.push_back(copy[copy.size()-1]);
    }

    vector<Vector3> caveSpline1 = {};
    vector<Vector3> caveSpline2 = {};
    vector<Vector3> caveSpline3 = {};

    void Init()
    {
        vector<Vector3> spline =
        {
            { -15, 0,  0 },
            {  -2, 0,  0 },
            {  -2, 0, 20 },
            {   2, 0, 20 },
            {   2, 0,  0 },
            {  15, 0,  0 },
        };
        Subdivide(spline, 1.0f);
        caveSpline1 = spline;
        caveSpline2 = spline;
        caveSpline3 = spline;
        RandOffset(caveSpline1);
        RandOffset(caveSpline2);
        RandOffset(caveSpline3);
        Offset(caveSpline2, Vector3Up()*2);
        Offset(caveSpline3, Vector3Up()*4);
    }
    void Draw(Bitmap* bitmap)
    {
        for (size_t i = 1; i < caveSpline1.size(); i++)
        {
            Vector3& v0 = caveSpline1[i-1];
            Vector3& v1 = caveSpline2[i-1];
            Vector3& v2 = caveSpline3[i-1];
            Vector3& v3 = caveSpline1[i];
            Vector3& v4 = caveSpline2[i];
            Vector3& v5 = caveSpline3[i];
            BitmapDrawQuad(bitmap, v0, v1, v4, v3);
            BitmapDrawQuad(bitmap, v1, v2, v5, v4);
        }

        {
            Vector3 v0 = { -3, 4,  0 };
            Vector3 v1 = { -3, 4, 20 };
            Vector3 v2 = {  3, 4, 20 };
            Vector3 v3 = {  3, 4,  0 };
            BitmapDrawQuad(bitmap, v3, v2, v1, v0);
        }

        // Bound bound;
        // bound.p0 = {  -15,  0, -1 };
        // bound.p1 = {  -1.25f, 10, +1 };
        // BitmapDrawBoundWire(bitmap, bound);
        // bound.p0.x = -bound.p0.x;
        // bound.p1.x = -bound.p1.x;
        // BitmapDrawBoundWire(bitmap, bound);
        // bound.p0 = {  -2.00f,  0, +20 };
        // bound.p1 = {  -1.25f, 10, -1 };
        // BitmapDrawBoundWire(bitmap, bound);
        // bound.p0.x = -bound.p0.x;
        // bound.p1.x = -bound.p1.x;
        // BitmapDrawBoundWire(bitmap, bound);
        // bound.p0 = {  -2.00f,  0, +19 };
        // bound.p1 = {  +2.00f, 10, +20 };
        // BitmapDrawBoundWire(bitmap, bound);
    }
    void Push(Vector3& point)
    {
        Bound bound;
        bound.p0 = {  -15,  0, -1 };
        bound.p1 = {  -1.25f, 10, +1 };
        PushOutBound(&point, bound);
        bound.p0.x = -bound.p0.x;
        bound.p1.x = -bound.p1.x;
        PushOutBound(&point, bound);
        bound.p0 = {  -2.00f,  0, +20 };
        bound.p1 = {  -1.25f, 10, -1 };
        PushOutBound(&point, bound);
        bound.p0.x = -bound.p0.x;
        bound.p1.x = -bound.p1.x;
        PushOutBound(&point, bound);
        bound.p0 = {  -2.00f,  0, +19 };
        bound.p1 = {  +2.00f, 10, +20 };
        PushOutBound(&point, bound);
    }
}
