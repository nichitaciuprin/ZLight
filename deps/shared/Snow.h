#pragma once

#include "BaseLang.hpp"
#include "Subgen.h"
#include "Bitmap.h"

namespace Snow
{
    const int dist = 20;
    const int size = 40;
    const float val1 = size / 2.0f;
    Vector3 points[size][size];
    Subgen subgen = SubgenCreate(0);

    void _Init()
    {
        GUARDX

        for (int z = 0; z < size; z++)
        for (int x = 0; x < size; x++)
        {
            auto& point = points[x][z];

            point.y = SubgenRange(&subgen, 0, 20);

            point.x = (x - val1) / val1 * dist;
            point.z = (z - val1) / val1 * dist;
            point.x += SubgenFractionSigned(&subgen);
            point.z += SubgenFractionSigned(&subgen);
        }
    }
    void Update()
    {
        _Init();

        for (int z = 0; z < size; z++)
        for (int x = 0; x < size; x++)
        {
            auto& point = points[x][z];

            if (point.y <= 0.3f)
            {
                point.y = 20;

                point.x = (x - val1) / val1 * dist;
                point.z = (z - val1) / val1 * dist;
                point.x += SubgenFractionSigned(&subgen);
                point.z += SubgenFractionSigned(&subgen);
            }
            else
            {
                point.y -= 1.5f * DELTA_TIME;
            }
        }
    }
    void Draw(Bitmap* bitmap)
    {
        for (int z = 0; z < size; z++)
        for (int x = 0; x < size; x++)
            BitmapDrawVertex(bitmap, points[x][z]);
    }
}
