#pragma once

#include "BaseLang.hpp"
#include "BaseMath.hpp"
#include "Subgen.h"
#include "BitmapExt.h"

class Spider
{
public:
    Vector2 pos;
    Vector2 target;
    bool attack;

    Spider(Vector2 pos)
    {
        this->pos = pos;
        this->target = GetRandomPos();
    }
    void Update(float dt)
    {
        if (Vector2Distance(pos, target) > 0.1f)
        {
            pos = Vector2MoveTowards1(pos, target, dt*3);
        }
        else
        {
            target = GetRandomPos();
        }
    }
    void Draw(Bitmap* bitmap)
    {
        BitmapDrawSphere(bitmap, { pos.x, 0, pos.y });
    }

private:
    Vector2 GetRandomPos()
    {
        Vector2 randNorm = Vector2FromRad(Subgen1Range(0, MATH_PI_MUL_2));
        float randLength = Subgen1Range(10, 15);
        return randNorm * randLength;
    }
};

namespace SpiderPool
{
    vector<shared_ptr<Spider>> spiders;

    void Init()
    {
        for (int i = 0; i < 3; i++)
            spiders.push_back(make_shared<Spider>(Vector2Zero()));
    }
    void Update(float dt)
    {
        for (auto& i : spiders)
            i->Update(dt);
    }
    void Draw(Bitmap* bitmap)
    {
        for (auto& i : spiders)
            i->Draw(bitmap);
    }
}