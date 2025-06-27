#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <float.h>
#include <math.h>

#define MATH_PI        (float)3.14159265358979323846
#define MATH_PI_MUL_2  (float)6.28318530717958647692
#define MATH_PI_DIV_2  (float)1.57079632679489661923
#define MATH_PI_DIV_4  (float)0.78539816339744830961

#define LIGHT_MAX_DIST 15
#define SHADOW_MAP_SIZE 128
#define SHADOW_MAP_BIAS 0.001f
#define SHADOW_MAP_PROJ_MACRO(near, far) ((Matrix)\
{{\
    {1, 0, 0, 0},\
    {0, 1, 0, 0},\
    {0, 0,  ((far+near)   / (far-near)), 1},\
    {0, 0, -((near*2*far) / (far-near)), 0}\
}})
#define SHADOW_MAP_PROJ SHADOW_MAP_PROJ_MACRO(0.1f, LIGHT_MAX_DIST)

typedef struct Vector2
{
    float x, y;
}
Vector2;
typedef struct Vector3
{
    float x, y, z;
}
Vector3;
typedef struct Vector4
{
    float x, y, z, w;
}
Vector4;
typedef struct Matrix
{
    float m[4][4];
}
Matrix;
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
typedef struct SpotLight
{
    Vector3 pos;
    float lum;
    float bufl[SHADOW_MAP_SIZE*SHADOW_MAP_SIZE]; Matrix matl;
    float bufr[SHADOW_MAP_SIZE*SHADOW_MAP_SIZE]; Matrix matr;
    float bufd[SHADOW_MAP_SIZE*SHADOW_MAP_SIZE]; Matrix matd;
    float bufu[SHADOW_MAP_SIZE*SHADOW_MAP_SIZE]; Matrix matu;
    float bufb[SHADOW_MAP_SIZE*SHADOW_MAP_SIZE]; Matrix matb;
    float buff[SHADOW_MAP_SIZE*SHADOW_MAP_SIZE]; Matrix matf;
}
SpotLight;
typedef struct LightData
{
    SpotLight* lights;
    int lightsc;
}
LightData;

static inline float MathClamp(float x, float min, float max)
{
    if (x < min) { return min; };
    if (x > max) { return max; };
                   return x;
}
static inline float MathLerp(float a, float b, float t)
{
    return a + (b - a) * t;
}
static inline float MathLerpInverse(float a, float b, float x)
{
    return (x - a) / (b - a);
}

static inline Vector3 Vector3Neg(Vector3 r)
{
    r.x = -r.x;
    r.y = -r.y;
    r.z = -r.z;
    return r;
}
static inline Vector3 Vector3Add(Vector3 l, Vector3 r)
{
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    return l;
}
static inline Vector3 Vector3Sub(Vector3 l, Vector3 r)
{
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    return l;
}
static inline Vector3 Vector3Mul(Vector3 l, float r)
{
    l.x *= r;
    l.y *= r;
    l.z *= r;
    return l;
}
static inline Vector3 Vector3Div(Vector3 l, float r)
{
    l.x /= r;
    l.y /= r;
    l.z /= r;
    return l;
}

static inline float Vector3Length(Vector3 v)
{
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    return sqrtf(x + y + z);
}
static inline float Vector3Distance(Vector3 a, Vector3 b)
{
    Vector3 v = Vector3Sub(a, b);
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    return sqrtf(x + y + z);
}
static inline Vector4 Vector4Lerp(Vector4 a, Vector4 b, float t)
{
    a.x = MathLerp(a.x, b.x, t);
    a.y = MathLerp(a.y, b.y, t);
    a.z = MathLerp(a.z, b.z, t);
    a.w = MathLerp(a.w, b.w, t);
    return a;
}
static inline Vector3 Vector3Normalize(Vector3 v)
{
    // TODO remove "if (length == 0)" ?
    float length = Vector3Length(v);
    if (length == 0) return v;
    return Vector3Div(v, length);
}

static inline Vector3 Vector3RotateX(Vector3 v, float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    float x = v.x;
    float y = v.y * ( cos) + v.z * ( sin);
    float z = v.y * (-sin) + v.z * ( cos);
    return (Vector3){ x, y, z };
}
static inline Vector3 Vector3RotateY(Vector3 v, float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    float x = v.x * ( cos) + v.z * (-sin);
    float y = v.y;
    float z = v.x * ( sin) + v.z * ( cos);
    return (Vector3){ x, y, z };
}
static inline Vector3 Vector3RotateZ(Vector3 v, float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    float x = v.x * ( cos) + v.y * ( sin);
    float y = v.x * (-sin) + v.y * ( cos);
    float z = v.z;
    return (Vector3){ x, y, z };
}

static inline Vector3 Vector3Cross(Vector3 a, Vector3 b)
{
    float x = a.y*b.z - a.z*b.y;
    float y = a.z*b.x - a.x*b.z;
    float z = a.x*b.y - a.y*b.x;
    return (Vector3){ x, y, z };
}

static inline float Vector3Dot(Vector3 l, Vector3 r)
{
    float x = l.x * r.x;
    float y = l.y * r.y;
    float z = l.z * r.z;
    return x + y + z;
}
static inline float Vector4Dot(Vector4 l, Vector4 r)
{
    float x = l.x * r.x;
    float y = l.y * r.y;
    float z = l.z * r.z;
    float w = l.w * r.w;
    return x + y + z + w;
}

static inline Vector3 MatrixMultiply3L(Vector3 v, Matrix m)
{
    Vector4 col0 = { m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0] };
    Vector4 col1 = { m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1] };
    Vector4 col2 = { m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2] };

    Vector4 row = { v.x, v.y, v.z, 1 };

    v.x = Vector4Dot(row, col0);
    v.y = Vector4Dot(row, col1);
    v.z = Vector4Dot(row, col2);

    return v;
}
static inline Vector4 MatrixMultiply4L(Vector4 v, Matrix m)
{
    Vector4 col0 = { m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0] };
    Vector4 col1 = { m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1] };
    Vector4 col2 = { m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2] };
    Vector4 col3 = { m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3] };

    Vector4 row = v;

    v.x = Vector4Dot(row, col0);
    v.y = Vector4Dot(row, col1);
    v.z = Vector4Dot(row, col2);
    v.w = Vector4Dot(row, col3);

    return v;
}

static inline Matrix MatrixIdentity()
{
    return (Matrix)
    {{
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1},
    }};
}
static inline Matrix MatrixInvert(Matrix m)
{
    Matrix result;

    float a00 = m.m[0][0], a01 = m.m[0][1], a02 = m.m[0][2], a03 = m.m[0][3];
    float a10 = m.m[1][0], a11 = m.m[1][1], a12 = m.m[1][2], a13 = m.m[1][3];
    float a20 = m.m[2][0], a21 = m.m[2][1], a22 = m.m[2][2], a23 = m.m[2][3];
    float a30 = m.m[3][0], a31 = m.m[3][1], a32 = m.m[3][2], a33 = m.m[3][3];

    float b00 = a00*a11 - a01*a10;
    float b01 = a00*a12 - a02*a10;
    float b02 = a00*a13 - a03*a10;
    float b03 = a01*a12 - a02*a11;
    float b04 = a01*a13 - a03*a11;
    float b05 = a02*a13 - a03*a12;
    float b06 = a20*a31 - a21*a30;
    float b07 = a20*a32 - a22*a30;
    float b08 = a20*a33 - a23*a30;
    float b09 = a21*a32 - a22*a31;
    float b10 = a21*a33 - a23*a31;
    float b11 = a22*a33 - a23*a32;

    float invDet = 1.0f / (b00*b11 - b01*b10 + b02*b09 + b03*b08 - b04*b07 + b05*b06);

    result.m[0][0] = ( a11*b11 - a12*b10 + a13*b09) * invDet;
    result.m[0][1] = (-a01*b11 + a02*b10 - a03*b09) * invDet;
    result.m[0][2] = ( a31*b05 - a32*b04 + a33*b03) * invDet;
    result.m[0][3] = (-a21*b05 + a22*b04 - a23*b03) * invDet;
    result.m[1][0] = (-a10*b11 + a12*b08 - a13*b07) * invDet;
    result.m[1][1] = ( a00*b11 - a02*b08 + a03*b07) * invDet;
    result.m[1][2] = (-a30*b05 + a32*b02 - a33*b01) * invDet;
    result.m[1][3] = ( a20*b05 - a22*b02 + a23*b01) * invDet;
    result.m[2][0] = ( a10*b10 - a11*b08 + a13*b06) * invDet;
    result.m[2][1] = (-a00*b10 + a01*b08 - a03*b06) * invDet;
    result.m[2][2] = ( a30*b04 - a31*b02 + a33*b00) * invDet;
    result.m[2][3] = (-a20*b04 + a21*b02 - a23*b00) * invDet;
    result.m[3][0] = (-a10*b09 + a11*b07 - a12*b06) * invDet;
    result.m[3][1] = ( a00*b09 - a01*b07 + a02*b06) * invDet;
    result.m[3][2] = (-a30*b03 + a31*b01 - a32*b00) * invDet;
    result.m[3][3] = ( a20*b03 - a21*b01 + a22*b00) * invDet;

    return result;
}
static inline Matrix MatrixMultiply(Matrix l, Matrix r)
{
    Vector4 row0 = { l.m[0][0], l.m[0][1], l.m[0][2], l.m[0][3] };
    Vector4 row1 = { l.m[1][0], l.m[1][1], l.m[1][2], l.m[1][3] };
    Vector4 row2 = { l.m[2][0], l.m[2][1], l.m[2][2], l.m[2][3] };
    Vector4 row3 = { l.m[3][0], l.m[3][1], l.m[3][2], l.m[3][3] };

    Vector4 col0 = { r.m[0][0], r.m[1][0], r.m[2][0], r.m[3][0] };
    Vector4 col1 = { r.m[0][1], r.m[1][1], r.m[2][1], r.m[3][1] };
    Vector4 col2 = { r.m[0][2], r.m[1][2], r.m[2][2], r.m[3][2] };
    Vector4 col3 = { r.m[0][3], r.m[1][3], r.m[2][3], r.m[3][3] };

    float m00 = Vector4Dot(row0, col0);
    float m01 = Vector4Dot(row0, col1);
    float m02 = Vector4Dot(row0, col2);
    float m03 = Vector4Dot(row0, col3);

    float m10 = Vector4Dot(row1, col0);
    float m11 = Vector4Dot(row1, col1);
    float m12 = Vector4Dot(row1, col2);
    float m13 = Vector4Dot(row1, col3);

    float m20 = Vector4Dot(row2, col0);
    float m21 = Vector4Dot(row2, col1);
    float m22 = Vector4Dot(row2, col2);
    float m23 = Vector4Dot(row2, col3);

    float m30 = Vector4Dot(row3, col0);
    float m31 = Vector4Dot(row3, col1);
    float m32 = Vector4Dot(row3, col2);
    float m33 = Vector4Dot(row3, col3);

    return (Matrix)
    {{
        {m00,m01,m02,m03},
        {m10,m11,m12,m13},
        {m20,m21,m22,m23},
        {m30,m31,m32,m33}
    }};
}
static inline Matrix MatrixRotateX(float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    return (Matrix)
    {{
        { 1,   0,    0,    0 },
        { 0,   cos, -sin,  0 },
        { 0,   sin,  cos,  0 },
        { 0,   0,    0,    1 }
    }};
}
static inline Matrix MatrixRotateY(float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    return (Matrix)
    {{
       {  cos,   0,  sin,   0 },
       {    0,   1,    0,   0 },
       { -sin,   0,  cos,   0 },
       {    0,   0,    0,   1 }
    }};
}
static inline Matrix MatrixRotateZ(float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    return (Matrix)
    {{
        { cos, -sin,  0,   0 },
        { sin,  cos,  0,   0 },
        { 0,    0,    1,   0 },
        { 0,    0,    0,   1 }
    }};
}
static inline Matrix MatrixTranslate(Vector3 position)
{
    float x = position.x;
    float y = position.y;
    float z = position.z;
    return (Matrix)
    {{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {x, y, z, 1}
    }};
}
static inline Matrix MatrixRotate(Vector3 rotation)
{
    Matrix result;
    result = MatrixRotateX(rotation.x);
    result = MatrixMultiply(result, MatrixRotateY(rotation.y));
    result = MatrixMultiply(result, MatrixRotateZ(rotation.z));
    return result;
}
static inline Matrix MatrixScale(Vector3 scale)
{
    float x = scale.x;
    float y = scale.y;
    float z = scale.z;
    return (Matrix)
    {{
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1}
    }};
}
static inline Matrix MatrixWorld(Vector3 position, Vector3 rotation, Vector3 scale)
{
    Matrix result;
    result = MatrixScale(scale);
    result = MatrixMultiply(result, MatrixRotate(rotation));
    result = MatrixMultiply(result, MatrixTranslate(position));
    return result;
}
static inline Matrix MatrixProjOrthographic(float width, float height, float near, float far)
{
    float w = 2.0f / width;
    float h = 2.0f / height;
    float a = 1.0f / (far - near);
    float b = a * -near;
    return (Matrix)
    {{
        {w, 0, 0, 0},
        {0, h, 0, 0},
        {0, 0, a, 0},
        {0, 0, b, 1}
    }};
}
static inline Matrix MatrixProjPerspective1(float width, float height, float near, float far)
{
    float x = (near*2) / (near*2/width*height);
    float y = (near*2) / (near*2);
    float z = (far+near) / (far-near);
    float o = (near*2*far) / (far-near);

    return (Matrix)
    {{
        {x,  0,  0,  0},
        {0,  y,  0,  0},
        {0,  0,  z,  1},
        {0,  0, -o,  0}
    }};
}
static inline Matrix MatrixProjPerspective3(float width, float height, float near, float far, float fov)
{
    float ratio = width / height;

    float h = 1.0f / tanf(fov / 2);
    float w = h / ratio;
    float a = far / (far - near);
    float o = a * near;

    return (Matrix)
    {{
        {w,  0,  0,  0},
        {0,  h,  0,  0},
        {0,  0,  a,  1},
        {0,  0, -o,  0}
    }};
}

static inline Vector3 WorldToNdc(Vector3 p, Matrix view, Matrix proj)
{
    Vector4 _p = { p.x, p.y, p.z, 1 };

    _p = MatrixMultiply4L(_p, view);

    _p = MatrixMultiply4L(_p, proj);
    _p.x /= _p.w;
    _p.y /= _p.w;
    _p.z /= _p.w;
    _p.w = 1;

    return (Vector3) { _p.x, _p.y, _p.z };
}
static inline Vector3 NdcToWorld(Vector3 p, Matrix viewi, Matrix proji)
{
    Vector4 _p = { p.x, p.y, p.z, 1 };
    _p = MatrixMultiply4L(_p, proji);
    _p.x /= _p.w;
    _p.y /= _p.w;
    _p.z /= _p.w;
    _p.w = 1;
    _p = MatrixMultiply4L(_p, viewi);
    return (Vector3){ _p.x, _p.y, _p.z };
}

static inline Vector3 NdcToScreenSpace(Vector3 v, int width, int height)
{
    // v.y = -v.y;
    // v.x += 1.0f;
    // v.y += 1.0f;
    // v.x /= 2.0f;
    // v.y /= 2.0f;
    // v.x = maxx * v.x;
    // v.y = maxy * v.y;

    v.x = (+v.x + 1) / 2 * (width  - 1);
    v.y = (-v.y + 1) / 2 * (height - 1);

    // TODO temp, remove if not called
    assert(0 <= v.x && v.x <= (width  - 1));
    assert(0 <= v.y && v.y <= (height - 1));

    return v;
}
static inline Vector3 ScreenSpaceToNdc(Vector3 v, int maxx, int maxy)
{
    // v.x /= maxx;
    // v.y /= maxy;
    // v.x *= 2.0f;
    // v.y *= 2.0f;
    // v.x -= 1.0f;
    // v.y -= 1.0f;
    // v.y = -v.y;

    v.x = +(v.x / maxx * 2 - 1);
    v.y = -(v.y / maxy * 2 - 1);

    // TODO temp, remove if not called
    assert(-1 <= v.x && v.x <= +1);
    assert(-1 <= v.y && v.y <= +1);

    return v;
}

static inline bool TriangleIsClockwise(Vector3 v0, Vector3 v1, Vector3 v2)
{
    Vector3 d0 = Vector3Sub(v1, v0);
    Vector3 d1 = Vector3Sub(v2, v0);
    float crossZ = d0.x*d1.y - d0.y*d1.x;
    return crossZ < 0;
}
static inline bool TriangleIsInside(Vector3 v0, Vector3 v1, Vector3 v2, float x, float y)
{
    // by half-plane

    // https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
    // In general, the simplest (and quite optimal) algorithm is
    // checking on which side of the half-plane created by the edges the point is.

    Vector2 v = { x, y };

    #define SIGN(v0, v1, v2) (v0.x - v2.x) * (v1.y - v2.y) - (v1.x - v2.x) * (v0.y - v2.y)

    float d0 = SIGN(v, v0, v1);
    float d1 = SIGN(v, v1, v2);
    float d2 = SIGN(v, v2, v0);

    #undef SIGN

    // float d0 = (v.x - v1.x) * (v0.y - v1.y) - (v0.x - v1.x) * (v.y - v1.y);
    // float d1 = (v.x - v2.x) * (v1.y - v2.y) - (v1.x - v2.x) * (v.y - v2.y);
    // float d2 = (v.x - v0.x) * (v2.y - v0.y) - (v2.x - v0.x) * (v.y - v0.y);

    bool neg = (d0 < 0) || (d1 < 0) || (d2 < 0);
    bool pos = (d0 > 0) || (d1 > 0) || (d2 > 0);

    return !(neg && pos);
}
static inline float TriangleBarycentric(Vector3 v0, Vector3 v1, Vector3 v2, float x, float y)
{
    // TODO check

    // <   0.000000,  +64.579498, +1.000000>
    // <+127.000000,  +64.579498, +1.000000>
    // <+127.000000, +127.000000, +0.884352>
    // <  +2.000000,  +64.000000, +1.001074>
    // bad +1.001074

    // <+109.000000, +62.000000, +0.987062>
    // <+117.000000, +71.000000, +0.986772>
    // <+118.000000, +72.000000, +0.985751>
    // <+116.000000, +72.000000, +1.003553>
    // bad +1.003553

    float det = (v1.y - v2.y) * (v0.x - v2.x) + (v2.x - v1.x) * (v0.y - v2.y);

    if (det == 0) return 1;

    float l1 =  (v1.y - v2.y) * (   x - v2.x) + (v2.x - v1.x) * (   y - v2.y);
    float l2 =  (v2.y - v0.y) * (   x - v2.x) + (v0.x - v2.x) * (   y - v2.y);

    l1 /= det;
    l2 /= det;

    float l3 = 1.0f - l1 - l2;

    float result =
        l1 * v0.z +
        l2 * v1.z +
        l3 * v2.z;

    return result;
}

static inline bool Hiden(Vector3 pos, float radius, Matrix view, float far)
{
    Vector3 pos2 = MatrixMultiply3L(pos, view);
    if (pos2.z < -radius)                                 return true;
    if (pos2.z > +radius + far)                           return true;
    if (Vector3RotateY(pos2, -MATH_PI_DIV_4).x < -radius) return true;
    if (Vector3RotateY(pos2, +MATH_PI_DIV_4).x > +radius) return true;
    if (Vector3RotateX(pos2, +MATH_PI_DIV_4).y < -radius) return true;
    if (Vector3RotateX(pos2, -MATH_PI_DIV_4).y > +radius) return true;
    return false;
}

static inline bool ClipInFrustum(Vector4 p)
{
    return
    (-p.w <= p.x && p.x <= p.w) &&
    (-p.w <= p.y && p.y <= p.w) &&
    (-p.w <= p.z && p.z <= p.w);
}

static inline bool ClipLineWClipSpace(Vector4* p0, Vector4* p1)
{
    int flags = 0;

    if (p0->w < 0) flags += 1;
    if (p1->w < 0) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t0 = p0->w;
            float t1 = p1->w;

            float t = t0 / (t0 - t1);

            *p0 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w;
            float t1 = p1->w;

            float t = t0 / (t0 - t1);

            *p1 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool ClipLineBackClipSpace(Vector4* p0, Vector4* p1)
{
    int flags = 0;

    if (p0->z < -p0->w) flags += 1;
    if (p1->z < -p1->w) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t0 = p0->w + p0->z;
            float t1 = p1->w + p1->z;

            float t = t0 / (t0 - t1);

            *p0 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w + p0->z;
            float t1 = p1->w + p1->z;

            float t = t0 / (t0 - t1);

            *p1 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool ClipLineFrontClipSpace(Vector4* p0, Vector4* p1)
{
    int flags = 0;

    if (p0->z > p0->w) flags += 1;
    if (p1->z > p1->w) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t0 = p0->w - p0->z;
            float t1 = p1->w - p1->z;

            float t = t0 / (t0 - t1);

            *p0 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w - p0->z;
            float t1 = p1->w - p1->z;

            float t = t0 / (t0 - t1);

            *p1 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool ClipLineLeftClipSpace(Vector4* p0, Vector4* p1)
{
    int flags = 0;

    if (p0->x < -p0->w) flags += 1;
    if (p1->x < -p1->w) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t0 = p0->w + p0->x;
            float t1 = p1->w + p1->x;

            float t = t0 / (t0 - t1);

            *p0 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w + p0->x;
            float t1 = p1->w + p1->x;

            float t = t0 / (t0 - t1);

            *p1 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool ClipLineRightClipSpace(Vector4* p0, Vector4* p1)
{
    int flags = 0;

    if (p0->x > p0->w) flags += 1;
    if (p1->x > p1->w) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t0 = p0->w - p0->x;
            float t1 = p1->w - p1->x;

            float t = t0 / (t0 - t1);

            *p0 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w - p0->x;
            float t1 = p1->w - p1->x;

            float t = t0 / (t0 - t1);

            *p1 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool ClipLineDownClipSpace(Vector4* p0, Vector4* p1)
{
    int flags = 0;

    if (p0->y < -p0->w) flags += 1;
    if (p1->y < -p1->w) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t0 = p0->w + p0->y;
            float t1 = p1->w + p1->y;

            float t = t0 / (t0 - t1);

            *p0 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w + p0->y;
            float t1 = p1->w + p1->y;

            float t = t0 / (t0 - t1);

            *p1 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool ClipLineUpClipSpace(Vector4* p0, Vector4* p1)
{
    int flags = 0;

    if (p0->y > p0->w) flags += 1;
    if (p1->y > p1->w) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t0 = p0->w - p0->y;
            float t1 = p1->w - p1->y;

            float t = t0 / (t0 - t1);

            *p0 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w - p0->y;
            float t1 = p1->w - p1->y;

            float t = t0 / (t0 - t1);

            *p1 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}

static inline void ClipPoligonWClipSpace(Vector4* input, Vector4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector4* p0 = &input[initCount - 1];
    if (p0->w < 0) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector4* p1 = &input[i];
        if (p1->w < 0) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector4 newPoint;

                float t0 = p0->w;
                float t1 = p1->w;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.w = 0;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector4 newPoint;

                float t0 = p0->w;
                float t1 = p1->w;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.w = 0;

                output[index] = *p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
static inline void ClipPoligonBackClipSpace(Vector4* input, Vector4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector4* p0 = &input[initCount - 1];
    if (p0->z < -p0->w) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector4* p1 = &input[i];
        if (p1->z < -p1->w) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector4 newPoint;

                float t0 = p0->w + p0->z;
                float t1 = p1->w + p1->z;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.z = -newPoint.w;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector4 newPoint;

                float t0 = p0->w + p0->z;
                float t1 = p1->w + p1->z;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.z = -newPoint.w;

                output[index] = *p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
static inline void ClipPoligonFrontClipSpace(Vector4* input, Vector4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector4* p0 = &input[initCount - 1];
    if (p0->z > p0->w) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector4* p1 = &input[i];
        if (p1->z > p1->w) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector4 newPoint;

                float t0 = p0->w - p0->z;
                float t1 = p1->w - p1->z;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.z = newPoint.w;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector4 newPoint;

                float t0 = p0->w - p0->z;
                float t1 = p1->w - p1->z;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.z = newPoint.w;

                output[index] = *p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
static inline void ClipPoligonLeftClipSpace(Vector4* input, Vector4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector4* p0 = &input[initCount - 1];
    if (p0->x < -p0->w) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector4* p1 = &input[i];
        if (p1->x < -p1->w) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector4 newPoint;

                float t0 = p0->w + p0->x;
                float t1 = p1->w + p1->x;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.x = -newPoint.w;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector4 newPoint;

                float t0 = p0->w + p0->x;
                float t1 = p1->w + p1->x;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.x = -newPoint.w;

                output[index] = *p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
static inline void ClipPoligonRightClipSpace(Vector4* input, Vector4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector4* p0 = &input[initCount - 1];
    if (p0->x > p0->w) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector4* p1 = &input[i];
        if (p1->x > p1->w) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector4 newPoint;

                float t0 = p0->w - p0->x;
                float t1 = p1->w - p1->x;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.x = newPoint.w;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector4 newPoint;

                float t0 = p0->w - p0->x;
                float t1 = p1->w - p1->x;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.x = newPoint.w;

                output[index] = *p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
static inline void ClipPoligonDownClipSpace(Vector4* input, Vector4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector4* p0 = &input[initCount - 1];
    if (p0->y < -p0->w) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector4* p1 = &input[i];
        if (p1->y < -p1->w) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector4 newPoint;

                float t0 = p0->w + p0->y;
                float t1 = p1->w + p1->y;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.y = -newPoint.w;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector4 newPoint;

                float t0 = p0->w + p0->y;
                float t1 = p1->w + p1->y;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.y = -newPoint.w;

                output[index] = *p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
static inline void ClipPoligonUpClipSpace(Vector4* input, Vector4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector4* p0 = &input[initCount - 1];
    if (p0->y > p0->w) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector4* p1 = &input[i];
        if (p1->y > p1->w) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector4 newPoint;

                float t0 = p0->w - p0->y;
                float t1 = p1->w - p1->y;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.y = newPoint.w;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector4 newPoint;

                float t0 = p0->w - p0->y;
                float t1 = p1->w - p1->y;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.y = newPoint.w;

                output[index] = *p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
static inline void ClipPoligonClipSpaceDiv(Vector4* vs, int vertexCount)
{
    for (int i = 0; i < vertexCount; i++)
    {
        vs[i].x /= vs[i].w;
        vs[i].y /= vs[i].w;
        vs[i].z /= vs[i].w;

        // linear interpolation, in clipping, accumulates error
        // values, in NDC, can become slightly outside
        // duno what to do about that, I just clamp them
        vs[i].x = MathClamp(vs[i].x, -1, +1);
        vs[i].y = MathClamp(vs[i].y, -1, +1);
        vs[i].z = MathClamp(vs[i].z, -1, +1);
    }
}

static inline uint32_t ColorCreateRgb(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t result = 0;
    result += r; result <<= 8;
    result += g; result <<= 8;
    result += b;
    return result;
}
static inline uint32_t ColorCreateBwFloat(float t)
{
    // try me, see what happens
    // uint8_t r = (COLOR_WHITE >> 8 * 2) * t;
    // uint8_t g = (COLOR_WHITE >> 8 * 1) * t;
    // uint8_t b = (COLOR_WHITE >> 8 * 0) * t;
    // return ColorCreateRgb(r, g, b);

    uint8_t byte = (uint8_t)(255.0f * t);
    return ColorCreateRgb(byte, byte, byte);
}

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

static inline void BitmapReset(Bitmap* bitmap)
{
    int size = bitmap->width * bitmap->height;
    for (int i = 0; i < size; i++)
        bitmap->buffer[i] = 1;
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
}

static inline void BitmapSetProj(Bitmap* bitmap, float near, float far)
{
    bitmap->neari = 1.0f / near;
    bitmap->far = far;
    bitmap->proj = MatrixProjPerspective1(bitmap->width, bitmap->height, near, far);
}

static inline void BitmapSetPixel(Bitmap* bitmap, int x, int y, uint32_t color)
{
    assert(0 <= x && x < bitmap->width);
    assert(0 <= y && y < bitmap->height);

    int i = x + y * bitmap->width;

    ((uint32_t*)bitmap->buffer)[i] = color;
}
static inline void BitmapSetPixelZ(Bitmap* bitmap, int x, int y, float z)
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
    BitmapSetPixelZ(bitmap, v0.x, v0.y, v0.z);
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

    if (dx > dy)
    {
        float offset = (z1 - z0) / dx;

        int err = dx - dx / 2;

        for (int i = 0; i < dx; i++)
        {
            BitmapSetPixelZ(bitmap, x0, y0, z0);

                          { err -= dy; x0 += sx; }
            if (err <= 0) { err += dx; y0 += sy; }

            z0 += offset;
        }

        BitmapSetPixelZ(bitmap, x0, y0, z1);
    }
    else
    {
        float offset = (z1 - z0) / dy;

        int err = dy - dy / 2;

        for (int i = 0; i < dy; i++)
        {
            BitmapSetPixelZ(bitmap, x0, y0, z0);

                          { err -= dx; y0 += sy; }
            if (err <= 0) { err += dy; x0 += sx; }

            z0 += offset;
        }

        BitmapSetPixelZ(bitmap, x0, y0, z1);
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

    int maxx = fmaxf(v0.x, fmaxf(v1.x, v2.x));
    int minx = fminf(v0.x, fminf(v1.x, v2.x));
    int maxy = fmaxf(v0.y, fmaxf(v1.y, v2.y));
    int miny = fminf(v0.y, fminf(v1.y, v2.y));

    for (int y = miny; y <= maxy; y++)
    for (int x = minx; x <= maxx; x++)
    {
        if (!TriangleIsInside(v0, v1, v2, x, y)) continue;
        float z = TriangleBarycentric(v0, v1, v2, x, y);
        BitmapSetPixelZ(bitmap, x, y, z);
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



static inline void UpdateShadows1(void (*draw)(Bitmap* bitmap), SpotLight* light)
{
    Vector3 eye = Vector3Neg(light->pos);
    Matrix mat = MatrixTranslate(eye);

    light->matf = MatrixMultiply(mat, MatrixRotateY(MATH_PI_DIV_2*0));
    light->matr = MatrixMultiply(mat, MatrixRotateY(MATH_PI_DIV_2*1));
    light->matb = MatrixMultiply(mat, MatrixRotateY(MATH_PI_DIV_2*2));
    light->matl = MatrixMultiply(mat, MatrixRotateY(MATH_PI_DIV_2*3));
    light->matu = MatrixMultiply(mat, MatrixRotateX(-MATH_PI_DIV_2));
    light->matd = MatrixMultiply(mat, MatrixRotateX(+MATH_PI_DIV_2));

    Bitmap bf; bf.buffer = light->buff; bf.view = light->matf; bf.proj = SHADOW_MAP_PROJ; bf.width = SHADOW_MAP_SIZE; bf.height = SHADOW_MAP_SIZE; bf.far = LIGHT_MAX_DIST;
    Bitmap br; br.buffer = light->bufr; br.view = light->matr; br.proj = SHADOW_MAP_PROJ; br.width = SHADOW_MAP_SIZE; br.height = SHADOW_MAP_SIZE; br.far = LIGHT_MAX_DIST;
    Bitmap bb; bb.buffer = light->bufb; bb.view = light->matb; bb.proj = SHADOW_MAP_PROJ; bb.width = SHADOW_MAP_SIZE; bb.height = SHADOW_MAP_SIZE; bb.far = LIGHT_MAX_DIST;
    Bitmap bl; bl.buffer = light->bufl; bl.view = light->matl; bl.proj = SHADOW_MAP_PROJ; bl.width = SHADOW_MAP_SIZE; bl.height = SHADOW_MAP_SIZE; bl.far = LIGHT_MAX_DIST;
    Bitmap bu; bu.buffer = light->bufu; bu.view = light->matu; bu.proj = SHADOW_MAP_PROJ; bu.width = SHADOW_MAP_SIZE; bu.height = SHADOW_MAP_SIZE; bu.far = LIGHT_MAX_DIST;
    Bitmap bd; bd.buffer = light->bufd; bd.view = light->matd; bd.proj = SHADOW_MAP_PROJ; bd.width = SHADOW_MAP_SIZE; bd.height = SHADOW_MAP_SIZE; bd.far = LIGHT_MAX_DIST;

    BitmapReset(&bf); draw(&bf);
    BitmapReset(&br); draw(&br);
    BitmapReset(&bb); draw(&bb);
    BitmapReset(&bl); draw(&bl);
    BitmapReset(&bu); draw(&bu);
    BitmapReset(&bd); draw(&bd);
}
static inline void UpdateShadows2(void (*draw)(Bitmap* bitmap), LightData* lightData)
{
    for (int i = 0; i < lightData->lightsc; i++)
        UpdateShadows1(draw, &lightData->lights[i]);
}

static inline float CalcLight1(Vector3 surPos, float lum, Vector3 lightPos)
{
    float t;

    float dist1 = Vector3Distance(surPos, lightPos);
    float dist2 = LIGHT_MAX_DIST;
    t = dist1 / dist2;
    t = t < 1 ? (1 - t) * lum : 0;

    return t;
}
static inline float CalcLight4(Vector3 surPos, float lum, Vector3 lightPos, float* buffer, Matrix view)
{
    Vector3 ndc = WorldToNdc(surPos, view, SHADOW_MAP_PROJ);

    if (ndc.x < -1 || +1 < ndc.x) return 0.0f;
    if (ndc.y < -1 || +1 < ndc.y) return 0.0f;
    // if (ndc.z < -1 || +1 < ndc.z) return 0.0f;

    if (ndc.z < -1) return lum;
    if (ndc.z > +1) return 0.0f;

    int x = (+ndc.x + 1.0f) / 2.0f * (SHADOW_MAP_SIZE - 1);
    int y = (-ndc.y + 1.0f) / 2.0f * (SHADOW_MAP_SIZE - 1);

    int i = x + y * SHADOW_MAP_SIZE;

    float z1 = buffer[i] + SHADOW_MAP_BIAS;
    float z2 = ndc.z;

    if (z1 < z2) return 0.0f;

    float t;

    float dist1 = Vector3Distance(surPos, lightPos);
    float dist2 = LIGHT_MAX_DIST;
    t = dist1 / dist2;
    t = t < 1 ? (1 - t) * lum : 0;

    return t;
}

static inline float CalcLightSpot(Vector3 surPos, SpotLight* light)
{
    int sectorId = 0;
    {
        Vector3 v = Vector3Sub(surPos, light->pos);

        float absx = fabsf(v.x);
        float absy = fabsf(v.y);
        float absz = fabsf(v.z);

        float max; char axis;

                        { max = absx; axis = 'x'; };
        if (max < absy) { max = absy; axis = 'y'; };
        if (max < absz) { max = absz; axis = 'z'; };

        switch (axis)
        {
            case 'x': sectorId = v.x < 0 ? 0 : 1; break;
            case 'y': sectorId = v.y < 0 ? 2 : 3; break;
            case 'z': sectorId = v.z < 0 ? 4 : 5; break;
        }
    }

    float t = 0;
    {
        switch (sectorId)
        {
            case 0: { t = CalcLight4(surPos, light->lum, light->pos, light->bufl, light->matl); break; }
            case 1: { t = CalcLight4(surPos, light->lum, light->pos, light->bufr, light->matr); break; }
            case 2: { t = CalcLight4(surPos, light->lum, light->pos, light->bufd, light->matd); break; }
            case 3: { t = CalcLight4(surPos, light->lum, light->pos, light->bufu, light->matu); break; }
            case 4: { t = CalcLight4(surPos, light->lum, light->pos, light->bufb, light->matb); break; }
            case 5: { t = CalcLight4(surPos, light->lum, light->pos, light->buff, light->matf); break; }
        }
    }

    return t;
}
static inline float CalcLightSpotNoShadow(Vector3 surPos, SpotLight* light)
{
    return CalcLight1(surPos, light->lum, light->pos);
}

static inline float CalcLight(Vector3 surPos, LightData* lightData)
{
    float result = 0;

    for (int i = 0; i < lightData->lightsc; i++)
    {
        SpotLight* light = &lightData->lights[i];

        float t = CalcLightSpot(surPos, light);

        result =
        result > t ?
        result : t;
    }

    return result;
}
static inline float CalcLightNoShadow(Vector3 surPos, LightData* lightData)
{
    float result = 0;

    for (int i = 0; i < lightData->lightsc; i++)
    {
        SpotLight* light = &lightData->lights[i];

        float t = CalcLightSpotNoShadow(surPos, light);

        result =
        result > t ?
        result : t;
    }

    return result;
}

static inline void ApplyLight(Bitmap* bitmap, LightData* lightData)
{
    uint32_t* pixels = (uint32_t*)bitmap->buffer;

    Matrix viewi = MatrixInvert(bitmap->view);
    Matrix proji = MatrixInvert(bitmap->proj);

    for (int y = 0; y < bitmap->height; y++)
    for (int x = 0; x < bitmap->width;  x++)
    {
        int i = x + y * bitmap->width;
        float z = bitmap->buffer[i];
        if (z == 1) { pixels[i] = ColorCreateBwFloat(0); continue; }
        Vector3 sp = (Vector3){ (float)x, (float)y, z };
        Vector3 ndc = ScreenSpaceToNdc(sp, bitmap->width-1, bitmap->height-1);
        Vector3 surPos = NdcToWorld(ndc, viewi, proji);
        float t = CalcLight(surPos, lightData);
        pixels[i] = ColorCreateBwFloat(t);
    }
}
static inline void ApplyLightNoShadow(Bitmap* bitmap, LightData* lightData)
{
    uint32_t* pixels = (uint32_t*)bitmap->buffer;

    Matrix viewi = MatrixInvert(bitmap->view);
    Matrix proji = MatrixInvert(bitmap->proj);

    for (int y = 0; y < bitmap->height; y++)
    for (int x = 0; x < bitmap->width;  x++)
    {
        int i = x + y * bitmap->width;
        float z = bitmap->buffer[i];
        if (z == 1) { pixels[i] = ColorCreateBwFloat(0); continue; }
        Vector3 sp = (Vector3){ (float)x, (float)y, z };
        Vector3 ndc = ScreenSpaceToNdc(sp, bitmap->width-1, bitmap->height-1);
        Vector3 surPos = NdcToWorld(ndc, viewi, proji);
        float t = CalcLightNoShadow(surPos, lightData);
        pixels[i] = ColorCreateBwFloat(t);
    }
}

LightData _LightData1_data = {};
int _LightData1_max = 0;
static inline void LightData1RemoveLight()
{
    _LightData1_data.lightsc = 0;
}
static inline void LightData1AddLight(Vector3 pos, float lum)
{
    int size = _LightData1_data.lightsc + 1;

    if (_LightData1_max < size)
    {
        _LightData1_max = size * 2;
        _LightData1_data.lights = (SpotLight*)realloc(_LightData1_data.lights, _LightData1_max*sizeof(SpotLight));
    }

    SpotLight* light = &_LightData1_data.lights[_LightData1_data.lightsc];

    light->pos = pos;
    light->lum = lum;

    _LightData1_data.lightsc++;
}
static inline void LightData1UpdateShadows(void (*draw)(Bitmap* bitmap))
{
    UpdateShadows2(draw, &_LightData1_data);
}
static inline void LightData1ApplyLight(Bitmap* bitmap)
{
    ApplyLight(bitmap, &_LightData1_data);
}
static inline void LightData1ApplyLightNoShadow(Bitmap* bitmap)
{
    ApplyLightNoShadow(bitmap, &_LightData1_data);
}



const Vector3 ModelCubeVerteces[8] =
{
    { -0.5f, -0.5f, -0.5f },
    { -0.5f, -0.5f,  0.5f },
    { -0.5f,  0.5f, -0.5f },
    { -0.5f,  0.5f,  0.5f },
    {  0.5f, -0.5f, -0.5f },
    {  0.5f, -0.5f,  0.5f },
    {  0.5f,  0.5f, -0.5f },
    {  0.5f,  0.5f,  0.5f }
};
const int ModelCubeIndecesLine[12][2] =
{
    {0, 1},
    {1, 5},
    {5, 4},
    {4, 0},
    {2, 3},
    {3, 7},
    {7, 6},
    {6, 2},
    {0, 2},
    {1, 3},
    {5, 7},
    {4, 6}
};
const int ModelCubeIndecesTriangle[12][3] =
{
    {2, 6, 4},
    {4, 0, 2},
    {6, 7, 5},
    {5, 4, 6},
    {7, 3, 1},
    {1, 5, 7},
    {3, 2, 0},
    {0, 1, 3},
    {1, 0, 4},
    {4, 5, 1},
    {3, 7, 6},
    {6, 2, 3}
};
const int ModelCubeIndecesQuad[6][4] =
{
    {2, 6, 4, 0},
    {6, 7, 5, 4},
    {7, 3, 1, 5},
    {3, 2, 0, 1},
    {1, 0, 4, 5},
    {3, 7, 6, 2}
};

const Vector3 ModelSphereVerteces[32] =
{
    {  0.000000,  0.500000, -0.000000  },
    {  0.250000,  0.433000, -0.000000  },
    {  0.433000,  0.250000, -0.000000  },
    {  0.500000,  0.000000,  0.000000  },
    {  0.433000, -0.250000,  0.000000  },
    {  0.250000, -0.433000,  0.000000  },
    {  0.000000, -0.500000,  0.000000  },
    {  0.125000,  0.433000,  0.216500  },
    {  0.216500,  0.250000,  0.375000  },
    {  0.250000,  0.000000,  0.433000  },
    {  0.216500, -0.250000,  0.375000  },
    {  0.125000, -0.433000,  0.216500  },
    { -0.125000,  0.433000,  0.216500  },
    { -0.216500,  0.250000,  0.375000  },
    { -0.250000,  0.000000,  0.433000  },
    { -0.216500, -0.250000,  0.375000  },
    { -0.125000, -0.433000,  0.216500  },
    { -0.250000,  0.433000, -0.000000  },
    { -0.433000,  0.250000, -0.000000  },
    { -0.500000,  0.000000,  0.000000  },
    { -0.433000, -0.250000,  0.000000  },
    { -0.250000, -0.433000,  0.000000  },
    { -0.125000,  0.433000, -0.216500  },
    { -0.216500,  0.250000, -0.375000  },
    { -0.250000, -0.000000, -0.433000  },
    { -0.216500, -0.250000, -0.375000  },
    { -0.125000, -0.433000, -0.216500  },
    {  0.125000,  0.433000, -0.216500  },
    {  0.216500,  0.250000, -0.375000  },
    {  0.250000, -0.000000, -0.433000  },
    {  0.216500, -0.250000, -0.375000  },
    {  0.125000, -0.433000, -0.216500  }
};
const int ModelSphereIndecesTriangles[60][3] =
{
    {0, 7, 1},
    {1, 7, 8},
    {1, 8, 2},
    {2, 8, 9},
    {2, 9, 3},
    {3, 9, 10},
    {3, 10, 4},
    {4, 10, 11},
    {4, 11, 5},
    {5, 11, 6},
    {0, 12, 7},
    {7, 12, 13},
    {7, 13, 8},
    {8, 13, 14},
    {8, 14, 9},
    {9, 14, 15},
    {9, 15, 10},
    {10, 15, 16},
    {10, 16, 11},
    {11, 16, 6},
    {0, 17, 12},
    {12, 17, 18},
    {13, 18, 19},
    {14, 19, 20},
    {15, 20, 21},
    {12, 18, 13},
    {13, 19, 14},
    {14, 20, 15},
    {15, 21, 16},
    {16, 21, 6},
    {0, 22, 17},
    {17, 22, 23},
    {18, 23, 24},
    {19, 24, 25},
    {20, 25, 26},
    {17, 23, 18},
    {18, 24, 19},
    {19, 25, 20},
    {20, 26, 21},
    {21, 26, 6},
    {0, 27, 22},
    {22, 27, 28},
    {23, 28, 29},
    {24, 29, 30},
    {25, 30, 31},
    {22, 28, 23},
    {23, 29, 24},
    {24, 30, 25},
    {25, 31, 26},
    {26, 31, 6},
    {0, 1, 27},
    {27, 1, 2},
    {28, 2, 3},
    {29, 3, 4},
    {30, 4, 5},
    {27, 2, 28},
    {28, 3, 29},
    {29, 4, 30},
    {30, 5, 31},
    {31, 5, 6},
};



static inline void BitmapExtDrawQuad(Bitmap* bitmap, Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3)
{
    BitmapDrawTriangle(bitmap, v0, v1, v2);
    BitmapDrawTriangle(bitmap, v2, v3, v0);
}
static inline void BitmapExtDrawBound(Bitmap* bitmap, Vector3* vs, int vsc)
{
    float maxx;
    float maxy;
    float maxz;
    float minx;
    float miny;
    float minz;

    for (int i = 0; i < vsc; i++)
    {
        Vector3 v = vs[i];
        maxx = fmaxf(maxx, v.x);
        maxy = fmaxf(maxy, v.y);
        maxz = fmaxf(maxz, v.z);
        minx = fminf(minx, v.x);
        miny = fminf(miny, v.y);
        minz = fminf(minz, v.z);
    }

    Vector3 p0 = { minx, miny, minz };
    Vector3 p1 = { minx, miny, maxz };
    Vector3 p2 = { minx, maxy, minz };
    Vector3 p3 = { minx, maxy, maxz };
    Vector3 p4 = { maxx, miny, minz };
    Vector3 p5 = { maxx, miny, maxz };
    Vector3 p6 = { maxx, maxy, minz };
    Vector3 p7 = { maxx, maxy, maxz };

    BitmapDrawLine(bitmap, p0, p1);
    BitmapDrawLine(bitmap, p1, p5);
    BitmapDrawLine(bitmap, p5, p4);
    BitmapDrawLine(bitmap, p4, p0);
    BitmapDrawLine(bitmap, p2, p3);
    BitmapDrawLine(bitmap, p3, p7);
    BitmapDrawLine(bitmap, p7, p6);
    BitmapDrawLine(bitmap, p6, p2);
    BitmapDrawLine(bitmap, p0, p2);
    BitmapDrawLine(bitmap, p1, p3);
    BitmapDrawLine(bitmap, p5, p7);
    BitmapDrawLine(bitmap, p4, p6);
}
static inline void BitmapExtDrawCubeMat(Bitmap* bitmap, Matrix mat)
{
    #define DRAW(INDEX)                            \
    {                                              \
        int i0 = ModelCubeIndecesQuad[INDEX][0];   \
        int i1 = ModelCubeIndecesQuad[INDEX][1];   \
        int i2 = ModelCubeIndecesQuad[INDEX][2];   \
        int i3 = ModelCubeIndecesQuad[INDEX][3];   \
        Vector3 p0 = ModelCubeVerteces[i0];        \
        Vector3 p1 = ModelCubeVerteces[i1];        \
        Vector3 p2 = ModelCubeVerteces[i2];        \
        Vector3 p3 = ModelCubeVerteces[i3];        \
        p0 = MatrixMultiply3L(p0, mat);            \
        p1 = MatrixMultiply3L(p1, mat);            \
        p2 = MatrixMultiply3L(p2, mat);            \
        p3 = MatrixMultiply3L(p3, mat);            \
        BitmapExtDrawQuad(bitmap, p0, p1, p2, p3); \
    }                                              \

    DRAW(0)
    DRAW(1)
    DRAW(2)
    DRAW(3)
    DRAW(4)
    DRAW(5)

    #undef DRAW
}
static inline void BitmapExtDrawCube(Bitmap* bitmap, Vector3 pos, Vector3 rot, Vector3 scale)
{
    Matrix mat = MatrixWorld(pos, rot, scale);
    BitmapExtDrawCubeMat(bitmap, mat);
}
static inline void BitmapExtDrawSphere(Bitmap* bitmap, Vector3 pos)
{
    if (Hiden(pos, 1.0f, bitmap->view, bitmap->far)) return;

    for (size_t i = 0; i < 60; i++)
    {
        int i0 = ModelSphereIndecesTriangles[i][0];
        int i1 = ModelSphereIndecesTriangles[i][1];
        int i2 = ModelSphereIndecesTriangles[i][2];
        Vector3 v0 = ModelSphereVerteces[i0];
        Vector3 v1 = ModelSphereVerteces[i1];
        Vector3 v2 = ModelSphereVerteces[i2];
        v0 = Vector3Add(v0, pos);
        v1 = Vector3Add(v1, pos);
        v2 = Vector3Add(v2, pos);
        BitmapDrawTriangle(bitmap, v0, v1, v2);
    }
}

static inline void BitmapExtDrawBorder(Bitmap* bitmap, float color)
{
    int x = bitmap->width - 1;
    int y = bitmap->height - 1;
    for (int i = 0; i < bitmap->width;  i++) BitmapSetPixel(bitmap, i, 0, color);
    for (int i = 0; i < bitmap->width;  i++) BitmapSetPixel(bitmap, i, y, color);
    for (int i = 0; i < bitmap->height; i++) BitmapSetPixel(bitmap, 0, i, color);
    for (int i = 0; i < bitmap->height; i++) BitmapSetPixel(bitmap, x, i, color);
}
static inline void BitmapExtDrawCross(Bitmap* bitmap, float color)
{
    for (int i = 0; i < bitmap->width;  i++) BitmapSetPixel(bitmap, i, (bitmap->height-1) / 2, color);
    for (int i = 0; i < bitmap->height; i++) BitmapSetPixel(bitmap, (bitmap->width-1) / 2, i, color);
}
static inline void BitmapExtDrawChar(Bitmap* bitmap, int x, int y, char c)
{
    #define P(x2, y2) BitmapSetPixel(bitmap, x+x2, y+y2, 0x00FFFFFF);

    switch (c)
    {
        case '0':
        {
            P(0,0) P(1,0) P(2,0)
            P(0,1)        P(2,1)
            P(0,2)        P(2,2)
            P(0,3)        P(2,3)
            P(0,4) P(1,4) P(2,4)
            break;
        }
        case '1':
        {
                   P(1,0)
            P(0,1) P(1,1)
                   P(1,2)
                   P(1,3)
            P(0,4) P(1,4) P(2,4)
            break;
        }
        case '2':
        {
            P(0,0) P(1,0) P(2,0)
                          P(2,1)
                   P(1,2)
            P(0,3)
            P(0,4) P(1,4) P(2,4)
            break;
        }
        case '3':
        {
            P(0,0) P(1,0) P(2,0)
                          P(2,1)
            P(0,2) P(1,2) P(2,2)
                          P(2,3)
            P(0,4) P(1,4) P(2,4)
            break;
        }
        case '4':
        {
            P(0,0)        P(2,0)
            P(0,1)        P(2,1)
            P(0,2) P(1,2) P(2,2)
                          P(2,3)
                          P(2,4)
            break;
        }
        case '5':
        {
            P(0,0) P(1,0) P(2,0)
            P(0,1)
            P(0,2) P(1,2) P(2,2)
                          P(2,3)
            P(0,4) P(1,4) P(2,4)
            break;
        }
        case '6':
        {
            P(0,0) P(1,0) P(2,0)
            P(0,1)
            P(0,2) P(1,2) P(2,2)
            P(0,3)        P(2,3)
            P(0,4) P(1,4) P(2,4)
            break;
        }
        case '7':
        {
            P(0,0) P(1,0) P(2,0)
                          P(2,1)
                   P(1,2)
                   P(1,3)
                   P(1,4)
            break;
        }
        case '8':
        {
            P(0,0) P(1,0) P(2,0)
            P(0,1)        P(2,1)
            P(0,2) P(1,2) P(2,2)
            P(0,3)        P(2,3)
            P(0,4) P(1,4) P(2,4)
            break;
        }
        case '9':
        {
            P(0,0) P(1,0) P(2,0)
            P(0,1)        P(2,1)
            P(0,2) P(1,2) P(2,2)
                          P(2,3)
            P(0,4) P(1,4) P(2,4)
            break;
        }
        default: break;
    }

    #undef P
}

static inline void BitmapExtDrawGrid(Bitmap* bitmap)
{
    int count = 10;

    for (int i = 0; i < count; i++)
    {
        float offset = (float)(i-count/2);
        Vector3 v0 = { offset, 0, -(float)count };
        Vector3 v1 = { offset, 0, +(float)count };
        BitmapDrawLine(bitmap, v0, v1);
    }

    for (int i = 0; i < count; i++)
    {
        float offset = (float)(i-count/2);
        Vector3 v0 = { -(float)count, 0, offset };
        Vector3 v1 = { +(float)count, 0, offset };
        BitmapDrawLine(bitmap, v0, v1);
    }
}
static inline void BitmapExtDrawPlane(Bitmap* bitmap)
{
    float size = 10;

    Vector3 p0 = { +size, 0, +size };
    Vector3 p1 = { +size, 0, -size };
    Vector3 p2 = { -size, 0, -size };
    Vector3 p3 = { -size, 0, +size };

    BitmapExtDrawQuad(bitmap, p0, p1, p2, p3);
}

static inline void BitmapExtDrawCubeWire(Bitmap* bitmap, Vector3 pos, Vector3 rot, Vector3 scale)
{
    Matrix model = MatrixWorld(pos, rot, scale);

    for (int i = 0; i < 12; i++)
    {
        int i0 = ModelCubeIndecesLine[i][0];
        int i1 = ModelCubeIndecesLine[i][1];
        Vector3 v0 = ModelCubeVerteces[i0];
        Vector3 v1 = ModelCubeVerteces[i1];
        v0 = MatrixMultiply3L(v0, model);
        v1 = MatrixMultiply3L(v1, model);
        BitmapDrawLine(bitmap, v0, v1);
    }
}
