#pragma once

#include "BaseMath.hpp"
#include "Subgen.h"
#include "ModelTree.h"

namespace ModelForest
{
    vector<ModelTree> treeModels;

    void Init()
    {
        auto subgen = SubgenCreate(0);

        for (int x = -10; x < 10; x++)
        for (int z =   0; z < 20; z++)
        {
            if (x == 0) continue;

            Vector3 position = { (float)x, 0, (float)z };

            float t1 = 2.0f;
            position.x *= t1;
            position.z *= t1;

            float offset = 1;
            position.x += position.x > 0 ? offset : -offset;

            float t2 = 0.5f;
            position.x += SubgenRange(&subgen, -t2, +t2);
            position.z += SubgenRange(&subgen, -t2, +t2);

            ModelTree model;
            model.pos = position;
            model.rot = (float)(x + z);
            model.h1 = SubgenRange(&subgen, 0.7f, 1.1f);
            model.h2 = SubgenRange(&subgen, 2.5f, 6.0f);
            model.w1 = SubgenRange(&subgen, 0.4f, 0.5f);
            model.w2 = SubgenRange(&subgen, 1.0f, 1.5f);

            treeModels.push_back(model);
        }
    }
    void Draw(Bitmap* bitmap, Vector3 camPos)
    {
        Vector2 v0 = { camPos.x, camPos.z };

        for (auto& model : treeModels)
        {
            Vector2 v1 = { model.pos.x, model.pos.z };
            float dist = Vector2DistanceSqrt(v0, v1);
            if (dist > 200) continue;
            ModelTreeDraw(bitmap, model.pos, model.rot, model.h1, model.h2, model.w1, model.w2);
        }
    }
    void Push(Vector3& point)
    {
        for (auto& x : treeModels)
            ModelTreePush(point, x);
    }

    void DrawTest(Bitmap* bitmap)
    {
        auto subgen = SubgenCreate(0);

        for (int x = -10; x < 10; x++)
        for (int z =   0; z < 20; z++)
        {
            // if (9 <= z && z <= 11) continue;
            // if (x > 10 && z == 10) continue;
            // if (x == -1) continue;
            if (x == 0) continue;

            Vector3 position = { (float)x, 0, (float)z };

            float t1 = 2.0f;
            position.x *= t1;
            position.z *= t1;

            float offset = 1;
            position.x += position.x > 0 ? offset : -offset;

            // float t2 = TEST1;
            float t2 = 0.5f;
            position.x += SubgenRange(&subgen, -t2, +t2);
            position.z += SubgenRange(&subgen, -t2, +t2);

            // int sign = MathSignInt(position.x);
            // position.x = MathClamp(position.x, 1*sign, 100*sign);

            // position.x = position.x > 0 ?
            // MathClamp(position.x, +2, +100) :
            // MathClamp(position.x, -100, -2);

            // position.x = MathClamp(position.x, -100, -1);

            // float distSqr = Vector2Length({ position.x, position.z });
            // if (distSqr < 3) continue;

            ModelTree model;
            model.pos = position;
            model.rot = (float)(x + z);
            model.h1 = SubgenRange(&subgen, 0.7f, 1.1f);
            model.h2 = SubgenRange(&subgen, 2.5f, 6.0f);
            model.w1 = SubgenRange(&subgen, 0.4f, 0.5f);
            model.w2 = SubgenRange(&subgen, 1.0f, 1.5f);

            ModelTreeDraw(bitmap, model);
        }
    }
    void PushTest(Vector3& point)
    {
        auto subgen = SubgenCreate(0);

        for (int x = -10; x < 10; x++)
        for (int z =   0; z < 20; z++)
        {
            if (x == 0) continue;
            // if (x == +1) continue;

            Vector3 position = { (float)x, 0, (float)z };

            float t1 = 2.0f;
            position.x *= t1;
            position.z *= t1;

            float t2 = 0.5f;
            position.x += SubgenRange(&subgen, -t2, +t2);
            position.z += SubgenRange(&subgen, -t2, +t2);

            // float distSqr = Vector2Length({ position.x, position.z });
            // if (distSqr < 3) continue;

            ModelTree model;
            model.pos = position;
            model.rot = (float)(x + z);
            model.h1 = SubgenRange(&subgen, 0.7f, 1.1f);
            model.h2 = SubgenRange(&subgen, 2.5f, 6.0f);
            model.w1 = SubgenRange(&subgen, 0.4f, 0.5f);
            model.w2 = SubgenRange(&subgen, 1.0f, 1.5f);

            ModelTreePush(point, model);
        }
    }
}
