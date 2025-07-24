#pragma once

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <float.h>
#include <math.h>

#define _ZL_PI        (float)3.14159265358979323846
#define _ZL_PI_MUL_2  (float)6.28318530717958647692
#define _ZL_PI_DIV_2  (float)1.57079632679489661923
#define _ZL_PI_DIV_4  (float)0.78539816339744830961

#define ZL_LIGHT_MAX_DIST 15
#define ZL_SHADOW_MAP_SIZE 128
#define ZL_SHADOW_MAP_BIAS 0.001f

#define _ZL_SHADOW_MAP_PROJ_MACRO(near, far) ((zlmat)\
{{\
    {1, 0, 0, 0},\
    {0, 1, 0, 0},\
    {0, 0,  ((far+near)   / (far-near)), 1},\
    {0, 0, -((near*2*far) / (far-near)), 0}\
}})
#define _ZL_SHADOW_MAP_PROJ _ZL_SHADOW_MAP_PROJ_MACRO(0.1f, ZL_LIGHT_MAX_DIST)

typedef struct zlvec3
{
    float x, y, z;
}
zlvec3;
typedef struct zlvec4
{
    float x, y, z, w;
}
zlvec4;
typedef struct zlmat
{
    float m[4][4];
}
zlmat;
typedef struct zlbitmap
{
    int width;
    int height;
    zlmat view;
    zlmat proj;
    float neari;
    float far;
    float* buffer;
}
zlbitmap;
typedef struct _zlSpotLight
{
    zlvec3 pos;
    float lum;
    float bufl[ZL_SHADOW_MAP_SIZE*ZL_SHADOW_MAP_SIZE]; zlmat matl;
    float bufr[ZL_SHADOW_MAP_SIZE*ZL_SHADOW_MAP_SIZE]; zlmat matr;
    float bufd[ZL_SHADOW_MAP_SIZE*ZL_SHADOW_MAP_SIZE]; zlmat matd;
    float bufu[ZL_SHADOW_MAP_SIZE*ZL_SHADOW_MAP_SIZE]; zlmat matu;
    float bufb[ZL_SHADOW_MAP_SIZE*ZL_SHADOW_MAP_SIZE]; zlmat matb;
    float buff[ZL_SHADOW_MAP_SIZE*ZL_SHADOW_MAP_SIZE]; zlmat matf;
}
_zlSpotLight;
typedef struct _zlLightData
{
    _zlSpotLight* lights;
    int lightsc;
    int lightsmax;
}
_zlLightData;

static inline float _ZlMathClamp(float x, float min, float max)
{
    if (x < min) { return min; };
    if (x > max) { return max; };
                   return x;
}
static inline float _ZlMathLerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

static inline zlvec3 _ZlVector3Neg(zlvec3 r)
{
    r.x = -r.x;
    r.y = -r.y;
    r.z = -r.z;
    return r;
}
static inline zlvec3 _ZlVector3Add(zlvec3 l, zlvec3 r)
{
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    return l;
}
static inline zlvec3 _ZlVector3Sub(zlvec3 l, zlvec3 r)
{
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    return l;
}
static inline zlvec3 _ZlVector3Mul(zlvec3 l, float r)
{
    l.x *= r;
    l.y *= r;
    l.z *= r;
    return l;
}
static inline zlvec3 _ZlVector3Div(zlvec3 l, float r)
{
    l.x /= r;
    l.y /= r;
    l.z /= r;
    return l;
}

static inline float _ZlVector3Length(zlvec3 v)
{
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    return sqrtf(x + y + z);
}
static inline float _ZlVector3Distance(zlvec3 a, zlvec3 b)
{
    zlvec3 v = _ZlVector3Sub(a, b);
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    return sqrtf(x + y + z);
}
static inline zlvec3 _ZlVector3Normalize(zlvec3 v)
{
    // TODO remove "if (length == 0)" ?
    float length = _ZlVector3Length(v);
    if (length == 0) return v;
    return _ZlVector3Div(v, length);
}

static inline zlvec3 _ZlVector3RotateX(zlvec3 v, float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    float x = v.x;
    float y = v.y * ( cos) + v.z * ( sin);
    float z = v.y * (-sin) + v.z * ( cos);
    return (zlvec3){ x, y, z };
}
static inline zlvec3 _ZlVector3RotateY(zlvec3 v, float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    float x = v.x * ( cos) + v.z * (-sin);
    float y = v.y;
    float z = v.x * ( sin) + v.z * ( cos);
    return (zlvec3){ x, y, z };
}
static inline zlvec3 _ZlVector3RotateZ(zlvec3 v, float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    float x = v.x * ( cos) + v.y * ( sin);
    float y = v.x * (-sin) + v.y * ( cos);
    float z = v.z;
    return (zlvec3){ x, y, z };
}

static inline zlvec3 _ZlVector3Cross(zlvec3 a, zlvec3 b)
{
    float x = a.y*b.z - a.z*b.y;
    float y = a.z*b.x - a.x*b.z;
    float z = a.x*b.y - a.y*b.x;
    return (zlvec3){ x, y, z };
}

static inline float _ZlVector3Dot(zlvec3 l, zlvec3 r)
{
    float x = l.x * r.x;
    float y = l.y * r.y;
    float z = l.z * r.z;
    return x + y + z;
}
static inline float _ZlVector4Dot(zlvec4 l, zlvec4 r)
{
    float x = l.x * r.x;
    float y = l.y * r.y;
    float z = l.z * r.z;
    float w = l.w * r.w;
    return x + y + z + w;
}

static inline zlvec4 _ZlVector4Lerp(zlvec4 a, zlvec4 b, float t)
{
    a.x = _ZlMathLerp(a.x, b.x, t);
    a.y = _ZlMathLerp(a.y, b.y, t);
    a.z = _ZlMathLerp(a.z, b.z, t);
    a.w = _ZlMathLerp(a.w, b.w, t);
    return a;
}

static inline zlvec3 _ZlMatrixMultiply3L(zlvec3 v, zlmat m)
{
    zlvec4 col0 = { m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0] };
    zlvec4 col1 = { m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1] };
    zlvec4 col2 = { m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2] };

    zlvec4 row = { v.x, v.y, v.z, 1 };

    v.x = _ZlVector4Dot(row, col0);
    v.y = _ZlVector4Dot(row, col1);
    v.z = _ZlVector4Dot(row, col2);

    return v;
}
static inline zlvec4 _ZlMatrixMultiply4L(zlvec4 v, zlmat m)
{
    zlvec4 col0 = { m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0] };
    zlvec4 col1 = { m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1] };
    zlvec4 col2 = { m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2] };
    zlvec4 col3 = { m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3] };

    zlvec4 row = v;

    v.x = _ZlVector4Dot(row, col0);
    v.y = _ZlVector4Dot(row, col1);
    v.z = _ZlVector4Dot(row, col2);
    v.w = _ZlVector4Dot(row, col3);

    return v;
}

static inline zlmat _ZlMatrixIdentity()
{
    return (zlmat)
    {{
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1},
    }};
}
static inline zlmat _ZlMatrixInvert(zlmat m)
{
    zlmat result;

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
static inline zlmat _ZlMatrixMultiply(zlmat l, zlmat r)
{
    zlvec4 row0 = { l.m[0][0], l.m[0][1], l.m[0][2], l.m[0][3] };
    zlvec4 row1 = { l.m[1][0], l.m[1][1], l.m[1][2], l.m[1][3] };
    zlvec4 row2 = { l.m[2][0], l.m[2][1], l.m[2][2], l.m[2][3] };
    zlvec4 row3 = { l.m[3][0], l.m[3][1], l.m[3][2], l.m[3][3] };

    zlvec4 col0 = { r.m[0][0], r.m[1][0], r.m[2][0], r.m[3][0] };
    zlvec4 col1 = { r.m[0][1], r.m[1][1], r.m[2][1], r.m[3][1] };
    zlvec4 col2 = { r.m[0][2], r.m[1][2], r.m[2][2], r.m[3][2] };
    zlvec4 col3 = { r.m[0][3], r.m[1][3], r.m[2][3], r.m[3][3] };

    float m00 = _ZlVector4Dot(row0, col0);
    float m01 = _ZlVector4Dot(row0, col1);
    float m02 = _ZlVector4Dot(row0, col2);
    float m03 = _ZlVector4Dot(row0, col3);

    float m10 = _ZlVector4Dot(row1, col0);
    float m11 = _ZlVector4Dot(row1, col1);
    float m12 = _ZlVector4Dot(row1, col2);
    float m13 = _ZlVector4Dot(row1, col3);

    float m20 = _ZlVector4Dot(row2, col0);
    float m21 = _ZlVector4Dot(row2, col1);
    float m22 = _ZlVector4Dot(row2, col2);
    float m23 = _ZlVector4Dot(row2, col3);

    float m30 = _ZlVector4Dot(row3, col0);
    float m31 = _ZlVector4Dot(row3, col1);
    float m32 = _ZlVector4Dot(row3, col2);
    float m33 = _ZlVector4Dot(row3, col3);

    return (zlmat)
    {{
        {m00,m01,m02,m03},
        {m10,m11,m12,m13},
        {m20,m21,m22,m23},
        {m30,m31,m32,m33}
    }};
}
static inline zlmat _ZlMatrixRotateX(float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    return (zlmat)
    {{
        { 1,   0,    0,    0 },
        { 0,   cos, -sin,  0 },
        { 0,   sin,  cos,  0 },
        { 0,   0,    0,    1 }
    }};
}
static inline zlmat _ZlMatrixRotateY(float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    return (zlmat)
    {{
       {  cos,   0,  sin,   0 },
       {    0,   1,    0,   0 },
       { -sin,   0,  cos,   0 },
       {    0,   0,    0,   1 }
    }};
}
static inline zlmat _ZlMatrixRotateZ(float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    return (zlmat)
    {{
        { cos, -sin,  0,   0 },
        { sin,  cos,  0,   0 },
        { 0,    0,    1,   0 },
        { 0,    0,    0,   1 }
    }};
}
static inline zlmat _ZlMatrixTranslate(zlvec3 position)
{
    float x = position.x;
    float y = position.y;
    float z = position.z;
    return (zlmat)
    {{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {x, y, z, 1}
    }};
}
static inline zlmat _ZlMatrixRotate(zlvec3 rotation)
{
    zlmat result;
    result = _ZlMatrixRotateX(rotation.x);
    result = _ZlMatrixMultiply(result, _ZlMatrixRotateY(rotation.y));
    result = _ZlMatrixMultiply(result, _ZlMatrixRotateZ(rotation.z));
    return result;
}
static inline zlmat _ZlMatrixScale(zlvec3 scale)
{
    float x = scale.x;
    float y = scale.y;
    float z = scale.z;
    return (zlmat)
    {{
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1}
    }};
}
static inline zlmat _ZlMatrixWorld(zlvec3 position, zlvec3 rotation, zlvec3 scale)
{
    zlmat result;
    result = _ZlMatrixScale(scale);
    result = _ZlMatrixMultiply(result, _ZlMatrixRotate(rotation));
    result = _ZlMatrixMultiply(result, _ZlMatrixTranslate(position));
    return result;
}
static inline zlmat _ZlMatrixProjOrthographic(float width, float height, float near, float far)
{
    float w = 2.0f / width;
    float h = 2.0f / height;
    float a = 1.0f / (far - near);
    float b = a * -near;
    return (zlmat)
    {{
        {w, 0, 0, 0},
        {0, h, 0, 0},
        {0, 0, a, 0},
        {0, 0, b, 1}
    }};
}
static inline zlmat _ZlMatrixProjPerspective1(float width, float height, float near, float far)
{
    float x = (near*2) / (near*2/width*height);
    float y = (near*2) / (near*2);
    float z = (far+near) / (far-near);
    float o = (near*2*far) / (far-near);

    return (zlmat)
    {{
        {x,  0,  0,  0},
        {0,  y,  0,  0},
        {0,  0,  z,  1},
        {0,  0, -o,  0}
    }};
}
static inline zlmat _ZlMatrixProjPerspective2(float width, float height, float near, float far, float fov)
{
    float ratio = width / height;

    float h = 1.0f / tanf(fov / 2);
    float w = h / ratio;
    float a = far / (far - near);
    float o = a * near;

    return (zlmat)
    {{
        {w,  0,  0,  0},
        {0,  h,  0,  0},
        {0,  0,  a,  1},
        {0,  0, -o,  0}
    }};
}

static inline zlvec3 _ZlWorldToNdc(zlvec3 p, zlmat view, zlmat proj)
{
    zlvec4 _p = { p.x, p.y, p.z, 1 };

    _p = _ZlMatrixMultiply4L(_p, view);

    _p = _ZlMatrixMultiply4L(_p, proj);
    _p.x /= _p.w;
    _p.y /= _p.w;
    _p.z /= _p.w;
    _p.w = 1;

    return (zlvec3) { _p.x, _p.y, _p.z };
}
static inline zlvec3 _ZlNdcToWorld(zlvec3 p, zlmat viewi, zlmat proji)
{
    zlvec4 _p = { p.x, p.y, p.z, 1 };
    _p = _ZlMatrixMultiply4L(_p, proji);
    _p.x /= _p.w;
    _p.y /= _p.w;
    _p.z /= _p.w;
    _p.w = 1;
    _p = _ZlMatrixMultiply4L(_p, viewi);
    return (zlvec3){ _p.x, _p.y, _p.z };
}

static inline zlvec3 _ZlNdcToSp(zlvec3 v, int width, int height)
{
    v.x = (+v.x + 1) / 2 * (width  - 1);
    v.y = (-v.y + 1) / 2 * (height - 1);
    return v;
}
static inline zlvec3 _ZlSpToNdc(zlvec3 v, int maxx, int maxy)
{
    v.x = +(v.x / maxx * 2 - 1);
    v.y = -(v.y / maxy * 2 - 1);
    return v;
}

static inline bool _ZlTriangleIsClockwise(zlvec3 v0, zlvec3 v1, zlvec3 v2)
{
    zlvec3 d0 = _ZlVector3Sub(v1, v0);
    zlvec3 d1 = _ZlVector3Sub(v2, v0);
    float crossZ = d0.x*d1.y - d0.y*d1.x;
    return crossZ < 0;
}
static inline bool _ZlTriangleIsInside(zlvec3 v0, zlvec3 v1, zlvec3 v2, float x, float y)
{
    // by half-plane

    // https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
    // In general, the simplest (and quite optimal) algorithm is
    // checking on which side of the half-plane created by the edges the point is.

    float d0 = (x - v1.x) * (v0.y - v1.y) - (v0.x - v1.x) * (y - v1.y);
    float d1 = (x - v2.x) * (v1.y - v2.y) - (v1.x - v2.x) * (y - v2.y);
    float d2 = (x - v0.x) * (v2.y - v0.y) - (v2.x - v0.x) * (y - v0.y);

    bool neg = (d0 < 0) || (d1 < 0) || (d2 < 0);
    bool pos = (d0 > 0) || (d1 > 0) || (d2 > 0);

    return !(neg && pos);
}
static inline float _ZlTriangleBarycentric(zlvec3 v0, zlvec3 v1, zlvec3 v2, float x, float y)
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

static inline bool _ZlHiden(zlvec3 pos, float radius, zlmat view, float far)
{
    zlvec3 pos2 = _ZlMatrixMultiply3L(pos, view);
    if (pos2.z < -radius)                                 return true;
    if (pos2.z > +radius + far)                           return true;
    if (_ZlVector3RotateY(pos2, -_ZL_PI_DIV_4).x < -radius) return true;
    if (_ZlVector3RotateY(pos2, +_ZL_PI_DIV_4).x > +radius) return true;
    if (_ZlVector3RotateX(pos2, +_ZL_PI_DIV_4).y < -radius) return true;
    if (_ZlVector3RotateX(pos2, -_ZL_PI_DIV_4).y > +radius) return true;
    return false;
}

static inline bool _ZlClipPoint(zlvec4 p)
{
    return
    (-p.w <= p.x && p.x <= p.w) &&
    (-p.w <= p.y && p.y <= p.w) &&
    (-p.w <= p.z && p.z <= p.w);
}

static inline bool _ZlClipLineW(zlvec4* p0, zlvec4* p1)
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

            *p0 = _ZlVector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w;
            float t1 = p1->w;

            float t = t0 / (t0 - t1);

            *p1 = _ZlVector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool _ZlClipLineB(zlvec4* p0, zlvec4* p1)
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

            *p0 = _ZlVector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w + p0->z;
            float t1 = p1->w + p1->z;

            float t = t0 / (t0 - t1);

            *p1 = _ZlVector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool _ZlClipLineF(zlvec4* p0, zlvec4* p1)
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

            *p0 = _ZlVector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w - p0->z;
            float t1 = p1->w - p1->z;

            float t = t0 / (t0 - t1);

            *p1 = _ZlVector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool _ZlClipLineL(zlvec4* p0, zlvec4* p1)
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

            *p0 = _ZlVector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w + p0->x;
            float t1 = p1->w + p1->x;

            float t = t0 / (t0 - t1);

            *p1 = _ZlVector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool _ZlClipLineR(zlvec4* p0, zlvec4* p1)
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

            *p0 = _ZlVector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w - p0->x;
            float t1 = p1->w - p1->x;

            float t = t0 / (t0 - t1);

            *p1 = _ZlVector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool _ZlClipLineD(zlvec4* p0, zlvec4* p1)
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

            *p0 = _ZlVector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w + p0->y;
            float t1 = p1->w + p1->y;

            float t = t0 / (t0 - t1);

            *p1 = _ZlVector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool _ZlClipLineU(zlvec4* p0, zlvec4* p1)
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

            *p0 = _ZlVector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w - p0->y;
            float t1 = p1->w - p1->y;

            float t = t0 / (t0 - t1);

            *p1 = _ZlVector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}

static inline void _ZlClipPoligonW(zlvec4* input, zlvec4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    zlvec4* p0 = &input[initCount - 1];
    if (p0->w < 0) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        zlvec4* p1 = &input[i];
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
                zlvec4 newPoint;

                float t0 = p0->w;
                float t1 = p1->w;

                float t = t0 / (t0 - t1);

                newPoint = _ZlVector4Lerp(*p0, *p1, t);
                newPoint.w = 0;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                zlvec4 newPoint;

                float t0 = p0->w;
                float t1 = p1->w;

                float t = t0 / (t0 - t1);

                newPoint = _ZlVector4Lerp(*p0, *p1, t);
                newPoint.w = 0;

                output[index] = *p0;      index++;
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
static inline void _ZlClipPoligonB(zlvec4* input, zlvec4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    zlvec4* p0 = &input[initCount - 1];
    if (p0->z < -p0->w) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        zlvec4* p1 = &input[i];
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
                zlvec4 newPoint;

                float t0 = p0->w + p0->z;
                float t1 = p1->w + p1->z;

                float t = t0 / (t0 - t1);

                newPoint = _ZlVector4Lerp(*p0, *p1, t);
                newPoint.z = -newPoint.w;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                zlvec4 newPoint;

                float t0 = p0->w + p0->z;
                float t1 = p1->w + p1->z;

                float t = t0 / (t0 - t1);

                newPoint = _ZlVector4Lerp(*p0, *p1, t);
                newPoint.z = -newPoint.w;

                output[index] = *p0;      index++;
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
static inline void _ZlClipPoligonF(zlvec4* input, zlvec4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    zlvec4* p0 = &input[initCount - 1];
    if (p0->z > p0->w) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        zlvec4* p1 = &input[i];
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
                zlvec4 newPoint;

                float t0 = p0->w - p0->z;
                float t1 = p1->w - p1->z;

                float t = t0 / (t0 - t1);

                newPoint = _ZlVector4Lerp(*p0, *p1, t);
                newPoint.z = newPoint.w;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                zlvec4 newPoint;

                float t0 = p0->w - p0->z;
                float t1 = p1->w - p1->z;

                float t = t0 / (t0 - t1);

                newPoint = _ZlVector4Lerp(*p0, *p1, t);
                newPoint.z = newPoint.w;

                output[index] = *p0;      index++;
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
static inline void _ZlClipPoligonL(zlvec4* input, zlvec4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    zlvec4* p0 = &input[initCount - 1];
    if (p0->x < -p0->w) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        zlvec4* p1 = &input[i];
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
                zlvec4 newPoint;

                float t0 = p0->w + p0->x;
                float t1 = p1->w + p1->x;

                float t = t0 / (t0 - t1);

                newPoint = _ZlVector4Lerp(*p0, *p1, t);
                newPoint.x = -newPoint.w;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                zlvec4 newPoint;

                float t0 = p0->w + p0->x;
                float t1 = p1->w + p1->x;

                float t = t0 / (t0 - t1);

                newPoint = _ZlVector4Lerp(*p0, *p1, t);
                newPoint.x = -newPoint.w;

                output[index] = *p0;      index++;
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
static inline void _ZlClipPoligonR(zlvec4* input, zlvec4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    zlvec4* p0 = &input[initCount - 1];
    if (p0->x > p0->w) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        zlvec4* p1 = &input[i];
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
                zlvec4 newPoint;

                float t0 = p0->w - p0->x;
                float t1 = p1->w - p1->x;

                float t = t0 / (t0 - t1);

                newPoint = _ZlVector4Lerp(*p0, *p1, t);
                newPoint.x = newPoint.w;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                zlvec4 newPoint;

                float t0 = p0->w - p0->x;
                float t1 = p1->w - p1->x;

                float t = t0 / (t0 - t1);

                newPoint = _ZlVector4Lerp(*p0, *p1, t);
                newPoint.x = newPoint.w;

                output[index] = *p0;      index++;
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
static inline void _ZlClipPoligonD(zlvec4* input, zlvec4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    zlvec4* p0 = &input[initCount - 1];
    if (p0->y < -p0->w) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        zlvec4* p1 = &input[i];
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
                zlvec4 newPoint;

                float t0 = p0->w + p0->y;
                float t1 = p1->w + p1->y;

                float t = t0 / (t0 - t1);

                newPoint = _ZlVector4Lerp(*p0, *p1, t);
                newPoint.y = -newPoint.w;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                zlvec4 newPoint;

                float t0 = p0->w + p0->y;
                float t1 = p1->w + p1->y;

                float t = t0 / (t0 - t1);

                newPoint = _ZlVector4Lerp(*p0, *p1, t);
                newPoint.y = -newPoint.w;

                output[index] = *p0;      index++;
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
static inline void _ZlClipPoligonU(zlvec4* input, zlvec4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    zlvec4* p0 = &input[initCount - 1];
    if (p0->y > p0->w) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        zlvec4* p1 = &input[i];
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
                zlvec4 newPoint;

                float t0 = p0->w - p0->y;
                float t1 = p1->w - p1->y;

                float t = t0 / (t0 - t1);

                newPoint = _ZlVector4Lerp(*p0, *p1, t);
                newPoint.y = newPoint.w;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                zlvec4 newPoint;

                float t0 = p0->w - p0->y;
                float t1 = p1->w - p1->y;

                float t = t0 / (t0 - t1);

                newPoint = _ZlVector4Lerp(*p0, *p1, t);
                newPoint.y = newPoint.w;

                output[index] = *p0;      index++;
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

static inline uint32_t _ZlColorCreateRgb(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t result = 0;
    result += r; result <<= 8;
    result += g; result <<= 8;
    result += b;
    return result;
}
static inline uint32_t _ZlColorCreateBwFloat(float t)
{
    // try me, see what happens
    // uint8_t r = (COLOR_WHITE >> 8 * 2) * t;
    // uint8_t g = (COLOR_WHITE >> 8 * 1) * t;
    // uint8_t b = (COLOR_WHITE >> 8 * 0) * t;
    // return _ZlColorCreateRgb(r, g, b);

    uint8_t byte = (uint8_t)(255.0f * t);
    return _ZlColorCreateRgb(byte, byte, byte);
}

#define _ZlBitmapSizeOf(width, height) (sizeof(zlbitmap) + sizeof(float)*width*height)
static inline zlbitmap* _ZLBitmapInit(int width, int height, void* mem)
{
    assert(width > 0);
    assert(height > 0);

    zlbitmap* bitmap = (zlbitmap*)((char*)mem);
    float* buffer  = (float*)((char*)mem + sizeof(zlbitmap));

    float near = 0.1f;
    float far = 100.f;

    bitmap->width = width;
    bitmap->height = height;
    bitmap->view = _ZlMatrixIdentity();
    bitmap->proj = _ZlMatrixProjPerspective1(width, height, near, far);
    bitmap->neari = 1.0f / near;
    bitmap->far = far;
    bitmap->buffer = buffer;

    return bitmap;
}
static inline zlbitmap* _ZlBitmapCreate(int width, int height)
{
    int size = _ZlBitmapSizeOf(width, height);
    void* mem = malloc(size);
    return _ZLBitmapInit(width, height, mem);
}
static inline void _ZlBitmapDestroy(zlbitmap* bitmap)
{
    free((void*)bitmap);
}

static inline void _ZlBitmapReset(zlbitmap* bitmap)
{
    int size = bitmap->width * bitmap->height;
    for (int i = 0; i < size; i++)
        bitmap->buffer[i] = 1;
}

static inline void _ZlBitmapSetViewByEuler(zlbitmap* bitmap, zlvec3 eye, float x, float y, float z)
{
    eye = _ZlVector3Neg(eye);
    zlmat result = _ZlMatrixTranslate(eye);
    result = _ZlMatrixMultiply(result, _ZlMatrixRotateY(-y));
    result = _ZlMatrixMultiply(result, _ZlMatrixRotateX(-x));
    result = _ZlMatrixMultiply(result, _ZlMatrixRotateZ(-z));
    bitmap->view = result;
}
static inline void _ZlBitmapSetViewByPyr(zlbitmap* bitmap, zlvec3 eye, float pitch, float yaw, float roll)
{
    eye = _ZlVector3Neg(eye);
    zlmat result = _ZlMatrixTranslate(eye);
    result = _ZlMatrixMultiply(result, _ZlMatrixRotateY(yaw));
    result = _ZlMatrixMultiply(result, _ZlMatrixRotateX(-pitch));
    result = _ZlMatrixMultiply(result, _ZlMatrixRotateZ(-roll));
    bitmap->view = result;
}
static inline void _ZlBitmapSetViewByTarget(zlbitmap* bitmap, zlvec3 eye, zlvec3 target, zlvec3 up)
{
    zlvec3 zAxis = _ZlVector3Sub(target, eye);
            zAxis = _ZlVector3Normalize(zAxis);

    zlvec3 xAxis = _ZlVector3Cross(up, zAxis);
            xAxis = _ZlVector3Normalize(xAxis);

    zlvec3 yAxis = _ZlVector3Cross(zAxis, xAxis);

    zlmat result =
    {{
        { xAxis.x, xAxis.y, xAxis.z, 0 },
        { yAxis.x, yAxis.y, yAxis.z, 0 },
        { zAxis.x, zAxis.y, zAxis.z, 0 },
        {   eye.x,   eye.y,   eye.z, 1 }
    }};

    result = _ZlMatrixInvert(result);

    bitmap->view = result;
}

static inline void _ZlBitmapSetProj(zlbitmap* bitmap, float near, float far)
{
    bitmap->neari = 1.0f / near;
    bitmap->far = far;
    bitmap->proj = _ZlMatrixProjPerspective1(bitmap->width, bitmap->height, near, far);
}

static inline void _ZlBitmapSetPixel(zlbitmap* bitmap, int x, int y, uint32_t color)
{
    assert(0 <= x && x < bitmap->width);
    assert(0 <= y && y < bitmap->height);

    int i = x + y * bitmap->width;

    ((uint32_t*)bitmap->buffer)[i] = color;
}
static inline void _ZlBitmapSetDepth(zlbitmap* bitmap, int x, int y, float z)
{
    assert( 0 <= x && x < bitmap->width);
    assert( 0 <= y && y < bitmap->height);
    assert(-1 <= z && z <= +1);

    int i = x + y * bitmap->width;

    bitmap->buffer[i] =
    bitmap->buffer[i] < z ?
    bitmap->buffer[i] : z;
}

static inline void _ZlBitmapDrawVertexSp(zlbitmap* bitmap, zlvec3 v0)
{
    _ZlBitmapSetDepth(bitmap, v0.x, v0.y, v0.z);
}
static inline void _ZlBitmapDrawLineSp(zlbitmap* bitmap, zlvec3 v0, zlvec3 v1)
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
            _ZlBitmapSetDepth(bitmap, x0, y0, z0);

                          { err -= dy; x0 += sx; }
            if (err <= 0) { err += dx; y0 += sy; }

            z0 += offset;
        }

        _ZlBitmapSetDepth(bitmap, x0, y0, z1);
    }
    else
    {
        float offset = (z1 - z0) / dy;

        int err = dy - dy / 2;

        for (int i = 0; i < dy; i++)
        {
            _ZlBitmapSetDepth(bitmap, x0, y0, z0);

                          { err -= dx; y0 += sy; }
            if (err <= 0) { err += dy; x0 += sx; }

            z0 += offset;
        }

        _ZlBitmapSetDepth(bitmap, x0, y0, z1);
    }
}
static inline void _ZlBitmapDrawTriangleSp(zlbitmap* bitmap, zlvec3 v0, zlvec3 v1, zlvec3 v2)
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
        if (!_ZlTriangleIsInside(v0, v1, v2, x, y)) continue;
        float z = _ZlTriangleBarycentric(v0, v1, v2, x, y);
        _ZlBitmapSetDepth(bitmap, x, y, z);
    }
}

static inline void _ZlBitmapDrawVertexNdc(zlbitmap* bitmap, zlvec3 v0)
{
    assert(-1 <= v0.x && v0.x <= 1);
    assert(-1 <= v0.y && v0.y <= 1);
    assert(-1 <= v0.z && v0.z <= 1);

    v0 = _ZlNdcToSp(v0, bitmap->width, bitmap->height);

    _ZlBitmapDrawVertexSp(bitmap, v0);
}
static inline void _ZlBitmapDrawLineNdc(zlbitmap* bitmap, zlvec3 v0, zlvec3 v1)
{
    assert(-1 <= v0.x && v0.x <= 1);
    assert(-1 <= v0.y && v0.y <= 1);
    assert(-1 <= v0.z && v0.z <= 1);

    assert(-1 <= v1.x && v1.x <= 1);
    assert(-1 <= v1.y && v1.y <= 1);
    assert(-1 <= v1.z && v1.z <= 1);

    v0 = _ZlNdcToSp(v0, bitmap->width, bitmap->height);
    v1 = _ZlNdcToSp(v1, bitmap->width, bitmap->height);

    _ZlBitmapDrawLineSp(bitmap, v0, v1);
}
static inline void _ZlBitmapDrawTriangleNdc(zlbitmap* bitmap, zlvec3 v0, zlvec3 v1, zlvec3 v2)
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

    // TODO move to _ZlBitmapDrawTriangleSp?
    if (!_ZlTriangleIsClockwise(v0, v1, v2)) return;

    v0 = _ZlNdcToSp(v0, bitmap->width, bitmap->height);
    v1 = _ZlNdcToSp(v1, bitmap->width, bitmap->height);
    v2 = _ZlNdcToSp(v2, bitmap->width, bitmap->height);

    _ZlBitmapDrawTriangleSp(bitmap, v0, v1, v2);
}

static inline void _ZlBitmapDrawVertex(zlbitmap* bitmap, zlvec3 v0)
{
    zlvec4 _v0 = { v0.x, v0.y, v0.z, 1 };

    _v0 = _ZlMatrixMultiply4L(_v0, bitmap->view);
    _v0 = _ZlMatrixMultiply4L(_v0, bitmap->proj);

    if (!_ZlClipPoint(_v0)) return;

    _v0.x /= _v0.w;
    _v0.y /= _v0.w;
    _v0.z /= _v0.w;

    v0 = (zlvec3){ _v0.x, _v0.y, _v0.z };

    _ZlBitmapDrawVertexNdc(bitmap, v0);
}
static inline void _ZlBitmapDrawLine(zlbitmap* bitmap, zlvec3 v0, zlvec3 v1)
{
    zlvec4 _v0 = { v0.x, v0.y, v0.z, 1 };
    zlvec4 _v1 = { v1.x, v1.y, v1.z, 1 };

    _v0 = _ZlMatrixMultiply4L(_v0, bitmap->view);
    _v1 = _ZlMatrixMultiply4L(_v1, bitmap->view);

    _v0 = _ZlMatrixMultiply4L(_v0, bitmap->proj);
    _v1 = _ZlMatrixMultiply4L(_v1, bitmap->proj);

    if (_ZlClipLineW(&_v0, &_v1)) return;
    if (_ZlClipLineB(&_v0, &_v1)) return;
    if (_ZlClipLineF(&_v0, &_v1)) return;
    if (_ZlClipLineL(&_v0, &_v1)) return;
    if (_ZlClipLineR(&_v0, &_v1)) return;
    if (_ZlClipLineD(&_v0, &_v1)) return;
    if (_ZlClipLineU(&_v0, &_v1)) return;

    _v0.x /= _v0.w;
    _v0.y /= _v0.w;
    _v0.z /= _v0.w;
    _v1.x /= _v1.w;
    _v1.y /= _v1.w;
    _v1.z /= _v1.w;

    // removing clip errors
    _v0.x = _ZlMathClamp(_v0.x, -1, +1);
    _v0.y = _ZlMathClamp(_v0.y, -1, +1);
    _v0.z = _ZlMathClamp(_v0.z, -1, +1);
    _v1.x = _ZlMathClamp(_v1.x, -1, +1);
    _v1.y = _ZlMathClamp(_v1.y, -1, +1);
    _v1.z = _ZlMathClamp(_v1.z, -1, +1);

    v0.x = _v0.x;
    v0.y = _v0.y;
    v0.z = _v0.z;
    v1.x = _v1.x;
    v1.y = _v1.y;
    v1.z = _v1.z;

    _ZlBitmapDrawLineNdc(bitmap, v0, v1);
}
static inline void _ZlBitmapDrawTriangle(zlbitmap* bitmap, zlvec3 v0, zlvec3 v1, zlvec3 v2)
{
    int vertexCount = 3;

    zlvec4 vs0[9];
    zlvec4 vs1[9];

    vs0[0] = (zlvec4){ v0.x, v0.y, v0.z, 1 };
    vs0[1] = (zlvec4){ v1.x, v1.y, v1.z, 1 };
    vs0[2] = (zlvec4){ v2.x, v2.y, v2.z, 1 };

    vs0[0] = _ZlMatrixMultiply4L(vs0[0], bitmap->view);
    vs0[1] = _ZlMatrixMultiply4L(vs0[1], bitmap->view);
    vs0[2] = _ZlMatrixMultiply4L(vs0[2], bitmap->view);

    vs0[0] = _ZlMatrixMultiply4L(vs0[0], bitmap->proj);
    vs0[1] = _ZlMatrixMultiply4L(vs0[1], bitmap->proj);
    vs0[2] = _ZlMatrixMultiply4L(vs0[2], bitmap->proj);

    _ZlClipPoligonW(vs0, vs1, &vertexCount); if (vertexCount < 3) return;
    _ZlClipPoligonB(vs1, vs0, &vertexCount); if (vertexCount < 3) return;
    _ZlClipPoligonF(vs0, vs1, &vertexCount); if (vertexCount < 3) return;
    _ZlClipPoligonL(vs1, vs0, &vertexCount); if (vertexCount < 3) return;
    _ZlClipPoligonR(vs0, vs1, &vertexCount); if (vertexCount < 3) return;
    _ZlClipPoligonD(vs1, vs0, &vertexCount); if (vertexCount < 3) return;
    _ZlClipPoligonU(vs0, vs1, &vertexCount); if (vertexCount < 3) return;

    for (int i = 0; i < vertexCount; i++)
    {
        vs1[i].x /= vs1[i].w;
        vs1[i].y /= vs1[i].w;
        vs1[i].z /= vs1[i].w;

        // linear interpolation, in clipping, accumulates error
        // values, in NDC, can become slightly outside
        // duno what to do about that, I just clamp them
        vs1[i].x = _ZlMathClamp(vs1[i].x, -1, +1);
        vs1[i].y = _ZlMathClamp(vs1[i].y, -1, +1);
        vs1[i].z = _ZlMathClamp(vs1[i].z, -1, +1);
    }

    for (int i = 1; i < vertexCount - 1; i++)
    {
        zlvec4 _v0 = vs1[0];
        zlvec4 _v1 = vs1[i];
        zlvec4 _v2 = vs1[i+1];

        v0 = (zlvec3){ _v0.x, _v0.y, _v0.z };
        v1 = (zlvec3){ _v1.x, _v1.y, _v1.z };
        v2 = (zlvec3){ _v2.x, _v2.y, _v2.z };

        _ZlBitmapDrawTriangleNdc(bitmap, v0, v1, v2);
    }
}

static inline void _ZlBitmapApplyDepth(zlbitmap* bitmap)
{
    float* zbuffer = (float*)bitmap->buffer;
    uint32_t* pixels = (uint32_t*)bitmap->buffer;

    int size = bitmap->width * bitmap->height;

    for (int i = 0; i < size; i++)
    {
        float t = zbuffer[i];
        t = (t + 1) / 2;
        pixels[i] = _ZlColorCreateBwFloat(t);
    }
}
static inline void _ZlBitmapApplyDepthInvert(zlbitmap* bitmap)
{
    float* zbuffer = (float*)bitmap->buffer;
    uint32_t* pixels = (uint32_t*)bitmap->buffer;

    int size = bitmap->width * bitmap->height;

    for (int i = 0; i < size; i++)
    {
        float t = zbuffer[i];
        t = (t + 1) / 2;
        t = 1 - t;
        pixels[i] = _ZlColorCreateBwFloat(t);
    }
}

static inline void _ZlBitmapApplyDepthAdjusted(zlbitmap* bitmap)
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
        t = _ZlMathClamp(t, 0, 1);
        pixels[i] = _ZlColorCreateBwFloat(t);
    }
}
static inline void _ZlBitmapApplyDepthAdjustedInvert(zlbitmap* bitmap)
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
        t = _ZlMathClamp(t, 0, 1);
        pixels[i] = _ZlColorCreateBwFloat(t);
    }
}

static inline float _ZlCalcLight(zlvec3 surPos, float lum, zlvec3 lightPos, float* buffer, zlmat view)
{
    zlvec3 ndc = _ZlWorldToNdc(surPos, view, _ZL_SHADOW_MAP_PROJ);

    if (ndc.x < -1 || +1 < ndc.x) return 0.0f;
    if (ndc.y < -1 || +1 < ndc.y) return 0.0f;
    // if (ndc.z < -1 || +1 < ndc.z) return 0.0f;

    if (ndc.z < -1) return lum;
    if (ndc.z > +1) return 0.0f;

    int x = (+ndc.x + 1.0f) / 2.0f * (ZL_SHADOW_MAP_SIZE - 1);
    int y = (-ndc.y + 1.0f) / 2.0f * (ZL_SHADOW_MAP_SIZE - 1);

    int i = x + y * ZL_SHADOW_MAP_SIZE;

    float z1 = buffer[i] + ZL_SHADOW_MAP_BIAS;
    float z2 = ndc.z;

    if (z1 < z2) return 0.0f;

    float t;

    float dist1 = _ZlVector3Distance(surPos, lightPos);
    float dist2 = ZL_LIGHT_MAX_DIST;
    t = dist1 / dist2;
    t = t < 1 ? (1 - t) * lum : 0;

    return t;
}
static inline float _ZlCalcLightSpot(zlvec3 surPos, _zlSpotLight* light)
{
    int sectorId = 0;
    {
        zlvec3 v = _ZlVector3Sub(surPos, light->pos);

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
            case 0: { t = _ZlCalcLight(surPos, light->lum, light->pos, light->bufl, light->matl); break; }
            case 1: { t = _ZlCalcLight(surPos, light->lum, light->pos, light->bufr, light->matr); break; }
            case 2: { t = _ZlCalcLight(surPos, light->lum, light->pos, light->bufd, light->matd); break; }
            case 3: { t = _ZlCalcLight(surPos, light->lum, light->pos, light->bufu, light->matu); break; }
            case 4: { t = _ZlCalcLight(surPos, light->lum, light->pos, light->bufb, light->matb); break; }
            case 5: { t = _ZlCalcLight(surPos, light->lum, light->pos, light->buff, light->matf); break; }
        }
    }

    return t;
}
static inline float _ZlCalcLightLightData(zlvec3 surPos, _zlLightData* lightData)
{
    float result = 0;

    for (int i = 0; i < lightData->lightsc; i++)
    {
        _zlSpotLight* light = &lightData->lights[i];

        float t = _ZlCalcLightSpot(surPos, light);

        result =
        result > t ?
        result : t;
    }

    return result;
}
static inline void _ZlUpdateShadows(void (*draw)(zlbitmap* bitmap), _zlSpotLight* light)
{
    zlvec3 eye = _ZlVector3Neg(light->pos);
    zlmat mat = _ZlMatrixTranslate(eye);

    light->matf = _ZlMatrixMultiply(mat, _ZlMatrixRotateY(_ZL_PI_DIV_2*0));
    light->matr = _ZlMatrixMultiply(mat, _ZlMatrixRotateY(_ZL_PI_DIV_2*1));
    light->matb = _ZlMatrixMultiply(mat, _ZlMatrixRotateY(_ZL_PI_DIV_2*2));
    light->matl = _ZlMatrixMultiply(mat, _ZlMatrixRotateY(_ZL_PI_DIV_2*3));
    light->matu = _ZlMatrixMultiply(mat, _ZlMatrixRotateX(-_ZL_PI_DIV_2));
    light->matd = _ZlMatrixMultiply(mat, _ZlMatrixRotateX(+_ZL_PI_DIV_2));

    zlbitmap bf; bf.buffer = light->buff; bf.view = light->matf;
    zlbitmap br; br.buffer = light->bufr; br.view = light->matr;
    zlbitmap bb; bb.buffer = light->bufb; bb.view = light->matb;
    zlbitmap bl; bl.buffer = light->bufl; bl.view = light->matl;
    zlbitmap bu; bu.buffer = light->bufu; bu.view = light->matu;
    zlbitmap bd; bd.buffer = light->bufd; bd.view = light->matd;

    bf.proj = _ZL_SHADOW_MAP_PROJ; bf.width = ZL_SHADOW_MAP_SIZE; bf.height = ZL_SHADOW_MAP_SIZE; bf.far = ZL_LIGHT_MAX_DIST;
    br.proj = _ZL_SHADOW_MAP_PROJ; br.width = ZL_SHADOW_MAP_SIZE; br.height = ZL_SHADOW_MAP_SIZE; br.far = ZL_LIGHT_MAX_DIST;
    bb.proj = _ZL_SHADOW_MAP_PROJ; bb.width = ZL_SHADOW_MAP_SIZE; bb.height = ZL_SHADOW_MAP_SIZE; bb.far = ZL_LIGHT_MAX_DIST;
    bl.proj = _ZL_SHADOW_MAP_PROJ; bl.width = ZL_SHADOW_MAP_SIZE; bl.height = ZL_SHADOW_MAP_SIZE; bl.far = ZL_LIGHT_MAX_DIST;
    bu.proj = _ZL_SHADOW_MAP_PROJ; bu.width = ZL_SHADOW_MAP_SIZE; bu.height = ZL_SHADOW_MAP_SIZE; bu.far = ZL_LIGHT_MAX_DIST;
    bd.proj = _ZL_SHADOW_MAP_PROJ; bd.width = ZL_SHADOW_MAP_SIZE; bd.height = ZL_SHADOW_MAP_SIZE; bd.far = ZL_LIGHT_MAX_DIST;

    _ZlBitmapReset(&bf); draw(&bf);
    _ZlBitmapReset(&br); draw(&br);
    _ZlBitmapReset(&bb); draw(&bb);
    _ZlBitmapReset(&bl); draw(&bl);
    _ZlBitmapReset(&bu); draw(&bu);
    _ZlBitmapReset(&bd); draw(&bd);
}
static inline void _ZlApplyLight(zlbitmap* bitmap, _zlLightData* lightData)
{
    uint32_t* pixels = (uint32_t*)bitmap->buffer;

    zlmat viewi = _ZlMatrixInvert(bitmap->view);
    zlmat proji = _ZlMatrixInvert(bitmap->proj);

    for (int y = 0; y < bitmap->height; y++)
    for (int x = 0; x < bitmap->width;  x++)
    {
        int i = x + y * bitmap->width;
        float z = bitmap->buffer[i];
        if (z == 1) { pixels[i] = _ZlColorCreateBwFloat(0); continue; }
        zlvec3 sp = (zlvec3){ (float)x, (float)y, z };
        zlvec3 ndc = _ZlSpToNdc(sp, bitmap->width-1, bitmap->height-1);
        zlvec3 surPos = _ZlNdcToWorld(ndc, viewi, proji);
        float t = _ZlCalcLightLightData(surPos, lightData);
        pixels[i] = _ZlColorCreateBwFloat(t);
    }
}

_zlLightData _LightData1_data = {};
static inline void _ZlLightData1RemoveLight()
{
    _LightData1_data.lightsc = 0;
}
static inline void _ZlLightData1AddLight(zlvec3 pos, float lum)
{
    int size = _LightData1_data.lightsc + 1;

    if (_LightData1_data.lightsmax < size)
    {
        _LightData1_data.lightsmax = size * 2;
        _LightData1_data.lights = (_zlSpotLight*)realloc(_LightData1_data.lights, _LightData1_data.lightsmax*sizeof(_zlSpotLight));
    }

    _zlSpotLight* light = &_LightData1_data.lights[_LightData1_data.lightsc];

    light->pos = pos;
    light->lum = lum;

    _LightData1_data.lightsc++;
}
static inline void _ZlLightData1UpdateShadows(void (*draw)(zlbitmap* bitmap))
{
    for (int i = 0; i < _LightData1_data.lightsc; i++)
        _ZlUpdateShadows(draw, &_LightData1_data.lights[i]);
}
static inline void _ZlLightData1ApplyLight(zlbitmap* bitmap)
{
    _ZlApplyLight(bitmap, &_LightData1_data);
}

const zlvec3 _ZlModelCubeVerteces[8] =
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
const int _ZlModelCubeIndecesLine[12][2] =
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
const int _ZlModelCubeIndecesQuad[6][4] =
{
    {2, 6, 4, 0},
    {6, 7, 5, 4},
    {7, 3, 1, 5},
    {3, 2, 0, 1},
    {1, 0, 4, 5},
    {3, 7, 6, 2}
};
const zlvec3 _ZlModelSphereVerteces[32] =
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
const int _ZlModelSphereIndecesTriangles[60][3] =
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
static inline void _ZLBitmapExtDrawQuad(zlbitmap* bitmap, zlvec3 v0, zlvec3 v1, zlvec3 v2, zlvec3 v3)
{
    _ZlBitmapDrawTriangle(bitmap, v0, v1, v2);
    _ZlBitmapDrawTriangle(bitmap, v2, v3, v0);
}
static inline void _ZLBitmapExtDrawBound(zlbitmap* bitmap, zlvec3* vs, int vsc)
{
    float maxx;
    float maxy;
    float maxz;
    float minx;
    float miny;
    float minz;

    for (int i = 0; i < vsc; i++)
    {
        zlvec3 v = vs[i];
        maxx = fmaxf(maxx, v.x);
        maxy = fmaxf(maxy, v.y);
        maxz = fmaxf(maxz, v.z);
        minx = fminf(minx, v.x);
        miny = fminf(miny, v.y);
        minz = fminf(minz, v.z);
    }

    zlvec3 p0 = { minx, miny, minz };
    zlvec3 p1 = { minx, miny, maxz };
    zlvec3 p2 = { minx, maxy, minz };
    zlvec3 p3 = { minx, maxy, maxz };
    zlvec3 p4 = { maxx, miny, minz };
    zlvec3 p5 = { maxx, miny, maxz };
    zlvec3 p6 = { maxx, maxy, minz };
    zlvec3 p7 = { maxx, maxy, maxz };

    _ZlBitmapDrawLine(bitmap, p0, p1);
    _ZlBitmapDrawLine(bitmap, p1, p5);
    _ZlBitmapDrawLine(bitmap, p5, p4);
    _ZlBitmapDrawLine(bitmap, p4, p0);
    _ZlBitmapDrawLine(bitmap, p2, p3);
    _ZlBitmapDrawLine(bitmap, p3, p7);
    _ZlBitmapDrawLine(bitmap, p7, p6);
    _ZlBitmapDrawLine(bitmap, p6, p2);
    _ZlBitmapDrawLine(bitmap, p0, p2);
    _ZlBitmapDrawLine(bitmap, p1, p3);
    _ZlBitmapDrawLine(bitmap, p5, p7);
    _ZlBitmapDrawLine(bitmap, p4, p6);
}
static inline void _ZLBitmapExtDrawCubeMat(zlbitmap* bitmap, zlmat mat)
{
    #define DRAW(INDEX)                               \
    {                                                 \
        int i0 = _ZlModelCubeIndecesQuad[INDEX][0];   \
        int i1 = _ZlModelCubeIndecesQuad[INDEX][1];   \
        int i2 = _ZlModelCubeIndecesQuad[INDEX][2];   \
        int i3 = _ZlModelCubeIndecesQuad[INDEX][3];   \
        zlvec3 p0 = _ZlModelCubeVerteces[i0];         \
        zlvec3 p1 = _ZlModelCubeVerteces[i1];         \
        zlvec3 p2 = _ZlModelCubeVerteces[i2];         \
        zlvec3 p3 = _ZlModelCubeVerteces[i3];         \
        p0 = _ZlMatrixMultiply3L(p0, mat);            \
        p1 = _ZlMatrixMultiply3L(p1, mat);            \
        p2 = _ZlMatrixMultiply3L(p2, mat);            \
        p3 = _ZlMatrixMultiply3L(p3, mat);            \
        _ZLBitmapExtDrawQuad(bitmap, p0, p1, p2, p3); \
    }                                                 \

    DRAW(0)
    DRAW(1)
    DRAW(2)
    DRAW(3)
    DRAW(4)
    DRAW(5)

    #undef DRAW
}
static inline void _ZLBitmapExtDrawCube(zlbitmap* bitmap, zlvec3 pos, zlvec3 rot, zlvec3 scale)
{
    zlmat mat = _ZlMatrixWorld(pos, rot, scale);
    _ZLBitmapExtDrawCubeMat(bitmap, mat);
}
static inline void _ZLBitmapExtDrawSphere(zlbitmap* bitmap, zlvec3 pos)
{
    if (_ZlHiden(pos, 1.0f, bitmap->view, bitmap->far)) return;

    for (size_t i = 0; i < 60; i++)
    {
        int i0 = _ZlModelSphereIndecesTriangles[i][0];
        int i1 = _ZlModelSphereIndecesTriangles[i][1];
        int i2 = _ZlModelSphereIndecesTriangles[i][2];
        zlvec3 v0 = _ZlModelSphereVerteces[i0];
        zlvec3 v1 = _ZlModelSphereVerteces[i1];
        zlvec3 v2 = _ZlModelSphereVerteces[i2];
        v0 = _ZlVector3Add(v0, pos);
        v1 = _ZlVector3Add(v1, pos);
        v2 = _ZlVector3Add(v2, pos);
        _ZlBitmapDrawTriangle(bitmap, v0, v1, v2);
    }
}
static inline void _ZLBitmapExtDrawBorder(zlbitmap* bitmap, float color)
{
    int x = bitmap->width - 1;
    int y = bitmap->height - 1;
    for (int i = 0; i < bitmap->width;  i++) _ZlBitmapSetPixel(bitmap, i, 0, color);
    for (int i = 0; i < bitmap->width;  i++) _ZlBitmapSetPixel(bitmap, i, y, color);
    for (int i = 0; i < bitmap->height; i++) _ZlBitmapSetPixel(bitmap, 0, i, color);
    for (int i = 0; i < bitmap->height; i++) _ZlBitmapSetPixel(bitmap, x, i, color);
}
static inline void _ZLBitmapExtDrawCross(zlbitmap* bitmap, float color)
{
    for (int i = 0; i < bitmap->width;  i++) _ZlBitmapSetPixel(bitmap, i, (bitmap->height-1) / 2, color);
    for (int i = 0; i < bitmap->height; i++) _ZlBitmapSetPixel(bitmap, (bitmap->width-1) / 2, i, color);
}
static inline void _ZLBitmapExtDrawChar(zlbitmap* bitmap, int x, int y, char c)
{
    #define P(x2, y2) _ZlBitmapSetPixel(bitmap, x+x2, y+y2, 0x00FFFFFF);

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
static inline void _ZLBitmapExtDrawGrid(zlbitmap* bitmap)
{
    int count = 10;

    for (int i = 0; i < count; i++)
    {
        float offset = (float)(i-count/2);
        zlvec3 v0 = { offset, 0, -(float)count };
        zlvec3 v1 = { offset, 0, +(float)count };
        _ZlBitmapDrawLine(bitmap, v0, v1);
    }

    for (int i = 0; i < count; i++)
    {
        float offset = (float)(i-count/2);
        zlvec3 v0 = { -(float)count, 0, offset };
        zlvec3 v1 = { +(float)count, 0, offset };
        _ZlBitmapDrawLine(bitmap, v0, v1);
    }
}
static inline void _ZLBitmapExtDrawPlane(zlbitmap* bitmap)
{
    float size = 10;

    zlvec3 p0 = { +size, 0, +size };
    zlvec3 p1 = { +size, 0, -size };
    zlvec3 p2 = { -size, 0, -size };
    zlvec3 p3 = { -size, 0, +size };

    _ZLBitmapExtDrawQuad(bitmap, p0, p1, p2, p3);
}
static inline void _ZLBitmapExtDrawCubeWire(zlbitmap* bitmap, zlvec3 pos, zlvec3 rot, zlvec3 scale)
{
    zlmat model = _ZlMatrixWorld(pos, rot, scale);

    for (int i = 0; i < 12; i++)
    {
        int i0 = _ZlModelCubeIndecesLine[i][0];
        int i1 = _ZlModelCubeIndecesLine[i][1];
        zlvec3 v0 = _ZlModelCubeVerteces[i0];
        zlvec3 v1 = _ZlModelCubeVerteces[i1];
        v0 = _ZlMatrixMultiply3L(v0, model);
        v1 = _ZlMatrixMultiply3L(v1, model);
        _ZlBitmapDrawLine(bitmap, v0, v1);
    }
}

// === Core ===
static inline zlbitmap* ZlBitmapCreate(int width, int height)                                             { return _ZlBitmapCreate(width, height); }
static inline void ZlBitmapDestroy(zlbitmap* bitmap)                                                      { _ZlBitmapDestroy(bitmap); }
static inline void ZlBitmapReset(zlbitmap* bitmap)                                                        { _ZlBitmapReset(bitmap); }
static inline void ZlBitmapSetViewByEuler(zlbitmap* bitmap, zlvec3 eye, float x, float y, float z)        { _ZlBitmapSetViewByEuler(bitmap, eye, x, y, z); }
static inline void ZlBitmapSetViewByPyr(zlbitmap* bitmap, zlvec3 eye, float pitch, float yaw, float roll) { _ZlBitmapSetViewByPyr(bitmap, eye, pitch, yaw, roll); }
static inline void ZlBitmapSetViewByTarget(zlbitmap* bitmap, zlvec3 eye, zlvec3 target, zlvec3 up)        { _ZlBitmapSetViewByTarget(bitmap, eye, target, up); }
static inline void ZlBitmapSetProj(zlbitmap* bitmap, float near, float far)                               { _ZlBitmapSetProj(bitmap, near, far); }
static inline void ZlBitmapSetPixel(zlbitmap* bitmap, int x, int y, uint32_t color)                       { _ZlBitmapSetPixel(bitmap, x, y, color); }
static inline void ZlBitmapDrawVertex(zlbitmap* bitmap, zlvec3 v0)                                        { _ZlBitmapDrawVertex(bitmap, v0); }
static inline void ZlBitmapDrawLine(zlbitmap* bitmap, zlvec3 v0, zlvec3 v1)                               { _ZlBitmapDrawLine(bitmap, v0, v1); }
static inline void ZlBitmapDrawTriangle(zlbitmap* bitmap, zlvec3 v0, zlvec3 v1, zlvec3 v2)                { _ZlBitmapDrawTriangle(bitmap, v0, v1, v2); }
static inline void ZlBitmapApplyDepth(zlbitmap* bitmap)                                                   { _ZlBitmapApplyDepth(bitmap); }
static inline void ZlBitmapApplyDepthInvert(zlbitmap* bitmap)                                             { _ZlBitmapApplyDepthInvert(bitmap); }
static inline void ZlBitmapApplyDepthAdjusted(zlbitmap* bitmap)                                           { _ZlBitmapApplyDepthAdjusted(bitmap); }
static inline void ZlBitmapApplyDepthAdjustedInvert(zlbitmap* bitmap)                                     { _ZlBitmapApplyDepthAdjustedInvert(bitmap); }

// === Light and Shadow ===
static inline void ZlLightRemove()                                                                        { _ZlLightData1RemoveLight(); }
static inline void ZlLightAdd(zlvec3 pos, float lum)                                                      { _ZlLightData1AddLight(pos, lum); }
static inline void ZlLightUpdate(void (*draw)(zlbitmap* bitmap))                                          { _ZlLightData1UpdateShadows(draw); }
static inline void ZlLightApply(zlbitmap* bitmap)                                                         { _ZlLightData1ApplyLight(bitmap); }

// === Extra Draw ===
static inline void ZlBitmapExtDrawGrid(zlbitmap* bitmap)                                                  { _ZLBitmapExtDrawGrid(bitmap); }
static inline void ZlBitmapExtDrawPlane(zlbitmap* bitmap)                                                 { _ZLBitmapExtDrawPlane(bitmap); }
static inline void ZlBitmapExtDrawCube(zlbitmap* bitmap, zlvec3 pos, zlvec3 rot, zlvec3 scale)            { _ZLBitmapExtDrawCube(bitmap, pos, rot, scale); }
static inline void ZlBitmapExtDrawCubeWire(zlbitmap* bitmap, zlvec3 pos, zlvec3 rot, zlvec3 scale)        { _ZLBitmapExtDrawCubeWire(bitmap, pos, rot, scale); }
static inline void ZlBitmapExtDrawChar(zlbitmap* bitmap, int x, int y, char c)                            { _ZLBitmapExtDrawChar(bitmap, x, y, c); }
