#pragma once

#include "BaseMath.h"
#include "Color.h"
#include "Clipping.h"

typedef struct Bitmap
{
    int width;
    int height;
    Matrix view;
    Matrix proj;
    float neari;
    float far;
    float* buffer;
}
Bitmap;

static inline void BitmapReset(Bitmap* bitmap)
{
    int size = bitmap->width * bitmap->height;
    for (int i = 0; i < size; i++)
        bitmap->buffer[i] = 1;
}
static inline void BitmapSetView(Bitmap* bitmap, Camera* camera)
{
    bitmap->view = MatrixView3(camera);
}
static inline void BitmapSetProj(Bitmap* bitmap, float near, float far)
{
    bitmap->neari = 1.0f / near;
    bitmap->far = far;
    bitmap->proj = MatrixProjPerspective1(bitmap->width, bitmap->height, near, far);
}

static inline void BitmapSetViewByEuler(Bitmap* bitmap, Vector3 eye, float x, float y, float z)
{
    eye = Vector3Neg(eye);
    Matrix result = MatrixTranslate(eye);
    result = MatrixMultiply(result, MatrixRotateY(-y));
    result = MatrixMultiply(result, MatrixRotateX(-x));
    result = MatrixMultiply(result, MatrixRotateZ(-z));
    bitmap->view = result;
}
static inline void BitmapSetViewByPyr(Bitmap* bitmap, Vector3 eye, float pitch, float yaw, float roll)
{
    eye = Vector3Neg(eye);
    Matrix result = MatrixTranslate(eye);
    result = MatrixMultiply(result, MatrixRotateY(yaw));
    result = MatrixMultiply(result, MatrixRotateX(-pitch));
    result = MatrixMultiply(result, MatrixRotateZ(-roll));
    bitmap->view = result;
}
static inline void BitmapSetViewByTarget(Bitmap* bitmap, Vector3 eye, Vector3 target, Vector3 up)
{
    // v1
    Vector3 zAxis = Vector3Sub(target, eye);
            zAxis = Vector3Normalize(zAxis);

    Vector3 xAxis = Vector3Cross(up, zAxis);
            xAxis = Vector3Normalize(xAxis);

    Vector3 yAxis = Vector3Cross(zAxis, xAxis);

    Matrix result =
    {{
        { xAxis.x, xAxis.y, xAxis.z, 0 },
        { yAxis.x, yAxis.y, yAxis.z, 0 },
        { zAxis.x, zAxis.y, zAxis.z, 0 },
        {   eye.x,   eye.y,   eye.z, 1 }
    }};

    result = MatrixInvert(result);

    bitmap->view = result;

    // v2
    // Vector3 zAxis = Vector3Sub(target, eye);
    //         zAxis = Vector3Normalize(zAxis);

    // float roty = atan2(zAxis.x, zAxis.z);
    // float rotx = -zAxis.y*MATH_PI_DIV_4;

    // Matrix result = MatrixTranslate(Vector3Neg(eye));
    // result = MatrixMultiply(result, MatrixRotateY(roty));
    // result = MatrixMultiply(result, MatrixRotateX(rotx));
    // return result;
}

static inline void BitmapSetPixel(Bitmap* bitmap, int x, int y, Color color)
{
    assert(0 <= x && x < bitmap->width);
    assert(0 <= y && y < bitmap->height);

    int i = x + y * bitmap->width;

    ((uint32_t*)bitmap->buffer)[i] = color;
}
static inline void BitmapSetDepth(Bitmap* bitmap, int x, int y, float z)
{
    assert( 0 <= x && x < bitmap->width);
    assert( 0 <= y && y < bitmap->height);
    assert(-1 <= z && z <= +1);

    int i = x + y * bitmap->width;

    bitmap->buffer[i] =
    bitmap->buffer[i] < z ?
    bitmap->buffer[i] : z;
}

static inline void BitmapDrawVertexSp(Bitmap* bitmap, Vector3 v0)
{
    BitmapSetDepth(bitmap, v0.x, v0.y, v0.z);
}
static inline void BitmapDrawLineSp(Bitmap* bitmap, Vector3 v0, Vector3 v1)
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
            BitmapSetDepth(bitmap, x0, y0, z0);

                          { err -= dy; x0 += sx; }
            if (err <= 0) { err += dx; y0 += sy; }

            z0 += offset;
        }

        BitmapSetDepth(bitmap, x0, y0, z1);
    }
    else
    {
        float offset = (z1 - z0) / dy;

        int err = dy - dy / 2;

        for (int i = 0; i < dy; i++)
        {
            BitmapSetDepth(bitmap, x0, y0, z0);

                          { err -= dx; y0 += sy; }
            if (err <= 0) { err += dy; x0 += sx; }

            z0 += offset;
        }

        BitmapSetDepth(bitmap, x0, y0, z1);
    }
}
static inline void BitmapDrawTriangleSp(Bitmap* bitmap, Vector3 v0, Vector3 v1, Vector3 v2)
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
        BitmapSetDepth(bitmap, x, y, z);
    }
}

static inline void BitmapDrawVertexNdc(Bitmap* bitmap, Vector3 v0)
{
    assert(-1 <= v0.x && v0.x <= 1);
    assert(-1 <= v0.y && v0.y <= 1);
    assert(-1 <= v0.z && v0.z <= 1);

    v0 = NdcToScreenSpace(v0, bitmap->width, bitmap->height);

    BitmapDrawVertexSp(bitmap, v0);
}
static inline void BitmapDrawLineNdc(Bitmap* bitmap, Vector3 v0, Vector3 v1)
{
    assert(-1 <= v0.x && v0.x <= 1);
    assert(-1 <= v0.y && v0.y <= 1);
    assert(-1 <= v0.z && v0.z <= 1);

    assert(-1 <= v1.x && v1.x <= 1);
    assert(-1 <= v1.y && v1.y <= 1);
    assert(-1 <= v1.z && v1.z <= 1);

    v0 = NdcToScreenSpace(v0, bitmap->width, bitmap->height);
    v1 = NdcToScreenSpace(v1, bitmap->width, bitmap->height);

    BitmapDrawLineSp(bitmap, v0, v1);
}
static inline void BitmapDrawTriangleNdc(Bitmap* bitmap, Vector3 v0, Vector3 v1, Vector3 v2)
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

    v0 = NdcToScreenSpace(v0, bitmap->width, bitmap->height);
    v1 = NdcToScreenSpace(v1, bitmap->width, bitmap->height);
    v2 = NdcToScreenSpace(v2, bitmap->width, bitmap->height);

    BitmapDrawTriangleSp(bitmap, v0, v1, v2);
}

static inline void BitmapDrawVertex(Bitmap* bitmap, Vector3 v0)
{
    Vector4 _v0 = { v0.x, v0.y, v0.z, 1 };

    _v0 = MatrixMultiply4L(_v0, bitmap->view);
    _v0 = MatrixMultiply4L(_v0, bitmap->proj);

    if (!ClipInFrustum(_v0)) return;

    _v0.x /= _v0.w;
    _v0.y /= _v0.w;
    _v0.z /= _v0.w;

    v0 = (Vector3){ _v0.x, _v0.y, _v0.z };

    BitmapDrawVertexNdc(bitmap, v0);
}
static inline void BitmapDrawLine(Bitmap* bitmap, Vector3 v0, Vector3 v1)
{
    Vector4 _v0 = { v0.x, v0.y, v0.z, 1 };
    Vector4 _v1 = { v1.x, v1.y, v1.z, 1 };

    _v0 = MatrixMultiply4L(_v0, bitmap->view);
    _v1 = MatrixMultiply4L(_v1, bitmap->view);

    _v0 = MatrixMultiply4L(_v0, bitmap->proj);
    _v1 = MatrixMultiply4L(_v1, bitmap->proj);

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

    BitmapDrawLineNdc(bitmap, v0, v1);
}
static inline void BitmapDrawTriangle(Bitmap* bitmap, Vector3 v0, Vector3 v1, Vector3 v2)
{
    int vertexCount = 3;

    Vector4 vs0[9];
    Vector4 vs1[9];

    vs0[0] = (Vector4){ v0.x, v0.y, v0.z, 1 };
    vs0[1] = (Vector4){ v1.x, v1.y, v1.z, 1 };
    vs0[2] = (Vector4){ v2.x, v2.y, v2.z, 1 };

    vs0[0] = MatrixMultiply4L(vs0[0], bitmap->view);
    vs0[1] = MatrixMultiply4L(vs0[1], bitmap->view);
    vs0[2] = MatrixMultiply4L(vs0[2], bitmap->view);

    vs0[0] = MatrixMultiply4L(vs0[0], bitmap->proj);
    vs0[1] = MatrixMultiply4L(vs0[1], bitmap->proj);
    vs0[2] = MatrixMultiply4L(vs0[2], bitmap->proj);

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

        BitmapDrawTriangleNdc(bitmap, v0, v1, v2);
    }
}

static inline void BitmapApplyDepth(Bitmap* bitmap)
{
    float* zbuffer = (float*)bitmap->buffer;
    uint32_t* pixels = (uint32_t*)bitmap->buffer;

    int size = bitmap->width * bitmap->height;

    for (int i = 0; i < size; i++)
    {
        float t = zbuffer[i];
        t = (t + 1) / 2;
        pixels[i] = ColorCreateBwFloat(t);
    }
}
static inline void BitmapApplyDepthInvert(Bitmap* bitmap)
{
    float* zbuffer = (float*)bitmap->buffer;
    uint32_t* pixels = (uint32_t*)bitmap->buffer;

    int size = bitmap->width * bitmap->height;

    for (int i = 0; i < size; i++)
    {
        float t = zbuffer[i];
        t = (t + 1) / 2;
        t = 1 - t;
        pixels[i] = ColorCreateBwFloat(t);
    }
}

static inline void BitmapApplyDepthAdjusted(Bitmap* bitmap)
{
    float* zbuffer = (float*)bitmap->buffer;
    uint32_t* pixels = (uint32_t*)bitmap->buffer;

    int size = bitmap->width * bitmap->height;

    for (int i = 0; i < size; i++)
    {
        float t = zbuffer[i];
        t = (t + 1) / 2;
        t = 1 - t;
        t *= bitmap->neari;
        t = 1 - t;
        t = MathClamp(t, 0, 1);
        pixels[i] = ColorCreateBwFloat(t);
    }
}
static inline void BitmapApplyDepthAdjustedInvert(Bitmap* bitmap)
{
    float* zbuffer = (float*)bitmap->buffer;
    uint32_t* pixels = (uint32_t*)bitmap->buffer;

    int size = bitmap->width * bitmap->height;

    for (int i = 0; i < size; i++)
    {
        float t = zbuffer[i];
        t = (t + 1) / 2;
        t = 1 - t;
        t *= bitmap->neari;
        t = MathClamp(t, 0, 1);
        pixels[i] = ColorCreateBwFloat(t);
    }
}

// INIT
#define BitmapSizeOf(width, height) (sizeof(Bitmap) + sizeof(float)*width*height)
static inline Bitmap* BitmapInit(int width, int height, void* mem)
{
    assert(width > 0);
    assert(height > 0);

    Bitmap* bitmap = (Bitmap*)((char*)mem);
    float* buffer  = (float*)((char*)mem + sizeof(Bitmap));

    float near = 0.1f;
    float far = 100.f;

    bitmap->width = width;
    bitmap->height = height;
    bitmap->view = MatrixIdentity();
    bitmap->proj = MatrixProjPerspective1(width, height, near, far);
    bitmap->neari = 1.0f / near;
    bitmap->far = far;
    bitmap->buffer = buffer;

    return bitmap;
}
static inline Bitmap* BitmapCreate(int width, int height)
{
    int size = BitmapSizeOf(width, height);
    void* mem = malloc(size);
    return BitmapInit(width, height, mem);
}
static inline void BitmapDestroy(Bitmap* bitmap)
{
    free((void*)bitmap);
}
