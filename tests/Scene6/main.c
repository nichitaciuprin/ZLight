#include "SysHelper.h"
#include "SysWindow.h"
#include "ZLight.h"

zlvec3 _p0 = { 0, 0, 0 };
zlvec3 _p1 = { 5, 7, 0 };

zlvec3 p0 = {};
zlvec3 p1 = {};

zlvec3 Clamp(zlvec3 v)
{
    v.x = (float)(int)v.x;
    v.y = (float)(int)v.y;
    return v;
}

void DrawGrid(zlbitmap* bitmap)
{
    // for (int x = -10; x < 10; x++)
    // {
    //     zlvec3 p0 = { x+0.5f, -10, 0 };
    //     zlvec3 p1 = { x+0.5f, +10, 0 };
    //     ZlBitmapDrawLine(bitmap, p0, p1);
    // }
    // for (int y = -10; y < 10; y++)
    // {
    //     zlvec3 p0 = { -10, y+0.5f, 0 };
    //     zlvec3 p1 = { +10, y+0.5f, 0 };
    //     ZlBitmapDrawLine(bitmap, p0, p1);
    // }

    for (int x = -10; x < 10; x++)
    {
        zlvec3 p0 = { x, -10, 0 };
        zlvec3 p1 = { x, +10, 0 };
        ZlBitmapDrawLine(bitmap, p0, p1);
    }
    for (int y = -10; y < 10; y++)
    {
        zlvec3 p0 = { -10, y, 0 };
        zlvec3 p1 = { +10, y, 0 };
        ZlBitmapDrawLine(bitmap, p0, p1);
    }
}
void DrawSquare(zlbitmap* bitmap, int x, int y)
{
    zlvec3 p0 = { -0.5f+x, -0.5f+y, 91 };
    zlvec3 p1 = { -0.5f+x, +0.5f+y, 91 };
    zlvec3 p2 = { +0.5f+x, +0.5f+y, 91 };
    zlvec3 p3 = { +0.5f+x, -0.5f+y, 91 };
    ZlBitmapDrawTriangle(bitmap, p0, p1, p2);
    ZlBitmapDrawTriangle(bitmap, p2, p3, p0);
}
void DrawLine(zlbitmap* bitmap)
{
    // p0.x += 0.5f;
    // p0.y += 0.5f;
    // p1.x += 0.5f;
    // p1.y += 0.5f;
    ZlBitmapDrawLine(bitmap, p0, p1);
}
void DrawPoint(zlbitmap* bitmap, zlvec3 p)
{
    zlvec3 p0 = { p.x-0.1f, p.y-0.1f, 0 };
    zlvec3 p1 = { p.x-0.1f, p.y+0.1f, 0 };
    zlvec3 p2 = { p.x+0.1f, p.y+0.1f, 0 };
    zlvec3 p3 = { p.x+0.1f, p.y-0.1f, 0 };
    ZlBitmapDrawTriangle(bitmap, p0, p1, p2);
    ZlBitmapDrawTriangle(bitmap, p2, p3, p0);
}
void DrawCollision(zlbitmap* bitmap)
{
    // test
    // DrawSquare(bitmap, 0, 0);
    // DrawSquare(bitmap, 2, 0);
    // DrawSquare(bitmap, 3, 0);

    float length = _ZlVector3Length(p1);
    zlvec3 dir = _ZlVector3Normalize(p1);

    float dx = fabsf(length / p1.x);
    float dy = fabsf(length / p1.y);

    float tx = dx;
    float ty = dy;

    for (int i = 0; i < 99; i++)
    {
        if (tx < ty)
        {
            if (length < tx) break;
            zlvec3 cp = _ZlVector3Mul(dir, tx);
            DrawPoint(bitmap, cp);
            tx += dx;
        }
        else
        {
            if (length < ty) break;
            zlvec3 cp = _ZlVector3Mul(dir, ty);
            DrawPoint(bitmap, cp);
            ty += dy;
        }
    }
}

void Draw(zlbitmap* bitmap)
{
    DrawGrid(bitmap);
    DrawLine(bitmap);
    DrawCollision(bitmap);
}

int main()
{
    // zlbitmap* bitmap = ZlBitmapCreate(256, 256);
    zlbitmap* bitmap = ZlBitmapCreate(512, 512);
    SysWindow* window = SysWindowCreate(1000, 250, 512, 512);
    SysWindowSetFormatBw(window);
    SysWindowShow(window);
    float time = 0;

    float near = 0.1f;
    float far = 100.0f;
    bitmap->neari = 1.0f / near;
    bitmap->far = far;
    bitmap->proj = _ZlMatrixProjOrthographic(19, 19, near, far);

    // ZlBitmapSetViewByTarget(bitmap, (zlvec3){1, 1, -1}, (zlvec3){}, (zlvec3){0,1,0});

    while (SysWindowExists(window))
    {
        if (SysWindowKeyDownLEFT(window))  _p1.x -= 0.1f;
        if (SysWindowKeyDownRIGHT(window)) _p1.x += 0.1f;
        if (SysWindowKeyDownDOWN(window))  _p1.y -= 0.1f;
        if (SysWindowKeyDownUP(window))    _p1.y += 0.1f;
        p0 = _p0;
        p1 = _p1;
        // p0 = Clamp(_p0);
        // p1 = Clamp(_p1);

        ZlBitmapReset(bitmap);
        Draw(bitmap);
        ZlBitmapApplyDepthAdjustedInvert(bitmap);
        SysWindowSetPixelsAutoScaleBw1(window, (uint32_t*)bitmap->buffer, bitmap->width, bitmap->height);
        SysWindowUpdate(window);
        SysHelperHaltLoop(20);
        time += 0.020f;
    }

    return 0;
}
