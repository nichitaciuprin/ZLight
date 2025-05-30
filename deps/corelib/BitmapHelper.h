#pragma once

#include "BaseMath.h"
#include "Color.h"
#include "Clipping.h"

static inline void ZBuffReset(float* zb, int size)
{
    for (int i = 0; i < size; i++)
        zb[i] = 1;
}

static inline void ZBuffSetColor(float* zb, int width, int x, int y, Color color)
{
    int i = x + y * width;
    uint32_t* pixels = (uint32_t*)zb;
    pixels[i] = color;
}
static inline void ZBuffSetDepth(float* zb, int width, int x, int y, float depth)
{
    int i = x + y * width;

    zb[i] =
    zb[i] < depth ?
    zb[i] : depth;
}

static inline void ZBuffDrawVS(float* zb, int width, Vector3 v0)
{
    ZBuffSetDepth(zb, width, v0.x, v0.y, v0.z);
}
static inline void ZBuffDrawLS(float* zb, int width, Vector3 v0, Vector3 v1)
{
    int x0 = (int)v0.x;
    int y0 = (int)v0.y;
    float z0 = v0.z;

    int x1 = (int)v1.x;
    int y1 = (int)v1.y;
    float z1 = v1.z;

    int dx, sx;
    int dy, sy;

    if (x0 < x1) { dx = x1 - x0; sx =  1; }
    else         { dx = x0 - x1; sx = -1; }

    if (y0 < y1) { dy = y1 - y0; sy =  1; }
    else         { dy = y0 - y1; sy = -1; }

    // TODO maybe refactor branching
    if (dx > dy)
    {
        float offset = (z1 - z0) / dx;

        int err = dx - dx / 2;

        for (int i = 0; i < dx; i++)
        {
            ZBuffSetDepth(zb, width, x0, y0, z0);

                          { err -= dy; x0 += sx; }
            if (err <= 0) { err += dx; y0 += sy; }

            z0 += offset;
        }

        ZBuffSetDepth(zb, width, x0, y0, z1);
    }
    else
    {
        float offset = (z1 - z0) / dy;

        int err = dy - dy / 2;

        for (int i = 0; i < dy; i++)
        {
            ZBuffSetDepth(zb, width, x0, y0, z0);

                          { err -= dx; y0 += sy; }
            if (err <= 0) { err += dy; x0 += sx; }

            z0 += offset;
        }

        ZBuffSetDepth(zb, width, x0, y0, z1);
    }
}
static inline void ZBuffDrawTS(float* zb, int width, Vector3 v0, Vector3 v1, Vector3 v2)
{
    // pushes corners
    // v0.x = (float)(int)v0.x;
    // v0.y = (float)(int)v0.y;
    // v1.x = (float)(int)v1.x;
    // v1.y = (float)(int)v1.y;
    // v2.x = (float)(int)v2.x;
    // v2.y = (float)(int)v2.y;

    int maxx = MathMax(v0.x, MathMax(v1.x, v2.x));
    int minx = MathMin(v0.x, MathMin(v1.x, v2.x));
    int maxy = MathMax(v0.y, MathMax(v1.y, v2.y));
    int miny = MathMin(v0.y, MathMin(v1.y, v2.y));

    for (int y = miny; y <= maxy; y++)
    for (int x = minx; x <= maxx; x++)
    {
        if (!TriangleIsInside3(v0, v1, v2, x, y)) continue;
        float z = TriangleBarycentric2(v0, v1, v2, x, y);
        ZBuffSetDepth(zb, width, x, y, z);
    }
}

static inline void ZBuffDrawVN(float* zb, int width, int height, Vector3 v0)
{
    assert(-1 <= v0.x && v0.x <= 1);
    assert(-1 <= v0.y && v0.y <= 1);
    assert(-1 <= v0.z && v0.z <= 1);

    v0 = NdcToScreenSpace(v0, width, height);

    ZBuffDrawVS(zb, width, v0);
}
static inline void ZBuffDrawLN(float* zb, int width, int height, Vector3 v0, Vector3 v1)
{
    assert(-1 <= v0.x && v0.x <= 1);
    assert(-1 <= v0.y && v0.y <= 1);
    assert(-1 <= v0.z && v0.z <= 1);

    assert(-1 <= v1.x && v1.x <= 1);
    assert(-1 <= v1.y && v1.y <= 1);
    assert(-1 <= v1.z && v1.z <= 1);

    v0 = NdcToScreenSpace(v0, width, height);
    v1 = NdcToScreenSpace(v1, width, height);

    ZBuffDrawLS(zb, width, v0, v1);
}
static inline void ZBuffDrawTN(float* zb, int width, int height, Vector3 v0, Vector3 v1, Vector3 v2)
{
    assert(-1 <= v0.x && v0.x <= 1);
    assert(-1 <= v0.y && v0.y <= 1);
    assert(-1 <= v0.z && v0.z <= 1);

    assert(-1 <= v1.x && v1.x <= 1);
    assert(-1 <= v1.y && v1.y <= 1);
    assert(-1 <= v1.z && v1.z <= 1);

    assert(-1 <= v2.x && v2.x <= 1);
    assert(-1 <= v2.y && v2.y <= 1);
    assert(-1 <= v2.z && v2.z <= 1);

    // TODO move to BitmapDrawTriangleSp?
    if (!TriangleIsClockwise(v0, v1, v2)) return;

    v0 = NdcToScreenSpace(v0, width, height);
    v1 = NdcToScreenSpace(v1, width, height);
    v2 = NdcToScreenSpace(v2, width, height);

    ZBuffDrawTS(zb, width, v0, v1, v2);
}

static inline void ZBuffDrawV(float* zb, int width, int height, Matrix view, Matrix proj, Vector3 v0)
{
    Vector4 _v0 = { v0.x, v0.y, v0.z, 1 };

    _v0 = MatrixMultiply4L(_v0, view);
    _v0 = MatrixMultiply4L(_v0, proj);

    if (!ClipInFrustum(_v0)) return;

    _v0.x /= _v0.w;
    _v0.y /= _v0.w;
    _v0.z /= _v0.w;

    v0 = (Vector3){ _v0.x, _v0.y, _v0.z };

    ZBuffDrawVN(zb, width, height, v0);
}
static inline void ZBuffDrawL(float* zb, int width, int height, Matrix view, Matrix proj, Vector3 v0, Vector3 v1)
{
    Vector4 _v0 = { v0.x, v0.y, v0.z, 1 };
    Vector4 _v1 = { v1.x, v1.y, v1.z, 1 };

    _v0 = MatrixMultiply4L(_v0, view);
    _v1 = MatrixMultiply4L(_v1, view);

    _v0 = MatrixMultiply4L(_v0, proj);
    _v1 = MatrixMultiply4L(_v1, proj);

    if (ClipLineWClipSpace      (&_v0, &_v1)) return;
    if (ClipLineBackClipSpace   (&_v0, &_v1)) return;
    if (ClipLineFrontClipSpace  (&_v0, &_v1)) return;
    if (ClipLineLeftClipSpace   (&_v0, &_v1)) return;
    if (ClipLineRightClipSpace  (&_v0, &_v1)) return;
    if (ClipLineDownClipSpace   (&_v0, &_v1)) return;
    if (ClipLineUpClipSpace     (&_v0, &_v1)) return;

    _v0.x /= _v0.w;
    _v0.y /= _v0.w;
    _v0.z /= _v0.w;
    _v1.x /= _v1.w;
    _v1.y /= _v1.w;
    _v1.z /= _v1.w;

    // removing clip errors
    _v0.x = MathClamp(_v0.x, -1, +1);
    _v0.y = MathClamp(_v0.y, -1, +1);
    _v0.z = MathClamp(_v0.z, -1, +1);
    _v1.x = MathClamp(_v1.x, -1, +1);
    _v1.y = MathClamp(_v1.y, -1, +1);
    _v1.z = MathClamp(_v1.z, -1, +1);

    v0.x = _v0.x;
    v0.y = _v0.y;
    v0.z = _v0.z;
    v1.x = _v1.x;
    v1.y = _v1.y;
    v1.z = _v1.z;

    ZBuffDrawLN(zb, width, height, v0, v1);
}
static inline void ZBuffDrawT(float* zb, int width, int height, Matrix view, Matrix proj, Vector3 v0, Vector3 v1, Vector3 v2)
{
    int vertexCount = 3;

    Vector4 vs0[9];
    Vector4 vs1[9];

    vs0[0] = (Vector4){ v0.x, v0.y, v0.z, 1 };
    vs0[1] = (Vector4){ v1.x, v1.y, v1.z, 1 };
    vs0[2] = (Vector4){ v2.x, v2.y, v2.z, 1 };

    vs0[0] = MatrixMultiply4L(vs0[0], view);
    vs0[1] = MatrixMultiply4L(vs0[1], view);
    vs0[2] = MatrixMultiply4L(vs0[2], view);

    vs0[0] = MatrixMultiply4L(vs0[0], proj);
    vs0[1] = MatrixMultiply4L(vs0[1], proj);
    vs0[2] = MatrixMultiply4L(vs0[2], proj);

    ClipPoligonWClipSpace      (vs0, vs1, &vertexCount); if (vertexCount < 3) return;
    ClipPoligonBackClipSpace   (vs1, vs0, &vertexCount); if (vertexCount < 3) return;
    ClipPoligonFrontClipSpace  (vs0, vs1, &vertexCount); if (vertexCount < 3) return;
    ClipPoligonLeftClipSpace   (vs1, vs0, &vertexCount); if (vertexCount < 3) return;
    ClipPoligonRightClipSpace  (vs0, vs1, &vertexCount); if (vertexCount < 3) return;
    ClipPoligonDownClipSpace   (vs1, vs0, &vertexCount); if (vertexCount < 3) return;
    ClipPoligonUpClipSpace     (vs0, vs1, &vertexCount); if (vertexCount < 3) return;
    ClipPoligonClipSpaceDiv    (vs1,       vertexCount);

    for (int i = 1; i < vertexCount - 1; i++)
    {
        Vector4 _v0 = vs1[0];
        Vector4 _v1 = vs1[i];
        Vector4 _v2 = vs1[i+1];

        v0 = (Vector3){ _v0.x, _v0.y, _v0.z };
        v1 = (Vector3){ _v1.x, _v1.y, _v1.z };
        v2 = (Vector3){ _v2.x, _v2.y, _v2.z };

        ZBuffDrawTN(zb, width, height, v0, v1, v2);
    }
}

static inline void ZBuffApplyDepth(float* zb, int size)
{
    uint32_t* pixels = (uint32_t*)zb;

    for (int i = 0; i < size; i++)
    {
        float t = zb[i];
        t = (t + 1) / 2;
        pixels[i] = ColorSetLightValueF(0x00FFFFFF, t);
    }
}
static inline void ZBuffApplyDepthInvert(float* zb, int size)
{
    uint32_t* pixels = (uint32_t*)zb;

    for (int i = 0; i < size; i++)
    {
        float t = zb[i];
        t = (t + 1) / 2;
        t = 1 - t;
        pixels[i] = ColorSetLightValueF(0x00FFFFFF, t);
    }
}

static inline void ZBuffApplyDepthAdjusted(float* zb, int size, float neari)
{
    uint32_t* pixels = (uint32_t*)zb;

    for (int i = 0; i < size; i++)
    {
        float t = zb[i];
        t = (t + 1) / 2;
        t = 1 - t;
        t *= neari;
        t = 1 - t;
        t = MathClamp(t, 0, 1);
        pixels[i] = ColorSetLightValueF(0x00FFFFFF, t);
    }
}
static inline void ZBuffApplyDepthAdjustedInvert(float* zb, int size, float neari)
{
    uint32_t* pixels = (uint32_t*)zb;

    for (int i = 0; i < size; i++)
    {
        float t = zb[i];
        t = (t + 1) / 2;
        t = 1 - t;
        t *= neari;
        t = MathClamp(t, 0, 1);
        pixels[i] = ColorSetLightValueF(0x00FFFFFF, t);
    }
}
