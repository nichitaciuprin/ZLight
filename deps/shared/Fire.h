#pragma once

#include "BaseLang.hpp"
#include "Subgen.h"

// class Particle;
// vector<Particle> particles;

class Particle
{
public:
    static void Create(Camera* camera)
    {
        // auto p1 = particles.data();
        // auto p2 = (char*)particles.data() + sizeof(Particle) * particles.capacity() - 1;
        // CALLONI(1000, { printf("%p -> %p\n", p1, p2); })
        // CALLONI(1000, { printf("%p ->\n", &particles); })

        Particle item;

        item.pos = camera->position;

        item.speed1 = Subgen1Range(5.0f, 5.5f);
        item.speed2 = 0;

        item.timer = Subgen1Range(2.0f, 2.5f);

        float randRot = Subgen1Range(0, MATH_PI_MUL_2);

        auto camx = CameraGetAxisX(camera);
        auto camy = CameraGetAxisY(camera);
        auto camz = CameraGetAxisZ(camera);

        item.pos += camz;
        item.pos += camx / 3;
        item.pos -= camy / 3;

        Vector2 offset = Vector2FromRad(randRot) * Subgen1FractionUnsigned() * 0.05f;

        item.norm = camz;
        item.norm += camx * offset.x;
        item.norm += camy * offset.y;

        particles.push_back(item);
    }
    static void Create(Vector3 pos, Vector3 norm)
    {
        Particle item;

        item.pos = pos;

        item.speed1 = Subgen1Range(5.0f, 5.5f);
        item.speed2 = 0;

        item.timer = Subgen1Range(2.0f, 2.5f);

        float randRot = Subgen1Range(0, MATH_PI_MUL_2);

        float y = -atan2(norm.x, norm.z);
        float x =  atan2(norm.y, norm.z);

        Vector2 offset2 = Vector2FromRad(randRot) * Subgen1FractionUnsigned() * 0.05f;
        Vector3 offset3 = { offset2.x, offset2.y, 0 };

        offset3 = Vector3RotateY(offset3, y);
        offset3 = Vector3RotateX(offset3, x);

        item.norm = norm + offset3;

        particles.push_back(item);
    }
    static void Update(float dt)
    {
        for (auto& x : particles)
        {
            x.speed1 = MathMoveTowards(x.speed1, 0, dt*2.5f);
            x.speed2 = MathMoveTowards(x.speed2, 1, dt*0.4f);

            x.pos += x.norm      * x.speed1 * dt;
            x.pos += Vector3Up() * x.speed2 * dt;

            x.timer -= dt;
        }

        particles.erase(remove_if(particles.begin(), particles.end(), [](Particle& x)
        {
            return x.timer <= 0;
        }),
        particles.end());
    }
    static void Draw(Bitmap* bitmap)
    {
        for (auto& x : particles)
            BitmapDrawVertex(bitmap, x.pos);
    }
private:
    static vector<Particle> particles;

    Vector3 pos;
    Vector3 norm;
    float speed1;
    float speed2;
    float timer;
};
vector<Particle> Particle::particles;

class Particle2
{
public:
    static void Create(Vector3 pos)
    {
        Particle2 item;

        item.speed = 1.0f;
        item.timer = Subgen1Range(40.0f, 45.0f);

        float rand = Subgen1Range(0, MATH_PI_MUL_2);

        Vector2 offset0 = Vector2FromRad(rand);

        Vector2 offset1 = offset0 * 0.30f * Subgen1FractionUnsigned();
        Vector2 offset2 = offset0 * 0.10f * Subgen1FractionUnsigned();

        Vector3 offset3 = { offset1.x, 0, offset1.y };
        Vector3 offset4 = { offset2.x, 0, offset2.y };

        item.pos = pos + offset3;
        item.norm = Vector3Up() + offset4;

        particles.push_back(item);
    }
    static void Update(float dt)
    {
        // CALLON(5, { Particle2::Create({}); })

        for (auto& x : particles)
        {
            x.speed = MathMoveTowards(x.speed, 0, dt*0.025f);
            x.pos += x.norm * x.speed * dt;
            x.timer -= dt;
        }

        particles.erase(remove_if(particles.begin(), particles.end(), [](Particle2& x)
        {
            return x.timer <= 0;
        }),
        particles.end());
    }
    static void Draw(Bitmap* bitmap)
    {
        for (auto& x : particles)
            BitmapDrawVertex(bitmap, x.pos);
    }
private:
    static vector<Particle2> particles;

    Vector3 pos;
    Vector3 norm;
    float speed;
    float timer;
};
vector<Particle2> Particle2::particles;
