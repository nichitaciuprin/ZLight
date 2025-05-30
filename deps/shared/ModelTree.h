#pragma once

#include "BaseMath.h"

struct ModelTree
{
    Vector3 pos;
    float rot;
    float h1;
    float h2;
    float w1;
    float w2;
};

void ModelTreeDraw(Bitmap* bitmap, Vector3 pos, float rot, float h1, float h2, float w1, float w2)
{
    float radius = (h1 + h2) / 2;
    Vector3 center = { pos.x, pos.y + radius, pos.z };
    auto hiden = Hiden(center, radius, bitmap->view, bitmap->far);
    if (hiden) return;

    Vector3 result[13] =
    {
        { -1, -1, -1 },
        { -1, -1,  1 },
        { -1,  1, -1 },
        { -1,  1,  1 },
        {  1, -1, -1 },
        {  1, -1,  1 },
        {  1,  1, -1 },
        {  1,  1,  1 },
        { -1, -1, -1 },
        { -1, -1,  1 },
        {  1, -1,  1 },
        {  1, -1, -1 },
        {  0,  1,  0 },
    };

    int treeIndeces[16*3] =
    {
         2,  6,  4,
         4,  0,  2,
         6,  7,  5,
         5,  4,  6,
         7,  3,  1,
         1,  5,  7,
         3,  2,  0,
         0,  1,  3,
         1,  0,  4,
         4,  5,  1,
         3,  7,  6,
         6,  2,  3,
        12,  8,  9,
        12,  9, 10,
        12, 10, 11,
        12, 11,  8,
    };

    for (size_t i = 0; i < 13; i++)
    {
        result[i].y += 1;
        result[i] /= 2;
    }

    for (size_t i = 0; i < 8; i++)
    {
        result[i].x *= w1;
        result[i].z *= w1;
        result[i].y *= h1;
    }

    for (size_t i = 8; i < 13; i++)
    {
        result[i].x *= w2;
        result[i].z *= w2;
        result[i].y *= h2;

        result[i].y += h1;
    }

    for (size_t i = 0; i < 13; i++)
        result[i] = Vector3RotateY(result[i], rot);

    for (size_t i = 0; i < 13; i++)
        result[i] += pos;

    for (size_t i = 0; i < 8; i++)
    {
        int i0 = treeIndeces[i*3+0];
        int i1 = treeIndeces[i*3+1];
        int i2 = treeIndeces[i*3+2];

        Vector3 p0 = result[i0];
        Vector3 p1 = result[i1];
        Vector3 p2 = result[i2];

        BitmapDrawTriangle(bitmap, p0, p1, p2);
    }

    for (size_t i = 12; i < 16; i++)
    {
        int i0 = treeIndeces[i*3+0];
        int i1 = treeIndeces[i*3+1];
        int i2 = treeIndeces[i*3+2];

        Vector3 p0 = result[i0];
        Vector3 p1 = result[i1];
        Vector3 p2 = result[i2];

        BitmapDrawTriangle(bitmap, p0, p1, p2);
    }
}

void ModelTreeDraw(Bitmap* bitmap, ModelTree& modelTree)
{
    ModelTreeDraw(bitmap, modelTree.pos, modelTree.rot, modelTree.h1, modelTree.h2, modelTree.w1, modelTree.w2);
}
void ModelTreePush(Vector3& point, ModelTree& modelTree)
{
    PushOutCylinder(&point, modelTree.pos, 10, 1);
}

void ModelTreeDrawTest(Bitmap* bitmap)
{
    // tree0 = TreeGen(2.0f, 0.80f, MATH_PI_DIV_2*(1.0f/6.0f*0));
    // tree1 = TreeGen(2.5f, 0.90f, MATH_PI_DIV_2*(1.0f/6.0f*1));
    // tree2 = TreeGen(3.0f, 1.00f, MATH_PI_DIV_2*(1.0f/6.0f*2));
    // tree3 = TreeGen(2.0f, 0.80f, MATH_PI_DIV_2*(1.0f/6.0f*3));
    // tree4 = TreeGen(2.5f, 0.90f, MATH_PI_DIV_2*(1.0f/6.0f*4));
    // tree5 = TreeGen(3.0f, 1.00f, MATH_PI_DIV_2*(1.0f/6.0f*5));

    int i = 0;

    int max = 2;
    int maxmin1 = max-1;

    for (int i0 = 0; i0 < max; i0++)
    for (int i1 = 0; i1 < max; i1++)
    for (int i2 = 0; i2 < max; i2++)
    for (int i3 = 0; i3 < max; i3++)
    {
        float t0 = i0 / maxmin1;
        float t1 = i1 / maxmin1;
        float t2 = i2 / maxmin1;
        float t3 = i3 / maxmin1;

        // float h1 = 1.0f;
        // float h2 = 3.0f;
        // float w1 = 0.5f;
        // float w2 = 1.5f;

        // float h1 = MathLerp(0.7f, 1.3f, t1);
        // float h2 = MathLerp(2.0f, 6.0f, t0);
        // float w1 = MathLerp(0.4f, 0.6f, t2);
        // float w2 = MathLerp(1.0f, 2.0f, t3);

        float h1 = MathLerp(0.7f, 1.1f, t1);
        float h2 = MathLerp(2.5f, 6.0f, t0);
        float w1 = MathLerp(0.4f, 0.5f, t2);
        float w2 = MathLerp(1.0f, 1.5f, t3);

        Vector3 position = { (float)i*2, 0, 2 };

        ModelTreeDraw(bitmap, position, i, h1, h2, w1, w2);

        i++;
    }
}
