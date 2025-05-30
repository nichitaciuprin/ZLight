#pragma once

#include "BaseMath.hpp"
#include "Subgen.h"
#include "ModelTree.h"

namespace ModelForest
{
    ModelTree treeModels[20*20]; int treeModelsc = 0;

    STATIC_INIT
    void Init()
    {
        auto subgen = SubgenCreate(0);

        int count = 20;

        for (int x = 0; x < count; x++)
        for (int z = 0; z < count; z++)
        {
            Vector3 position = { (float)x, 0, (float)z };

            position.x += SubgenRange(&subgen, -0.40f, +0.40f);
            position.z += SubgenRange(&subgen, -0.40f, +0.40f);

            position.x -= count * 0.5f;
            position.z -= count * 0.5f;

            position.x *= 3;
            position.z *= 3;

            float distSqr = Vector2Length({ position.x, position.z });
            if (distSqr < 4) continue;

            // eyeballing circle in center
            position.x -= 0.97;
            position.z += 1.14;

            // removing 2 tree near player spawn
            float dist = Vector3DistanceSquared(position, { 6.0f, 0, 7.0f });
            if (dist < 1.0f*1.0f)
                continue;

            ModelTree model;
            model.pos = position;
            model.rot = (float)(x + z);
            model.h1 = SubgenRange(&subgen, 0.7f, 1.1f);
            model.h2 = SubgenRange(&subgen, 2.5f, 6.0f);
            model.w1 = SubgenRange(&subgen, 0.4f, 0.5f);
            model.w2 = SubgenRange(&subgen, 1.0f, 1.5f);

            treeModels[treeModelsc] = model;
            treeModelsc++;
        }
    }
    void Draw(Bitmap* bitmap)
    {
        for (int i = 0; i < treeModelsc; i++)
        {
            auto& x = treeModels[i];
            ModelTreeDraw(bitmap, x.pos, x.rot, x.h1, x.h2, x.w1, x.w2);
        }
    }
    void Push(Vector3& point)
    {
        for (int i = 0; i < treeModelsc; i++)
        {
            auto& x = treeModels[i];
            ModelTreePush(point, x);
        }
    }
}
