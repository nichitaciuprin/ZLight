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
        Subgen subgen = SubgenCreate(8);

        int count = 20;

        for (int x = 0; x < count; x++)
        for (int z = 0; z < count; z++)
        {
            Vector3 position = { (float)x, 0, (float)z };

            // float rad = MATH_PI_MUL_2 * Subgen1FractionSigned();
            // Vector2 offset = Vector2FromRad(rad) * 0.40f;
            position.x += SubgenRange(&subgen, -0.40f, 0.40f);
            position.z += SubgenRange(&subgen, -0.40f, 0.40f);

            position.x -= count / 2;
            position.z -= count;

            position *= 3;

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
