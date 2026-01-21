#include "SysHelper.h"
#include "SysWindow.h"
#include "ZLight.h"

zlvec3 target = {};

void DrawGrid(zlbitmap* bitmap)
{
    for (int x = -10; x < 10; x++)
    {
        zlvec3 p0 = { x+0.5f, -10, 0 };
        zlvec3 p1 = { x+0.5f, +10, 0 };
        ZlBitmapDrawLine(bitmap, p0, p1);
    }
    for (int y = -10; y < 10; y++)
    {
        zlvec3 p0 = { -10, y+0.5f, 0 };
        zlvec3 p1 = { +10, y+0.5f, 0 };
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
    ZlBitmapDrawLine(bitmap, (zlvec3){}, target);
}
void DrawCollision(zlbitmap* bitmap)
{
    // test
    DrawSquare(bitmap, 0, 0);
    DrawSquare(bitmap, 2, 0);
    DrawSquare(bitmap, 3, 0);
}

void Draw(zlbitmap* bitmap)
{
    DrawGrid(bitmap);
    DrawLine(bitmap);
    DrawCollision(bitmap);
}

int main()
{
    zlbitmap* bitmap = ZlBitmapCreate(256, 256);
    SysWindow* window = SysWindowCreate(1000, 250, 512, 512);
    SysWindowSetFormatBw(window);
    SysWindowShow(window);
    float time = 0;

    float near = 0.1f;
    float far = 100.0f;
    bitmap->neari = 1.0f / near;
    bitmap->far = far;
    bitmap->proj = _ZlMatrixProjOrthographic(19, 19, near, far);

    while (SysWindowExists(window))
    {
        if (SysWindowKeyDownLEFT(window))  target.x -= 0.05f;
        if (SysWindowKeyDownRIGHT(window)) target.x += 0.05f;
        if (SysWindowKeyDownDOWN(window))  target.y -= 0.05f;
        if (SysWindowKeyDownUP(window))    target.y += 0.05f;

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
