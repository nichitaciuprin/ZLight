#pragma once

#include "BaseLang.hpp"
#include "Subgen.h"

class Snow
{
public:
    static void Create()
    {
        float size = 20;

        float x = Subgen1Range(-size, size);
        float z = Subgen1Range(-size, size);

        Vector3 pos = { x, 20, z };

        particles.push_back(pos);
    }
    static void Update()
    {
        CALLON(2, { Create(); })

        for (auto& x : particles)
        {
            x.y -= DELTA_TIME * 1.5f;

            if (x.y <= 0.3f)
                x.y = -1;
        }

        particles.erase(remove_if(particles.begin(), particles.end(), [](Vector3& x)
        {
            return x.y <= 0;
        }),
        particles.end());
    }
    static void Draw(Bitmap* bitmap)
    {
        for (auto& x : particles)
            BitmapDrawVertex(bitmap, x);
    }
private:
    static vector<Vector3> particles;
};
vector<Vector3> Snow::particles;
