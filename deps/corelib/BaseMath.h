#pragma once

#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <assert.h>

#define MATH_PI        (float)3.14159265358979323846
#define MATH_PI_MUL_2  (float)6.28318530717958647692
#define MATH_PI_DIV_2  (float)1.57079632679489661923
#define MATH_PI_DIV_4  (float)0.78539816339744830961

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
typedef struct Camera
{
    Vector3 position;
    float yaw;
    float pitch;
}
Camera;
typedef struct Bound
{
    Vector3 p0;
    Vector3 p1;
}
Bound;
typedef struct Box
{
    Vector3 position;
    Vector3 rotation;
    Vector3 halfExtent;
}
Box;
typedef struct Sphere
{
    Vector3 position;
    float radius;
}
Sphere;
typedef struct Pose
{
    Vector3 position;
    Vector3 rotation;
}
Pose;

static inline void SwapInt(int* l, int* r)
{
    int temp = *l;
    *l = *r;
    *r = temp;
}
static inline void SwapVector3(Vector3* l, Vector3* r)
{
    Vector3 temp = *l;
    *l = *r;
    *r = temp;
}

static inline int MathSignInt(int x)
{
    return (0 < x) - (x < 0);
}
static inline int MathAbsInt(int x)
{
    return abs(x);
}
static inline int MathMinInt(int x, int y)
{
    return fmin(x, y);
}
static inline int MathMaxInt(int x, int y)
{
    return fmax(x, y);
}
static inline int MathClampInt(int x, int min, int max)
{
    if (x < min) { return min; };
    if (x > max) { return max; };
                   return x;
}

static inline float MathSign(float x)
{
    return (0 < x) - (x < 0);
}
static inline float MathAbs(float x)
{
    return fabsf(x);
}
static inline float MathMin(float x, float y)
{
    return fminf(x, y);
}
static inline float MathMax(float x, float y)
{
    return fmaxf(x, y);
}
static inline float MathPow(float x, float pow)
{
    return powf(x, pow);
}
static inline float MathSqrt(float x)
{
    return sqrtf(x);
}
static inline float MathSin(float x)
{
    return sinf(x);
}
static inline float MathCos(float x)
{
    return cosf(x);
}
static inline float MathMod(float x, float div)
{
    return fmodf(x, div);
}
static inline float MathToDegree(float rad)
{
    float _180_div_pi = (float)57.2957795130823208768;
    return _180_div_pi * rad;
}
static inline float MathToRadians(float deg)
{
    float _pi_div_180 = (float)0.01745329251994329576;
    return _pi_div_180 * deg;
}
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
static inline float MathInverseLerp(float a, float b, float x)
{
    return (x - a) / (b - a);
}
static inline float MathPingPong(float x, float div)
{
    x = MathAbs(x);
    int whole = (int)(x / div);
    float rem = fmodf(x, div);
    return whole % 2 == 0 ? rem : div - rem;
}
static inline float MathEaseIn(float x, int pow)
{
    return MathPow(x, pow);
}
static inline float MathEaseOut(float x, int pow)
{
    float x2 = 1 - x;
    return 1 - MathPow(x2, pow);
}
static inline float MathMoveTowards(float source, float target, float delta)
{
    if (source < target)
    {
        source += delta;
        return
        source < target ?
        source : target;
    }
    else
    {
        source -= delta;
        return
        source > target ?
        source : target;
    }
}

static inline bool MathEqual(float a, float b, float bias)
{
    return MathAbs(a - b) < bias;
}

static inline bool Vector2Equal(Vector2 l, Vector2 r)
{
    return
    l.x == r.x &&
    l.y == r.y;
}
static inline bool Vector3Equal(Vector3 l, Vector3 r)
{
    return
    l.x == r.x &&
    l.y == r.y &&
    l.z == r.z;
}
static inline bool Vector4Equal(Vector4 l, Vector4 r)
{
    return
    l.x == r.x &&
    l.y == r.y &&
    l.z == r.z &&
    l.w == r.w;
}

static inline Vector2 Vector2Neg(Vector2 r)
{
    r.x = -r.x;
    r.y = -r.y;
    return r;
}
static inline Vector3 Vector3Neg(Vector3 r)
{
    r.x = -r.x;
    r.y = -r.y;
    r.z = -r.z;
    return r;
}
static inline Vector4 Vector4Neg(Vector4 r)
{
    r.x = -r.x;
    r.y = -r.y;
    r.z = -r.z;
    r.w = -r.w;
    return r;
}

static inline Vector2 Vector2Add(Vector2 l, Vector2 r)
{
    l.x += r.x;
    l.y += r.y;
    return l;
}
static inline Vector3 Vector3Add(Vector3 l, Vector3 r)
{
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    return l;
}
static inline Vector4 Vector4Add(Vector4 l, Vector4 r)
{
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    l.w += r.w;
    return l;
}

static inline Vector2 Vector2Sub(Vector2 l, Vector2 r)
{
    l.x -= r.x;
    l.y -= r.y;
    return l;
}
static inline Vector3 Vector3Sub(Vector3 l, Vector3 r)
{
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    return l;
}
static inline Vector4 Vector4Sub(Vector4 l, Vector4 r)
{
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    l.w -= r.w;
    return l;
}

static inline Vector2 Vector2Mul(Vector2 l, float r)
{
    l.x *= r;
    l.y *= r;
    return l;
}
static inline Vector3 Vector3Mul(Vector3 l, float r)
{
    l.x *= r;
    l.y *= r;
    l.z *= r;
    return l;
}
static inline Vector4 Vector4Mul(Vector4 l, float r)
{
    l.x *= r;
    l.y *= r;
    l.z *= r;
    l.w *= r;
    return l;
}

static inline Vector2 Vector2Div(Vector2 l, float r)
{
    l.x /= r;
    l.y /= r;
    return l;
}
static inline Vector3 Vector3Div(Vector3 l, float r)
{
    l.x /= r;
    l.y /= r;
    l.z /= r;
    return l;
}
static inline Vector4 Vector4Div(Vector4 l, float r)
{
    l.x /= r;
    l.y /= r;
    l.z /= r;
    l.w /= r;
    return l;
}

static inline float Vector2Dot(Vector2 l, Vector2 r)
{
    float x = l.x * r.x;
    float y = l.y * r.y;
    return x + y;
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

static inline float Vector2Cross(Vector2 a, Vector2 b)
{
    return a.x * b.y - a.y * b.x;
}
static inline Vector3 Vector3Cross(Vector3 a, Vector3 b)
{
    float x = a.y*b.z - a.z*b.y;
    float y = a.z*b.x - a.x*b.z;
    float z = a.x*b.y - a.y*b.x;
    return (Vector3){ x, y, z };
}

static inline Vector2 Vector2Abs(Vector2 v)
{
    v.x = MathAbs(v.x);
    v.y = MathAbs(v.y);
    return v;
}
static inline Vector3 Vector3Abs(Vector3 v)
{
    v.x = MathAbs(v.x);
    v.y = MathAbs(v.y);
    v.z = MathAbs(v.z);
    return v;
}
static inline Vector4 Vector4Abs(Vector4 v)
{
    v.x = MathAbs(v.x);
    v.y = MathAbs(v.y);
    v.z = MathAbs(v.z);
    v.w = MathAbs(v.w);
    return v;
}

static inline float Vector2Length(Vector2 v)
{
    float x = v.x * v.x;
    float y = v.y * v.y;
    return MathSqrt(x + y);
}
static inline float Vector3Length(Vector3 v)
{
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    return MathSqrt(x + y + z);
}
static inline float Vector4Length(Vector4 v)
{
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    float w = v.w * v.w;
    return MathSqrt(x + y + z + w);
}

static inline float Vector2LengthSquared(Vector2 v)
{
    float x = v.x * v.x;
    float y = v.y * v.y;
    return x + y;
}
static inline float Vector3LengthSquared(Vector3 v)
{
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    return x + y + z;
}
static inline float Vector4LengthSquared(Vector4 v)
{
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    float w = v.w * v.w;
    return x + y + z + w;
}

static inline float Vector2Distance(Vector2 a, Vector2 b)
{
    Vector2 v = Vector2Sub(a, b);
    float x = v.x * v.x;
    float y = v.y * v.y;
    return MathSqrt(x + y);
}
static inline float Vector3Distance(Vector3 a, Vector3 b)
{
    Vector3 v = Vector3Sub(a, b);
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    return MathSqrt(x + y + z);
}
static inline float Vector4Distance(Vector4 a, Vector4 b)
{
    Vector4 v = Vector4Sub(a, b);
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    float w = v.w * v.w;
    return MathSqrt(x + y + z + w);
}

static inline float Vector2DistanceSquared(Vector2 a, Vector2 b)
{
    Vector2 v = Vector2Sub(a, b);
    float x = v.x * v.x;
    float y = v.y * v.y;
    return x + y;
}
static inline float Vector3DistanceSquared(Vector3 a, Vector3 b)
{
    Vector3 v = Vector3Sub(a, b);
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    return x + y + z;
}
static inline float Vector4DistanceSquared(Vector4 a, Vector4 b)
{
    Vector4 v = Vector4Sub(a, b);
    float x = v.x * v.x;
    float y = v.y * v.y;
    float z = v.z * v.z;
    float w = v.w * v.w;
    return x + y + z + w;
}

static inline Vector3 Vector2Lerp(Vector3 a, Vector3 b, float t)
{
    a.x = MathLerp(a.x, b.x, t);
    a.y = MathLerp(a.y, b.y, t);
    return a;
}
static inline Vector3 Vector3Lerp(Vector3 a, Vector3 b, float t)
{
    a.x = MathLerp(a.x, b.x, t);
    a.y = MathLerp(a.y, b.y, t);
    a.z = MathLerp(a.z, b.z, t);
    return a;
}
static inline Vector4 Vector4Lerp(Vector4 a, Vector4 b, float t)
{
    a.x = MathLerp(a.x, b.x, t);
    a.y = MathLerp(a.y, b.y, t);
    a.z = MathLerp(a.z, b.z, t);
    a.w = MathLerp(a.w, b.w, t);
    return a;
}

static inline Vector2 Vector2Zero()
{
    return (Vector2){};
}
static inline Vector3 Vector3Zero()
{
    return (Vector3){};
}
static inline Vector4 Vector4Zero()
{
    return (Vector4){};
}

static inline Vector2 Vector2One()
{
    return (Vector2){ 1, 1 };
}
static inline Vector3 Vector3One()
{
    return (Vector3){ 1, 1, 1 };
}
static inline Vector4 Vector4One()
{
    return (Vector4){ 1, 1, 1, 1 };
}

static inline Vector2 Vector2Left()
{
    return (Vector2){ -1, 0 };
}
static inline Vector2 Vector2Right()
{
    return (Vector2){ +1, 0 };
}
static inline Vector2 Vector2Down()
{
    return (Vector2){ 0, -1 };
}
static inline Vector2 Vector2Up()
{
    return (Vector2){ 0, +1 };
}

static inline Vector3 Vector3Left()
{
    return (Vector3){ -1, 0, 0 };
}
static inline Vector3 Vector3Right()
{
    return (Vector3){ 1, 0, 0 };
}
static inline Vector3 Vector3Up()
{
    return (Vector3){ 0, 1, 0 };
}
static inline Vector3 Vector3Down()
{
    return (Vector3){ 0, 1, 0 };
}
static inline Vector3 Vector3Backward()
{
    return (Vector3){ 0, 0, -1 };
}
static inline Vector3 Vector3Forward()
{
    return (Vector3){ 0, 0, 1 };
}

static inline Vector2 Vector2Normalize(Vector2 v)
{
    // TODO remove "if (length == 0)" ?
    float length = Vector2Length(v);
    if (length == 0) return v;
    return Vector2Div(v, length);
}
static inline Vector3 Vector3Normalize(Vector3 v)
{
    // TODO remove "if (length == 0)" ?
    float length = Vector3Length(v);
    if (length == 0) return v;
    return Vector3Div(v, length);
}
static inline Vector4 Vector4Normalize(Vector4 v)
{
    // TODO remove "if (length == 0)" ?
    float length = Vector4Length(v);
    if (length == 0) return v;
    return Vector4Div(v, length);
}

static inline Vector2 Vector2Dir(Vector2 start, Vector2 end)
{
    Vector2 diff = Vector2Sub(end, start);
    Vector2 dir = Vector2Normalize(diff);
    return dir;
}
static inline Vector3 Vector3Dir(Vector3 start, Vector3 end)
{
    Vector3 diff = Vector3Sub(end, start);
    Vector3 dir = Vector3Normalize(diff);
    return dir;
}
static inline Vector4 Vector4Dir(Vector4 start, Vector4 end)
{
    Vector4 diff = Vector4Sub(end, start);
    Vector4 dir = Vector4Normalize(diff);
    return dir;
}

static inline Vector2 Vector2ClampLength(Vector2 v, float min, float max)
{
    float length = Vector2Length(v);
    if (length <= 0)  return Vector2Zero();
    if (length > max) return Vector2Mul(v, max / length);
    if (length < min) return Vector2Mul(v, min / length);
    return v;
}
static inline Vector3 Vector3ClampLength(Vector3 v, float min, float max)
{
    float length = Vector3Length(v);
    if (length <= 0)  return Vector3Zero();
    if (length > max) return Vector3Mul(v, max / length);
    if (length < min) return Vector3Mul(v, min / length);
    return v;
}
static inline Vector4 Vector4ClampLength(Vector4 v, float min, float max)
{
    float length = Vector4Length(v);
    if (length <= 0)  return Vector4Zero();
    if (length > max) return Vector4Mul(v, max / length);
    if (length < min) return Vector4Mul(v, min / length);
    return v;
}

static inline float Vector2Rotation(Vector2 v)
{
    // atan2( 0.0f,  1.0f ) = 0.0000
    // atan2( 1.0f,  1.0f ) = 0.7853
    // atan2( 1.0f,  0.0f ) = 1.5708
    // atan2( 1.0f, -1.0f ) = 2.3561
    // atan2( 0.0f, -1.0f ) = 3.1415
    return atan2(v.x, v.y);
}

static inline Vector2 Vector2FromRad(float rad)
{
    float sin = MathSin(rad);
    float cos = MathCos(rad);
    return (Vector2){ sin, cos };
}
static inline Vector3 Vector3FromRad(float rad0, float rad1)
{
    float sin0 = MathSin(rad0);
    float sin1 = MathSin(rad1);
    float cos0 = MathCos(rad0);
    float cos1 = MathCos(rad1);
    return (Vector3){ sin0*cos1, sin0*sin1, cos0 };
}

static inline Vector2 Vector2Rotate(Vector2 v, float rad)
{
    float sin = MathSin(rad);
    float cos = MathCos(rad);
    float x = v.x * ( cos) + v.y * ( sin);
    float y = v.x * (-sin) + v.y * ( cos);
    return (Vector2){ x, y };
}

static inline Vector3 Vector3RotateX(Vector3 v, float rad)
{
    float sin = MathSin(rad);
    float cos = MathCos(rad);
    float x = v.x;
    float y = v.y * ( cos) + v.z * ( sin);
    float z = v.y * (-sin) + v.z * ( cos);
    return (Vector3){ x, y, z };
}
static inline Vector3 Vector3RotateY(Vector3 v, float rad)
{
    float sin = MathSin(rad);
    float cos = MathCos(rad);
    float x = v.x * ( cos) + v.z * (-sin);
    float y = v.y;
    float z = v.x * ( sin) + v.z * ( cos);
    return (Vector3){ x, y, z };
}
static inline Vector3 Vector3RotateZ(Vector3 v, float rad)
{
    float sin = MathSin(rad);
    float cos = MathCos(rad);
    float x = v.x * ( cos) + v.y * ( sin);
    float y = v.x * (-sin) + v.y * ( cos);
    float z = v.z;
    return (Vector3){ x, y, z };
}
static inline Vector3 Vector3Rotate(Vector3 v, Vector3 rot)
{
    v = Vector3RotateX(v, rot.x);
    v = Vector3RotateY(v, rot.y);
    v = Vector3RotateZ(v, rot.z);
    return v;
}

static inline Vector2 Vector2MoveTowards1(Vector2 source, Vector2 target, float delta)
{
    if (Vector2Equal(source, target)) return source;
    Vector2 diff = Vector2Sub(target, source);
    float dist = Vector2Length(diff);
    if (dist <= delta) return target;
    diff = Vector2Normalize(diff);
    Vector2 moveVec = Vector2Mul(diff, delta);
    return Vector2Add(source, moveVec);
}
static inline Vector2 Vector2MoveTowards2(Vector2 source, Vector2 target, float delta, float limit)
{
    if (Vector2Equal(source, target)) return source;
    Vector2 diff = Vector2Sub(target, source);
    float dist = Vector2Length(diff);
    if (dist <= limit) return source;
    if (dist <= delta) return target;
    diff = Vector2Normalize(diff);
    Vector2 moveVec = Vector2Mul(diff, delta);
    return Vector2Add(source, moveVec);
}
static inline Vector3 Vector3MoveTowards1(Vector3 source, Vector3 target, float delta)
{
    if (Vector3Equal(source, target)) return source;
    Vector3 diff = Vector3Sub(target, source);
    float dist = Vector3Length(diff);
    if (dist <= delta) return target;
    diff = Vector3Normalize(diff);
    Vector3 moveVec = Vector3Mul(diff, delta);
    return Vector3Add(source, moveVec);
}
static inline Vector3 Vector3MoveTowards2(Vector3 source, Vector3 target, float acc, float deltaTime)
{
    // like easeOut function

    float dist = Vector3Distance(source, target);
    float speed = MathSqrt(2 * dist * acc);
    return Vector3MoveTowards1(source, target, speed * deltaTime);
}
static inline Vector3 Vector3MoveTowards3(Vector3 source, Vector3 target, Vector3* velocity, float acc, float maxSpeed, float deltaTime)
{
    // like easeInOut function
    // but source will decelerate only on rotations

    Vector3 diff = Vector3Sub(target, source);
    Vector3 dir = Vector3Normalize(diff);

    Vector3 targetVelocity = Vector3Mul(dir, maxSpeed);

    Vector3 oldVelocity = *velocity;
    Vector3 newVelocity = Vector3MoveTowards1(oldVelocity, targetVelocity, acc * deltaTime);

    Vector3 offset;

    offset = Vector3Add(oldVelocity, newVelocity);
    offset = Vector3Div(offset, 2);
    offset = Vector3Mul(offset, deltaTime);

    Vector3 result = Vector3Add(source, offset);

    *velocity = newVelocity;

    return result;
}
static inline Vector3 Vector3MoveTowards4(Vector3 source, Vector3 target, Vector3* velocity, float acc, float deltaTime)
{
    // like easeInOut function

    Vector3 diff = Vector3Sub(target, source);
    Vector3 dir = Vector3Normalize(diff);

    float dist = Vector3Length(diff);
    float maxSpeed = MathSqrt(2 * dist * acc);

    Vector3 targetVelocity = Vector3Mul(dir, maxSpeed);

    Vector3 oldVelocity = *velocity;
    Vector3 newVelocity = Vector3MoveTowards1(oldVelocity, targetVelocity, acc * deltaTime);

    Vector3 offset;

    offset = Vector3Add(oldVelocity, newVelocity);
    offset = Vector3Div(offset, 2);
    offset = Vector3Mul(offset, deltaTime);

    Vector3 result = Vector3Add(source, offset);

    *velocity = newVelocity;

    return result;
}
static inline Vector3 Vector3MoveTowards5(Vector3 source, Vector3 target, Vector3* velocity, float acc, float deltaTime)
{
    // like easeInOut function
    // but removes jittering near target

    Vector3 diff = Vector3Sub(target, source);
    Vector3 dir = Vector3Normalize(diff);

    float dist = Vector3Length(diff);

    float maxSpeed = MathSqrt(2 * dist * acc);
    Vector3 targetVelocity = Vector3Mul(dir, maxSpeed);

    Vector3 oldVelocity = *velocity;
    Vector3 newVelocity;

    if (dist < 0.1f)
        newVelocity = targetVelocity;
    else
        newVelocity = Vector3MoveTowards1(oldVelocity, targetVelocity, acc * deltaTime);

    Vector3 offset;

    offset = Vector3Add(oldVelocity, newVelocity);
    offset = Vector3Div(offset, 2);
    offset = Vector3Mul(offset, deltaTime);

    Vector3 result = Vector3Add(source, offset);

    *velocity = newVelocity;

    return result;
}

static inline Vector2 MatrixMultiply2L(Vector2 v, Matrix m)
{
    Vector4 col0 = { m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0] };
    Vector4 col1 = { m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1] };

    Vector4 row = { v.x, v.y, 1, 1 };

    v.x = Vector4Dot(row, col0);
    v.y = Vector4Dot(row, col1);

    return v;
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
    // int a[4] __attribute__((aligned(16))) = { 1, 3, 5, 7 };
    // int b[4] __attribute__((aligned(16))) = { 2, 4, 6, 8 };
    // int c[4] __attribute__((aligned(16)));
    // __vector signed int *va = (__vector signed int *) a;
    // __vector signed int *vb = (__vector signed int *) b;
    // __vector signed int *vc = (__vector signed int *) c;
    // *vc = vec_add(*va, *vb);    // 1 + 2, 3 + 4, 5 + 6, 7 + 8

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
static inline Vector2 MatrixMultiply2R(Matrix m, Vector2 v)
{
    Vector4 col0 = { m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3] };
    Vector4 col1 = { m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3] };

    Vector4 row = { v.x, v.y, 1, 1 };

    v.x = Vector4Dot(row, col0);
    v.y = Vector4Dot(row, col1);

    return v;
}
static inline Vector3 MatrixMultiply3R(Matrix m, Vector3 v)
{
    Vector4 col0 = { m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3] };
    Vector4 col1 = { m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3] };
    Vector4 col2 = { m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3] };

    Vector4 row = { v.x, v.y, v.z, 1 };

    v.x = Vector4Dot(row, col0);
    v.y = Vector4Dot(row, col1);
    v.z = Vector4Dot(row, col2);

    return v;
}
static inline Vector4 MatrixMultiply4R(Matrix m, Vector4 v)
{
    Vector4 col0 = { m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3] };
    Vector4 col1 = { m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3] };
    Vector4 col2 = { m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3] };
    Vector4 col3 = { m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3] };

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
    {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1,
    };
}
static inline Matrix MatrixTranspose(Matrix m)
{
    return (Matrix)
    {
        m.m[0][0],m.m[1][0],m.m[2][0],m.m[3][0],
        m.m[0][1],m.m[1][1],m.m[2][1],m.m[3][1],
        m.m[0][2],m.m[1][2],m.m[2][2],m.m[3][2],
        m.m[0][3],m.m[1][3],m.m[2][3],m.m[3][3]
    };
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
    {
        m00,m01,m02,m03,
        m10,m11,m12,m13,
        m20,m21,m22,m23,
        m30,m31,m32,m33
    };
}
static inline Matrix MatrixRotateX(float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    return (Matrix)
    {
        1,   0,    0,    0,
        0,   cos, -sin,  0,
        0,   sin,  cos,  0,
        0,   0,    0,    1
    };
}
static inline Matrix MatrixRotateY(float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    return (Matrix)
    {
         cos,   0,  sin,   0,
           0,   1,    0,   0,
        -sin,   0,  cos,   0,
           0,   0,    0,   1
    };
}
static inline Matrix MatrixRotateZ(float rad)
{
    float sin = sinf(rad);
    float cos = cosf(rad);
    return (Matrix)
    {
        cos, -sin,  0,   0,
        sin,  cos,  0,   0,
        0,    0,    1,   0,
        0,    0,    0,   1
    };
}
static inline Matrix MatrixTranslate(Vector3 position)
{
    Vector3 v = position;
    return (Matrix)
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        v.x, v.y, v.z, 1
    };
}
static inline Matrix MatrixRotate(Vector3 rotation)
{
    Matrix result;
    Matrix matX = MatrixRotateX(rotation.x);
    Matrix matY = MatrixRotateY(rotation.y);
    Matrix matZ = MatrixRotateZ(rotation.z);
    result = matX;
    result = MatrixMultiply(result, matY);
    result = MatrixMultiply(result, matZ);
    return result;
}
static inline Matrix MatrixScale(Vector3 scale)
{
    float x = scale.x;
    float y = scale.y;
    float z = scale.z;
    return (Matrix)
    {
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    };
}
static inline Matrix MatrixWorld(Vector3 position, Vector3 rotation, Vector3 scale)
{
    Matrix result;
    Matrix mat1 = MatrixScale(scale);
    Matrix mat2 = MatrixRotate(rotation);
    Matrix mat3 = MatrixTranslate(position);
    result = mat1;
    result = MatrixMultiply(result, mat2);
    result = MatrixMultiply(result, mat3);
    return result;
}
static inline Matrix MatrixWorldDir(Vector3 position, Vector3 direction)
{
    Vector3 zAxis = direction;
            zAxis = Vector3Normalize(zAxis); // maybe remove

    Vector3 xAxis = Vector3Cross(Vector3Up(), zAxis);
            xAxis = Vector3Normalize(xAxis);

    Vector3 yAxis = Vector3Cross(zAxis, xAxis);

    float x = position.x;
    float y = position.y;
    float z = position.z;

    return (Matrix)
    {
        xAxis.x, xAxis.y, xAxis.z, 0.0f,
        yAxis.x, yAxis.y, yAxis.z, 0.0f,
        zAxis.x, zAxis.y, zAxis.z, 0.0f,
              x,       y,       z, 1.0f
    };
}
static inline Matrix MatrixView1(Vector3 eye, float yaw, float pitch)
{
    eye = Vector3Neg(eye);
    Matrix mat1 = MatrixTranslate(eye);
    Matrix mat2 = MatrixRotateY(yaw);
    Matrix mat3 = MatrixRotateX(-pitch);
    Matrix result;
    result = mat1;
    result = MatrixMultiply(result, mat2);
    result = MatrixMultiply(result, mat3);
    return result;
}
static inline Matrix MatrixView2(Vector3 eye, Vector3 target, Vector3 up)
{
    // it almost works, try fixing it
    /*
    Vector3 zAxis = Vector3Sub(target, eye);
            zAxis = Vector3Normalize(zAxis);

    Vector3 xAxis = Vector3Cross(up, zAxis);
            xAxis = Vector3Normalize(xAxis);

    Vector3 yAxis = Vector3Cross(zAxis, xAxis);

    float x = -Vector3Dot(xAxis, eye);
    float y = -Vector3Dot(yAxis, eye);
    float z = -Vector3Dot(zAxis, eye);

    return (Matrix)
    {
        xAxis.x, xAxis.y, xAxis.z, 0.0f,
        yAxis.x, yAxis.y, yAxis.z, 0.0f,
        zAxis.x, zAxis.y, zAxis.z, 0.0f,
              x,       y,       z, 1.0f
    };
    */

    Vector3 zAxis = Vector3Sub(target, eye);
            zAxis = Vector3Normalize(zAxis);

    Vector3 xAxis = Vector3Cross(up, zAxis);
            xAxis = Vector3Normalize(xAxis);

    Vector3 yAxis = Vector3Cross(zAxis, xAxis);

    Matrix result =
    {
        xAxis.x, xAxis.y, xAxis.z, 0,
        yAxis.x, yAxis.y, yAxis.z, 0,
        zAxis.x, zAxis.y, zAxis.z, 0,
          eye.x,   eye.y,   eye.z, 1
    };

    result = MatrixInvert(result);

    return result;
}
static inline Matrix MatrixView3(Camera* camera)
{
    return MatrixView1(camera->position, camera->yaw, camera->pitch);
}
static inline Matrix MatrixProjOrthographic(float width, float height, float near, float far)
{
    float w = 2.0f / width;
    float h = 2.0f / height;
    float a = 1.0f / (far - near);
    float b = a * -near;
    return (Matrix)
    {
        w, 0, 0, 0,
        0, h, 0, 0,
        0, 0, a, 0,
        0, 0, b, 1
    };
}
static inline Matrix MatrixProjPerspective1(float width, float height, float near, float far)
{
    width /= height;
    height = 1;

    width *= near;
    height *= near;

    float n = near;
    float f = far;

    float r =  width;
    float t =  height;
    float l = -width;
    float b = -height;

    float x =  (2*n) / (r-l);
    float y =  (2*n) / (t-b);
    float z =  (f+n) / (f-n);

    // maybe remove
    // float u = (r+l) / (r-l);
    // float i = (t+b) / (t-b);
    // float o = (2*f*n) / (f-n);
    // return (Matrix)
    // {
    //     x,  0,  0,  0,
    //     0,  y,  0,  0,
    //    -u, -i,  z,  1,
    //     0,  0, -o,  0
    // };

    float o = (2*f*n) / (f-n);

    return (Matrix)
    {
        x,  0,  0,  0,
        0,  y,  0,  0,
        0,  0,  z,  1,
        0,  0, -o,  0
    };
}
static inline Matrix MatrixProjPerspective2(float width, float height, float near, float far)
{
    float n = near;
    float f = far;

    float aspectRatio = width / height;
    float fov = (float)(MATH_PI_DIV_2);
    float h = 1.0f / tanf(fov / 2);
    float w = h / aspectRatio;
    float a = f / (f - n);
    float o = a * n;

    return (Matrix)
    {
        w,  0,  0,  0,
        0,  h,  0,  0,
        0,  0,  a,  1,
        0,  0, -o,  0
    };
}
static inline Matrix MatrixProjPerspective3(float width, float height, float near, float far, float fov)
{
    float ratio = width / height;

    float h = 1.0f / tanf(fov / 2);
    float w = h / ratio;
    float a = far / (far - near);
    float o = a * near;

    return (Matrix)
    {
        w,  0,  0,  0,
        0,  h,  0,  0,
        0,  0,  a,  1,
        0,  0, -o,  0
    };
}

static inline Vector3 ToEuler(Vector4 q)
{
    Vector3 result;

    float x = q.x;
    float y = q.y;
    float z = q.z;
    float w = q.w;

    float x0 = 2.0f*(w*x + y*z);
    float x1 = 1.0f - 2.0f*(x*x + y*y);
    result.x = atan2f(x0, x1);

    float y0 = 2.0f*(w*y - z*x);
    y0 = y0 >  1.0f ?  1.0f : y0;
    y0 = y0 < -1.0f ? -1.0f : y0;
    result.y = asinf(y0);

    float z0 = 2.0f*(w*z + x*y);
    float z1 = 1.0f - 2.0f*(y*y + z*z);
    result.z = atan2f(z0, z1);

    return result;
}
static inline Vector4 ToQuaternion(Vector3 e)
{
    Vector4 result;

    float pitch = e.x /= 2;
    float yaw   = e.y /= 2;
    float roll  = e.z /= 2;

    float x0 = cosf(pitch);
    float x1 = sinf(pitch);
    float y0 = cosf(yaw);
    float y1 = sinf(yaw);
    float z0 = cosf(roll);
    float z1 = sinf(roll);

    result.x = x1*y0*z0 - x0*y1*z1;
    result.y = x0*y1*z0 + x1*y0*z1;
    result.z = x0*y0*z1 - x1*y1*z0;
    result.w = x0*y0*z0 + x1*y1*z1;

    return result;
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
    // maybe
    // Vector4 _p;
    // _p.x = p.x * proji.m[0][0];
    // _p.y = p.y;
    // _p.z = 1;
    // _p.w = p.z * proji.m[2][3] + proji.m[3][3];
    // _p.x /= _p.w;
    // _p.y /= _p.w;
    // _p.z /= _p.w;
    // _p.w = 1;
    // _p = MatrixMultiply4L(_p, viewi);
    // return (Vector3){ _p.x, _p.y, _p.z };

    Vector4 _p = { p.x, p.y, p.z, 1 };
    _p = MatrixMultiply4L(_p, proji);
    _p.x /= _p.w;
    _p.y /= _p.w;
    _p.z /= _p.w;
    _p.w = 1;
    _p = MatrixMultiply4L(_p, viewi);
    return (Vector3){ _p.x, _p.y, _p.z };
}

static inline float NdcToWorldZ(Vector3 p, Matrix proji)
{
    Vector4 v = { p.x, p.y, p.z, 1 };
    Matrix m = proji;
    Vector4 col2 = { m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2] };
    Vector4 col3 = { m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3] };
    Vector4 row = v;
    v.z = Vector4Dot(row, col2);
    v.w = Vector4Dot(row, col3);
    v.z /= v.w;
    return v.z;
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

static inline Vector3 CameraGetAxisX(Camera* camera)
{
    Vector3 result = { 1, 0, 0 };
    result = Vector3RotateX(result, camera->pitch);
    result = Vector3RotateY(result, -camera->yaw);
    return result;
}
static inline Vector3 CameraGetAxisY(Camera* camera)
{
    Vector3 result = { 0, 1, 0 };
    result = Vector3RotateX(result, camera->pitch);
    result = Vector3RotateY(result, -camera->yaw);
    return result;
}
static inline Vector3 CameraGetAxisZ(Camera* camera)
{
    Vector3 result = { 0, 0, 1 };
    result = Vector3RotateX(result, camera->pitch);
    result = Vector3RotateY(result, -camera->yaw);
    return result;
}

static inline void CameraRotateClamped(Camera* camera, Vector2 rot)
{
    camera->yaw    += rot.x;
    camera->pitch  += rot.y;

    float angle = 90;
    // float angle = 100; // 100 feels better

    camera->yaw = MathMod(camera->yaw, MATH_PI_MUL_2);
    camera->pitch = MathClamp(camera->pitch, MathToRadians(-angle), MathToRadians(angle));
}
static inline void CameraMoveFree(Camera* camera, Vector3 move)
{
    // TODO double check it works

    Vector3 x = CameraGetAxisX(camera);
    Vector3 y = CameraGetAxisY(camera);
    Vector3 z = CameraGetAxisZ(camera);

    x = Vector3Mul(x, move.x);
    y = Vector3Mul(y, move.y);
    z = Vector3Mul(z, move.z);
    // x.x *= move.x; x.y *= move.x; x.z *= move.x;
    // y.x *= move.y; y.y *= move.y; y.z *= move.y;
    // z.x *= move.z; z.y *= move.z; z.z *= move.z;

    camera->position = Vector3Add(camera->position, z);
    camera->position = Vector3Add(camera->position, y);
    camera->position = Vector3Add(camera->position, x);
}
static inline void CameraMovePlane(Camera* camera, Vector2 move)
{
    Vector3 up = { 0, 1, 0 };
    Vector3 forward = { 0, 0, 1 };

    forward = Vector3RotateY(forward, -camera->yaw);

    Vector3 right = Vector3Cross(up, forward);

    forward.x *= move.y;
    forward.z *= move.y;
    right.x *= move.x;
    right.z *= move.x;

    camera->position = Vector3Add(camera->position, forward);
    camera->position = Vector3Add(camera->position, right);
}

static inline void CameraInputRotateClamped(Camera* camera, float distance, bool left, bool up, bool down, bool right)
{
    int x = (int)right - (int)left;
    int y = (int)up - (int)down;

    Vector2 rot = { (float)x, (float)y };

    rot = Vector2Normalize(rot);
    rot = Vector2Mul(rot, distance);

    CameraRotateClamped(camera, rot);
}
static inline void CameraInputMoveFree(Camera* camera, float distance, bool w, bool a, bool s, bool d, bool e, bool q)
{
    int x = (int)d - (int)a;
    int y = (int)e - (int)q;
    int z = (int)w - (int)s;

    Vector3 move = { (float)x, (float)y, (float)z };

    move = Vector3Normalize(move);
    move = Vector3Mul(move, distance);

    CameraMoveFree(camera, move);
}
static inline void CameraInputMovePlane(Camera* camera, float distance, bool w, bool a, bool s, bool d)
{
    int x = (int)d - (int)a;
    int y = (int)w - (int)s;

    Vector2 move = { (float)x, (float)y };

    move = Vector2Normalize(move);
    move = Vector2Mul(move, distance);

    CameraMovePlane(camera, move);
}

static inline Vector3 BoundSize(Bound* bound)
{
    Vector3 result = Vector3Sub(bound->p0, bound->p1);
    result.x = MathAbs(result.x);
    result.y = MathAbs(result.y);
    result.z = MathAbs(result.z);
    return result;
}
static inline Vector3 BoundCenter(Bound* bound)
{
    Vector3 result;
    result = Vector3Add(bound->p0, bound->p1);
    result = Vector3Div(result, 2);
    return result;
}
static inline Vector3 BoundWrapAround(Bound* bound, Vector3 point)
{
    Vector3 size = BoundSize(bound);
    if      (point.x < MathMin(bound->p0.x, bound->p1.x)) point.x += size.x;
    else if (point.x > MathMax(bound->p0.x, bound->p1.x)) point.x -= size.x;
    if      (point.y < MathMin(bound->p0.y, bound->p1.y)) point.y += size.y;
    else if (point.y > MathMax(bound->p0.y, bound->p1.y)) point.y -= size.y;
    if      (point.z < MathMin(bound->p0.z, bound->p1.z)) point.z += size.z;
    else if (point.z > MathMax(bound->p0.z, bound->p1.z)) point.z -= size.z;
    return point;
}
static inline Vector3 BoundShortPathIn(Bound* bound, Vector3 point)
{
    Vector3 result = Vector3Zero(); float value;
    if      (point.x < (value = MathMin(bound->p0.x, bound->p1.x))) result.x = value - point.x;
    else if (point.x > (value = MathMax(bound->p0.x, bound->p1.x))) result.x = value - point.x;
    if      (point.y < (value = MathMin(bound->p0.y, bound->p1.y))) result.y = value - point.y;
    else if (point.y > (value = MathMax(bound->p0.y, bound->p1.y))) result.y = value - point.y;
    if      (point.z < (value = MathMin(bound->p0.z, bound->p1.z))) result.z = value - point.z;
    else if (point.z > (value = MathMax(bound->p0.z, bound->p1.z))) result.z = value - point.z;
    return result;
}

static inline float TriangleArea(Vector3 v0, Vector3 v1, Vector3 v2)
{
    float r1 = v0.x * (v1.y - v2.y);
    float r2 = v1.x * (v2.y - v0.y);
    float r3 = v2.x * (v0.y - v1.y);
    return MathAbs((r1 + r2 + r3) / 2.0f);
}
static inline bool TriangleIsClockwise(Vector3 v0, Vector3 v1, Vector3 v2)
{
    Vector3 d0 = Vector3Sub(v1, v0);
    Vector3 d1 = Vector3Sub(v2, v0);
    float crossZ = d0.x*d1.y - d0.y*d1.x;
    return crossZ < 0;
}

static inline bool TriangleIsInside1(Vector3 v0, Vector3 v1, Vector3 v2, float x, float y)
{
    // by area approximation

    Vector3 v = { x, y, 0 };

    float A0 = TriangleArea(v0, v1, v2);
    float A1 = TriangleArea(v,  v1, v2);
    float A2 = TriangleArea(v0, v,  v2);
    float A3 = TriangleArea(v0, v1, v );

    // handles rounding error
    A0 += 1e-3f;

    return A0 > (A1 + A2 + A3);
}
static inline bool TriangleIsInside2(Vector3 v0, Vector3 v1, Vector3 v2, float x, float y)
{
    // by cross

    Vector2 p0 = { x, y };

    Vector2 p1 = { v0.x, v0.y };
    Vector2 p2 = { v1.x, v1.y };
    Vector2 p3 = { v2.x, v2.y };

    Vector2 vec0 = Vector2Sub(p2, p1);
    Vector2 vec1 = Vector2Sub(p0, p1);
    if (Vector2Cross(vec0, vec1) < 0)
        return false;

    Vector2 vec2 = Vector2Sub(p3, p2);
    Vector2 vec3 = Vector2Sub(p0, p2);
    if (Vector2Cross(vec2, vec3) < 0)
        return false;

    Vector2 vec4 = Vector2Sub(p1, p3);
    Vector2 vec5 = Vector2Sub(p0, p3);
    if (Vector2Cross(vec4, vec5) < 0)
        return false;

    return true;
}
static inline bool TriangleIsInside3(Vector3 v0, Vector3 v1, Vector3 v2, float x, float y)
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

static inline float TriangleBarycentric1(Vector3 v0, Vector3 v1, Vector3 v2, float x, float y)
{
    Vector3 p = { x, y, 0 };

    float area  = TriangleArea(v0, v1, v2);
    float area1 = TriangleArea( p, v1, v2);
    float area2 = TriangleArea(v0,  p, v2);
    float area3 = TriangleArea(v0, v1,  p);

    float t1 = area1 / area;
    float t2 = area2 / area;
    float t3 = area3 / area;

    float result =
        t1 * v0.z +
        t2 * v1.z +
        t3 * v2.z;

    // TODO fix nan
    return __isnanf(result) ? 1 : result;
}
static inline float TriangleBarycentric2(Vector3 v0, Vector3 v1, Vector3 v2, float x, float y)
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

static inline bool SpherePointInside(Sphere sphere, Vector3 point)
{
    Vector3 diff = Vector3Sub(point, sphere.position);
    float radiusSquared = sphere.radius * sphere.radius;
    float diffLengthSquared = Vector3LengthSquared(diff);
    return diffLengthSquared <= radiusSquared;
}
static inline bool CylinderPointInside(Vector3 point, Vector3 pos, float height, float radius)
{
    point = Vector3Sub(point, pos);
    if (point.y < 0) return false;
    if (point.y > height) return false;
    point.y = 0;
    Vector2 v = { point.x, point.z };
    if (Vector2Length(v) > radius) return false;
    return true;
}

static inline void PushOutCylinder(Vector3* point, Vector3 pos, float height, float radius)
{
    Vector3 v = Vector3Sub(*point, pos);
    if (v.y < 0) return;
    if (v.y > height) return;
    v.y = 0;
    Vector2 v0 = { v.x, v.z };
    float length = Vector2Length(v0);
    if (length == 0)
    {
        point->x += radius;
        return;
    }
    if (length > radius) return;
    v = Vector3Div(v, length);
    v = Vector3Mul(v, radius);
    Vector3 v1 = { pos.x, point->y, pos.z };
    *point = Vector3Add(v1, v);
}
static inline void PushOutBound(Vector3* point, Bound bound)
{
    float minx = MathMin(bound.p0.x, bound.p1.x); float maxx = MathMax(bound.p0.x, bound.p1.x); if (point->x < minx || maxx < point->x) return;
    float miny = MathMin(bound.p0.y, bound.p1.y); float maxy = MathMax(bound.p0.y, bound.p1.y); if (point->y < miny || maxy < point->y) return;
    float minz = MathMin(bound.p0.z, bound.p1.z); float maxz = MathMax(bound.p0.z, bound.p1.z); if (point->z < minz || maxz < point->z) return;

    float xl = minx - point->x; float xla = -xl;
    float xr = maxx - point->x; float xra = +xr;
    float yl = miny - point->y; float yla = -yl;
    float yr = maxy - point->y; float yra = +yr;
    float zl = minz - point->z; float zla = -zl;
    float zr = maxz - point->z; float zra = +zr;

    float min; int cond;

                   { min = xla; cond = 0; }
    if (min > xra) { min = xra; cond = 1; }
    if (min > yla) { min = yla; cond = 2; }
    if (min > yra) { min = yra; cond = 3; }
    if (min > zla) { min = zla; cond = 4; }
    if (min > zra) {            cond = 5; }

    switch (cond)
    {
        case 0: point->x += xl; break;
        case 1: point->x += xr; break;
        case 2: point->y += yl; break;
        case 3: point->y += yr; break;
        case 4: point->z += zl; break;
        case 5: point->z += zr; break;
    }
}

static inline bool RaycastPlane(Vector3 origin, Vector3 dirNorm, Vector3 planePosition, Vector3 planeNormal)
{
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection.html

    float epsilon = 1e-6;
    float dot1 = Vector3Dot(dirNorm, planeNormal);
    if (MathAbs(dot1) < epsilon) return false;
    Vector3 diff1 = Vector3Sub(planePosition, origin);
    float dot2 = Vector3Dot(diff1, planeNormal);
    float rayLenght = dot2 / dot1;
    return rayLenght >= 0;
    // *rayLength = dot2 / dot1;
    // return *rayLength >= 0;
}
static inline bool RaycastSphere(Vector3 origin, Vector3 dirNorm, Sphere sphere)
{
    Vector3 v1 = Vector3Sub(sphere.position, origin);

    float v2Length = Vector3Dot(dirNorm, v1);

    Vector3 v2 = Vector3Mul(dirNorm, v2Length);
    Vector3 v3 = Vector3Sub(v2, v1);

    float v3LengthSquared = Vector3LengthSquared(v3);
    float radiusSquared = sphere.radius * sphere.radius;

    if (v3LengthSquared > radiusSquared)
        return false;

    // float offset = MathSqrt(radiusSquared - v3LengthSquared);

    // float dist1 = v2Length - offset;
    // float dist2 = v2Length + offset;

    // Vector3 point1 = Vector3Add(origin, Vector3Mul(dirNorm, dist1));
    // Vector3 point2 = Vector3Add(origin, Vector3Mul(dirNorm, dist2));

    // Vector3 normal1 = Vector3Sub(point1, sphere.position);
    // Vector3 normal2 = Vector3Sub(point2, sphere.position);

    // normal1 = Vector3Normalize(normal1);
    // normal2 = Vector3Normalize(normal2);

    return true;
}
static inline bool RaycastTriangleV1(Vector3 origin, Vector3 dirNorm, Vector3 v0, Vector3 v1, Vector3 v2)
{
    Vector3 ab = Vector3Sub(v1, v0);
    Vector3 ac = Vector3Sub(v2, v0);

    Vector3 dirNormNeg = Vector3Neg(dirNorm);

    Vector3 n = Vector3Cross(ab, ac);

    float d = Vector3Dot(dirNormNeg, n);
    if (d <= 0.0f) return false;

    Vector3 ap = Vector3Sub(origin, v0);
    float t = Vector3Dot(ap, n);
    if (t < 0.0f) return false;

    Vector3 e = Vector3Cross(dirNormNeg, ap);
    float v = Vector3Dot(ac, e);
    if (v < 0.0f || v > d) return false;

    float w = -Vector3Dot(ab, e);
    if (w < 0.0f || v + w > d) return false;

    // // Segment/ray intersects triangle. Perform delayed division and
    // // compute the last barycentric coordinate component
    // float ood = 1.0f / d;
    // t *= ood;
    // v *= ood;
    // w *= ood;
    // float u = 1.0f - v - w;

    // RaycastHit hit = new RaycastHit();

    // hit.point = ray.origin + t * ray.direction;
    // hit.distance = t;
    // hit.barycentricCoordinate = new Vector3(u, v, w);
    // hit.normal = Vector3.Normalize(n);

    return true;
}
static inline bool RaycastTriangleV2(Vector3 origin, Vector3 dirNorm, Vector3 v0, Vector3 v1, Vector3 v2)
{
    // ignores face direction
    // refactor

    v0 = Vector3Sub(v0, origin);
    v1 = Vector3Sub(v1, origin);
    v2 = Vector3Sub(v2, origin);

    Vector2 vec1 = { dirNorm.x, dirNorm.z };
    // vec1 = Vector2Normalize(vec1);
    float yaw = Vector2Rotation(vec1);
    v0 = Vector3RotateY(v0, yaw);
    v1 = Vector3RotateY(v1, yaw);
    v2 = Vector3RotateY(v2, yaw);

    dirNorm = Vector3RotateY(dirNorm, yaw);

    Vector2 vec2 = { dirNorm.y, dirNorm.z };
    // vec2 = Vector2Normalize(vec2);
    float pitch = Vector2Rotation(vec2);
    v0 = Vector3RotateX(v0, -pitch);
    v1 = Vector3RotateX(v1, -pitch);
    v2 = Vector3RotateX(v2, -pitch);

    bool isInside = TriangleIsInside2(v0, v1, v2, 0, 0);
    if (!isInside)
        return false;

    float z = TriangleBarycentric2(v0, v1, v2, 0, 0);
    if (z < 0)
        return false;

    return true;
}
static inline bool RaycastTriangleV3(Vector3 origin, Vector3 dirNorm, Vector3 v0, Vector3 v1, Vector3 v2)
{
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution.html
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage.html

    float epsilon = 1e-6;

    Vector3 d0 = Vector3Sub(v1, v0);
    Vector3 d1 = Vector3Sub(v2, v1);
	Vector3 d2 = Vector3Sub(v0, v2);

    // No need to normalize
    Vector3 normal = Vector3Cross(d0, d1);

    float dot1 = Vector3Dot(normal, dirNorm);

    // planes are almost parallel
    if (MathAbs(dot1) < epsilon)
        return false;

    float dot2 = Vector3Dot(normal, origin);
    float dot3 = Vector3Dot(normal, v0);

    float rayLenght = (dot3 - dot2) / dot1;

    // triangle is behind ray
    if (rayLenght < 0)
        return false;

    // p = origin + dirNorm * rayLenght;
    Vector3 p = Vector3Add(origin, Vector3Mul(dirNorm, rayLenght));

    Vector3 p0 = Vector3Sub(p, v0);
    Vector3 n0 = Vector3Cross(d0, p0);
    if (Vector3Dot(normal, n0) < 0) return false;

    Vector3 p1 = Vector3Sub(p, v1);
    Vector3 n1 = Vector3Cross(d1, p1);
    if (Vector3Dot(normal, n1) < 0) return false;

    Vector3 p2 = Vector3Sub(p, v2);
    Vector3 n2 = Vector3Cross(d2, p2);
    if (Vector3Dot(normal, n2) < 0) return false;

    return true;
}
static inline bool RaycastTriangle(Vector3 origin, Vector3 dirNorm, Vector3 v0, Vector3 v1, Vector3 v2)
{
    // return RaycastTriangleV1(origin, dirNorm, v0, v1, v2);
    // return RaycastTriangleV2(origin, dirNorm, v0, v1, v2);
    return RaycastTriangleV3(origin, dirNorm, v0, v1, v2);
}
static inline bool LinecastTriangle(Vector3 start, Vector3 end, Vector3 v0, Vector3 v1, Vector3 v2)
{
    Vector3 origin = start;

    Vector3 dir = Vector3Sub(end, start);
    Vector3 dirNorm = Vector3Normalize(dir);

    float epsilon = 1e-6;

    Vector3 d0 = Vector3Sub(v1, v0);
    Vector3 d1 = Vector3Sub(v2, v1);
	Vector3 d2 = Vector3Sub(v0, v2);

    // No need to normalize
    Vector3 normal = Vector3Cross(d0, d1);

    float dot1 = Vector3Dot(normal, dirNorm);

    // planes are almost parallel
    if (MathAbs(dot1) < epsilon)
        return false;

    float dot2 = Vector3Dot(normal, origin);
    float dot3 = Vector3Dot(normal, v0);

    float rayLenght = (dot3 - dot2) / dot1;

    // triangle is behind ray
    if (rayLenght < 0)
        return false;

    // p = origin + dirNorm * rayLenght;
    Vector3 p = Vector3Add(origin, Vector3Mul(dirNorm, rayLenght));

    Vector3 p0 = Vector3Sub(p, v0);
    Vector3 n0 = Vector3Cross(d0, p0);
    if (Vector3Dot(normal, n0) < 0) return false;

    Vector3 p1 = Vector3Sub(p, v1);
    Vector3 n1 = Vector3Cross(d1, p1);
    if (Vector3Dot(normal, n1) < 0) return false;

    Vector3 p2 = Vector3Sub(p, v2);
    Vector3 n2 = Vector3Cross(d2, p2);
    if (Vector3Dot(normal, n2) < 0) return false;

    // handles rounding error
    // rayLenght += 1e-3f;
    rayLenght += epsilon;

    // line is not hit
    // float lineLength = MathSqrt(dir.x*dir.x + dir.y*dir.y + dir.z*dir.z);
    // if (rayLenght - lineLength > 0.1f)
    //     return false;

    // line is not hit
    float rayLengthSqr = rayLenght * rayLenght;
    float lineLengthSqr = dir.x*dir.x + dir.y*dir.y + dir.z*dir.z;
    if (rayLengthSqr - lineLengthSqr > 0)
        return false;

    return true;
}

static inline Pose PoseGetLocal(Pose parentWorld, Pose childWorld)
{
    childWorld.rotation = Vector3Sub(childWorld.rotation, parentWorld.rotation);
    childWorld.position = Vector3Sub(childWorld.position, parentWorld.position);
    childWorld.position = Vector3RotateZ(childWorld.position, -parentWorld.rotation.z);
    childWorld.position = Vector3RotateY(childWorld.position, -parentWorld.rotation.y);
    childWorld.position = Vector3RotateX(childWorld.position, -parentWorld.rotation.x);
    return childWorld;
}
static inline Pose PoseGetWorld(Pose parentWorld, Pose childLocal)
{
    childLocal.position = Vector3RotateX(childLocal.position, parentWorld.rotation.x);
    childLocal.position = Vector3RotateY(childLocal.position, parentWorld.rotation.y);
    childLocal.position = Vector3RotateZ(childLocal.position, parentWorld.rotation.z);
    childLocal.position = Vector3Add(childLocal.position, parentWorld.position);
    childLocal.rotation = Vector3Add(childLocal.rotation, parentWorld.rotation);
    return childLocal;
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
