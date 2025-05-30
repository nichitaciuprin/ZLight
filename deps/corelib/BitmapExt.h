#pragma once

#include "Bitmap.h"
#include "Models.h"

static inline void BitmapFillBorder(Bitmap* bitmap, float color)
{
    int x = bitmap->width - 1;
    int y = bitmap->height - 1;
    for (int i = 0; i < bitmap->width;  i++) BitmapSetPixel(bitmap, i, 0, color);
    for (int i = 0; i < bitmap->width;  i++) BitmapSetPixel(bitmap, i, y, color);
    for (int i = 0; i < bitmap->height; i++) BitmapSetPixel(bitmap, 0, i, color);
    for (int i = 0; i < bitmap->height; i++) BitmapSetPixel(bitmap, x, i, color);
}
static inline void BitmapFillCross(Bitmap* bitmap, float color)
{
    for (int i = 0; i < bitmap->width;  i++) BitmapSetPixel(bitmap, i, bitmap->height-1 / 2, color);
    for (int i = 0; i < bitmap->height; i++) BitmapSetPixel(bitmap, bitmap->width-1 / 2, i, color);
}
static inline void BitmapDrawTriangleWire(Bitmap* bitmap, Vector3 v0, Vector3 v1, Vector3 v2)
{
    BitmapDrawLine(bitmap, v0, v1);
    BitmapDrawLine(bitmap, v1, v2);
    BitmapDrawLine(bitmap, v2, v0);
}
static inline void BitmapDrawQuad(Bitmap* bitmap, Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3)
{
    BitmapDrawTriangle(bitmap, v0, v1, v2);
    BitmapDrawTriangle(bitmap, v2, v3, v0);
}
static inline void BitmapDrawPoligonWire(Bitmap* bitmap, Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3)
{
    BitmapDrawTriangleWire(bitmap, v0, v1, v2);
    BitmapDrawTriangleWire(bitmap, v2, v3, v0);
}
static inline void BitmapDrawCube(Bitmap* bitmap, Vector3 position, Vector3 rotation, Vector3 scale)
{
    Matrix model = MatrixWorld(position, rotation, scale);

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
        p0 = MatrixMultiply3L(p0, model);          \
        p1 = MatrixMultiply3L(p1, model);          \
        p2 = MatrixMultiply3L(p2, model);          \
        p3 = MatrixMultiply3L(p3, model);          \
        BitmapDrawQuad(bitmap, p0, p1, p2, p3); \
    }                                              \

    DRAW(0)
    DRAW(1)
    DRAW(2)
    DRAW(3)
    DRAW(4)
    DRAW(5)

    #undef DRAW
}
static inline void BitmapDrawCube2(Bitmap* bitmap, Matrix model)
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
        p0 = MatrixMultiply3L(p0, model);          \
        p1 = MatrixMultiply3L(p1, model);          \
        p2 = MatrixMultiply3L(p2, model);          \
        p3 = MatrixMultiply3L(p3, model);          \
        BitmapDrawQuad(bitmap, p0, p1, p2, p3); \
    }                                              \

    DRAW(0)
    DRAW(1)
    DRAW(2)
    DRAW(3)
    DRAW(4)
    DRAW(5)

    #undef DRAW
}
static inline void BitmapDrawCubeWire(Bitmap* bitmap, Vector3 position, Vector3 rotation, Vector3 scale)
{
    Matrix model = MatrixWorld(position, rotation, scale);

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
static inline void BitmapDrawSphere(Bitmap* bitmap, Vector3 position)
{
    if (Hiden(position, 1.0f, bitmap->view, bitmap->far)) return;

    for (size_t i = 0; i < 60; i++)
    {
        int i0 = ModelWall1IndecesTriangles[i][0];
        int i1 = ModelWall1IndecesTriangles[i][1];
        int i2 = ModelWall1IndecesTriangles[i][2];
        Vector3 v0 = ModelSphereVerteces[i0];
        Vector3 v1 = ModelSphereVerteces[i1];
        Vector3 v2 = ModelSphereVerteces[i2];
        v0 = Vector3Add(v0, position);
        v1 = Vector3Add(v1, position);
        v2 = Vector3Add(v2, position);
        BitmapDrawTriangle(bitmap, v0, v1, v2);
    }
}
static inline void BitmapDrawSphereWire(Bitmap* bitmap, Vector3 position)
{
    for (size_t i = 0; i < 60; i++)
    {
        int i0 = ModelWall1IndecesTriangles[i][0];
        int i1 = ModelWall1IndecesTriangles[i][1];
        int i2 = ModelWall1IndecesTriangles[i][2];
        Vector3 v0 = ModelSphereVerteces[i0];
        Vector3 v1 = ModelSphereVerteces[i1];
        Vector3 v2 = ModelSphereVerteces[i2];
        v0 = Vector3Add(v0, position);
        v1 = Vector3Add(v1, position);
        v2 = Vector3Add(v2, position);
        BitmapDrawTriangleWire(bitmap, v0, v1, v2);
    }
}
static inline void BitmapDrawBoundWire(Bitmap* bitmap, Bound bound)
{
    float maxx = MathMax(bound.p0.x, bound.p1.x);
    float maxy = MathMax(bound.p0.y, bound.p1.y);
    float maxz = MathMax(bound.p0.z, bound.p1.z);
    float minx = MathMin(bound.p0.x, bound.p1.x);
    float miny = MathMin(bound.p0.y, bound.p1.y);
    float minz = MathMin(bound.p0.z, bound.p1.z);

    Vector3 v0 = { minx, miny, minz };
    Vector3 v1 = { minx, miny, maxz };
    Vector3 v2 = { minx, maxy, minz };
    Vector3 v3 = { minx, maxy, maxz };
    Vector3 v4 = { maxx, miny, minz };
    Vector3 v5 = { maxx, miny, maxz };
    Vector3 v6 = { maxx, maxy, minz };
    Vector3 v7 = { maxx, maxy, maxz };

    BitmapDrawLine(bitmap, v0, v1);
    BitmapDrawLine(bitmap, v1, v5);
    BitmapDrawLine(bitmap, v5, v4);
    BitmapDrawLine(bitmap, v4, v0);
    BitmapDrawLine(bitmap, v2, v3);
    BitmapDrawLine(bitmap, v3, v7);
    BitmapDrawLine(bitmap, v7, v6);
    BitmapDrawLine(bitmap, v6, v2);
    BitmapDrawLine(bitmap, v0, v2);
    BitmapDrawLine(bitmap, v1, v3);
    BitmapDrawLine(bitmap, v5, v7);
    BitmapDrawLine(bitmap, v4, v6);
}
static inline void DrawGrid(Bitmap* bitmap)
{
    int count = 100;

    for (int i = 0; i < count; i++)
    {
        float offset = (float)i-count/2;
        Vector3 v0 = { offset, 0, -(float)count };
        Vector3 v1 = { offset, 0, +(float)count };
        BitmapDrawLine(bitmap, v0, v1);
    }

    for (int i = 0; i < count; i++)
    {
        float offset = (float)i-count/2;
        Vector3 v0 = { -(float)count, 0, offset };
        Vector3 v1 = { +(float)count, 0, offset };
        BitmapDrawLine(bitmap, v0, v1);
    }
}
static inline void DrawPlane(Bitmap* bitmap)
{
    float size = 100;

    Vector3 p0 = { +size, 0, +size };
    Vector3 p1 = { +size, 0, -size };
    Vector3 p2 = { -size, 0, -size };
    Vector3 p3 = { -size, 0, +size };

    BitmapDrawQuad(bitmap, p0, p1, p2, p3);
}
static inline void DrawPlane(Bitmap* bitmap, Vector3 position)
{
    float size = 100;

    Vector3 p0 = { +size, 0, +size }; p0 += position;
    Vector3 p1 = { +size, 0, -size }; p1 += position;
    Vector3 p2 = { -size, 0, -size }; p2 += position;
    Vector3 p3 = { -size, 0, +size }; p3 += position;

    BitmapDrawQuad(bitmap, p0, p1, p2, p3);
}
static inline void DrawPlane(Bitmap* bitmap, Vector3 position, float size)
{
    Vector3 p0 = { +size, 0, +size }; p0 += position;
    Vector3 p1 = { +size, 0, -size }; p1 += position;
    Vector3 p2 = { -size, 0, -size }; p2 += position;
    Vector3 p3 = { -size, 0, +size }; p3 += position;

    BitmapDrawQuad(bitmap, p0, p1, p2, p3);
}
static inline void DrawCube(Bitmap* bitmap, Vector3 position)
{
    Vector3 rotation = { 0, 0, 0 };
    Vector3 scale = { 1, 1, 1 };
    BitmapDrawCube(bitmap, position, rotation, scale);
}
static inline void DrawCubeLight(Bitmap* bitmap, Vector3 position)
{
    BitmapDrawCube(bitmap, position, {}, Vector3One()/2);
}
static inline void DrawSpot(Bitmap* bitmap, Vector3 position)
{
    BitmapDrawCube(bitmap, position, {}, Vector3One()/5);
}
static inline void DrawBound(Bitmap* bitmap, vector<Vector3>& vs, Vector3 position)
{
    float maxx;
    float maxy;
    float maxz;
    float minx;
    float miny;
    float minz;

    for (auto& x : vs)
    {
        maxx = MathMax(maxx, x.x);
        maxy = MathMax(maxy, x.y);
        maxz = MathMax(maxz, x.z);
        minx = MathMin(minx, x.x);
        miny = MathMin(miny, x.y);
        minz = MathMin(minz, x.z);
    }

    Vector3 p0 = { minx, miny, minz };
    Vector3 p1 = { minx, miny, maxz };
    Vector3 p2 = { minx, maxy, minz };
    Vector3 p3 = { minx, maxy, maxz };
    Vector3 p4 = { maxx, miny, minz };
    Vector3 p5 = { maxx, miny, maxz };
    Vector3 p6 = { maxx, maxy, minz };
    Vector3 p7 = { maxx, maxy, maxz };

    p0 += position;
    p1 += position;
    p2 += position;
    p3 += position;
    p4 += position;
    p5 += position;
    p6 += position;
    p7 += position;

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
static inline void DrawCamera(Bitmap* bitmap, Camera* camera)
{
    Vector3 position = camera->position;
    Vector3 rotation = { camera->pitch, -camera->yaw, 0 };
    Vector3 scale = Vector3One() / 3;
    BitmapDrawCube(bitmap, position, rotation, scale);
}
static inline void DrawCamera(Bitmap* bitmap, Vector3 pos)
{
    BitmapDrawCube(bitmap, pos, {}, Vector3One() / 3);
}
static inline void DrawChar(Bitmap* bitmap, int x, int y, char c)
{
    #define P(x2, y2) BitmapSetPixel(bitmap, x+x2, y+y2, COLOR_WHITE);

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
static inline void DrawDigit(Bitmap* bitmap, int x, int y, uint32_t value)
{
    switch (value)
    {
        case 0: { DrawChar(bitmap, x, y, '0'); break; };
        case 1: { DrawChar(bitmap, x, y, '1'); break; };
        case 2: { DrawChar(bitmap, x, y, '2'); break; };
        case 3: { DrawChar(bitmap, x, y, '3'); break; };
        case 4: { DrawChar(bitmap, x, y, '4'); break; };
        case 5: { DrawChar(bitmap, x, y, '5'); break; };
        case 6: { DrawChar(bitmap, x, y, '6'); break; };
        case 7: { DrawChar(bitmap, x, y, '7'); break; };
        case 8: { DrawChar(bitmap, x, y, '8'); break; };
        case 9: { DrawChar(bitmap, x, y, '9'); break; };
    }
}
static inline void DrawInt(Bitmap* bitmap, int x, int y, int value)
{
    value = MathClampInt(value, 0, 99);

    DrawDigit(bitmap, 0*4, 0, (uint32_t)(value / 10));
    DrawDigit(bitmap, 1*4, 0, (uint32_t)(value % 10));
}
