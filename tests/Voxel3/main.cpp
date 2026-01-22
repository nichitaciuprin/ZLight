#include "SysHelper.h"
#include "SysWindow.h"
#include "Bitmap.h"

Vector3 _p0 = { 0, 0, 0 };
Vector3 _p1 = { 5, 7, 0 };

Vector3 p0 = {};
Vector3 p1 = {};

#define UNIT 20
uint8_t voxels[UNIT][UNIT];
void SetVoxel(int x, int y, uint8_t value)
{
    x += 10; if (x < 0 || x >= UNIT) return;
    y += 10; if (y < 0 || y >= UNIT) return;
    voxels[x][y] = value;
}
uint8_t GetVoxel(int x, int y)
{
    x += 10; if (x < 0 || x >= UNIT) return 1;
    y += 10; if (y < 0 || y >= UNIT) return 1;
    return voxels[x][y];
}
void InitVoxels()
{
    for (int x = 0; x < UNIT; x++)
    for (int y = 0; y < UNIT; y++)
    {
        voxels[x][y] = 0;
    }

    SetVoxel(0, 5, 1);
    SetVoxel(1, 5, 1);
    SetVoxel(2, 5, 1);
    SetVoxel(3, 5, 1);
}

Vector3 Clamp(Vector3 v)
{
    v.x = (float)(int)v.x;
    v.y = (float)(int)v.y;
    return v;
}

bool Trace(Vector3 p0, Vector3 p1, Vector3& pos, float dist)
{
    Vector3 diff = Vector3Sub(p1, p0);
    float length = Vector3Length(diff);
    Vector3 dir = Vector3Div(diff, length);

    float dx = length / fabsf(diff.x);
    float dy = length / fabsf(diff.y);

    int sx = signbit(diff.x) == 0 ? +1 : -1;
    int sy = signbit(diff.y) == 0 ? +1 : -1;

    int ix = (int)floorf(p0.x);
    int iy = (int)floorf(p0.y);

    float ox = p0.x < p1.x ? 1.0f - (p0.x - floorf(p0.x)) : p0.x - floorf(p0.x);
    float oy = p0.y < p1.y ? 1.0f - (p0.y - floorf(p0.y)) : p0.y - floorf(p0.y);

    float tx = dx*ox;
    float ty = dy*oy;

    for (int i = 0; i < 99; i++)
    {
        if (length < tx && length < ty) break;

        int state;

        if (tx < ty) { state = 0; }
        else         { state = 1; }

        switch (state)
        {
            case 0: { if (GetVoxel(ix, iy) == 1) { pos = Vector3Add(p0, Vector3Mul(dir, tx)); dist = tx; return true; } tx += dx; ix += sx; break; }
            case 1: { if (GetVoxel(ix, iy) == 1) { pos = Vector3Add(p0, Vector3Mul(dir, ty)); dist = ty; return true; } ty += dy; iy += sy; break; }
        }
    }

    return false;
}

void DrawGrid(Bitmap* bitmap)
{
    // for (int x = -10; x < 10; x++)
    // {
    //     Vector3 p0 = { x+0.5f, -10, 0 };
    //     Vector3 p1 = { x+0.5f, +10, 0 };
    //     BitmapDrawLine(bitmap, p0, p1);
    // }
    // for (int y = -10; y < 10; y++)
    // {
    //     Vector3 p0 = { -10, y+0.5f, 0 };
    //     Vector3 p1 = { +10, y+0.5f, 0 };
    //     BitmapDrawLine(bitmap, p0, p1);
    // }

    for (int x = -10; x < 10; x++)
    {
        Vector3 p0 = { (float)x, -10, 0 };
        Vector3 p1 = { (float)x, +10, 0 };
        BitmapDrawLine(bitmap, p0, p1);
    }
    for (int y = -10; y < 10; y++)
    {
        Vector3 p0 = { -10, (float)y, 0 };
        Vector3 p1 = { +10, (float)y, 0 };
        BitmapDrawLine(bitmap, p0, p1);
    }
}
void DrawSquare(Bitmap* bitmap, int x, int y)
{
    Vector3 p0 = { -0.5f+x+0.5f, -0.5f+y+0.5f, 91 };
    Vector3 p1 = { -0.5f+x+0.5f, +0.5f+y+0.5f, 91 };
    Vector3 p2 = { +0.5f+x+0.5f, +0.5f+y+0.5f, 91 };
    Vector3 p3 = { +0.5f+x+0.5f, -0.5f+y+0.5f, 91 };
    BitmapDrawTriangle(bitmap, p0, p1, p2);
    BitmapDrawTriangle(bitmap, p2, p3, p0);
}
void DrawLine(Bitmap* bitmap)
{
    // p0.x += 0.5f;
    // p0.y += 0.5f;
    // p1.x += 0.5f;
    // p1.y += 0.5f;
    BitmapDrawLine(bitmap, p0, p1);
}
void DrawPoint(Bitmap* bitmap, Vector3 p)
{
    Vector3 p0 = { p.x-0.1f, p.y-0.1f, 0 };
    Vector3 p1 = { p.x-0.1f, p.y+0.1f, 0 };
    Vector3 p2 = { p.x+0.1f, p.y+0.1f, 0 };
    Vector3 p3 = { p.x+0.1f, p.y-0.1f, 0 };
    BitmapDrawTriangle(bitmap, p0, p1, p2);
    BitmapDrawTriangle(bitmap, p2, p3, p0);
}
void DrawCollision(Bitmap* bitmap, Vector3 p0, Vector3 p1)
{
    Vector3 diff = Vector3Sub(p1, p0);
    float length = Vector3Length(diff);
    Vector3 dir = Vector3Div(diff, length);

    float dx = length / fabsf(diff.x);
    float dy = length / fabsf(diff.y);

    float ox = p0.x < p1.x ? 1.0f - (p0.x - floorf(p0.x)) : p0.x - floorf(p0.x);
    float oy = p0.y < p1.y ? 1.0f - (p0.y - floorf(p0.y)) : p0.y - floorf(p0.y);

    float tx = dx*ox;
    float ty = dy*oy;

    // TODO maybe calc loop count
    for (int i = 0; i < 99; i++)
    {
        if (length < tx && length < ty) break;

        if (tx < ty)
        {
            Vector3 cp = Vector3Add(p0, Vector3Mul(dir, tx));
            DrawPoint(bitmap, cp);
            tx += dx;
        }
        else
        {
            Vector3 cp = Vector3Add(p0, Vector3Mul(dir, ty));
            DrawPoint(bitmap, cp);
            ty += dy;
        }
    }
}
void DrawVoxels(Bitmap* bitmap)
{
    for (int x = 0; x < UNIT; x++)
    for (int y = 0; y < UNIT; y++)
    {
        if (voxels[x][y] == 1)
        {
            DrawSquare(bitmap, x-10, y-10);
        }
    }
}
void DrawHit(Bitmap* bitmap, Vector3 p0, Vector3 p1)
{
    Vector3 pos; float dist;
    if (Trace(p0, p1, pos, dist))
    {
        DrawPoint(bitmap, pos);
    }
}


void Draw(Bitmap* bitmap)
{
    DrawGrid(bitmap);
    DrawLine(bitmap);
    DrawVoxels(bitmap);
    // DrawCollision(bitmap, p0, p1);
    DrawHit(bitmap, p0, p1);
}

int main()
{
    InitVoxels();

    Bitmap* bitmap = BitmapCreate(512, 512);
    SysWindow* window = SysWindowCreate(1000, 250, 512, 512);
    SysWindowSetFormatBw(window);
    SysWindowSetFullscreen(window, true);
    SysWindowShow(window);

    float near = 0.1f;
    float far = 100.0f;
    bitmap->neari = 1.0f / near;
    bitmap->far = far;
    bitmap->proj = MatrixProjOrthographic(19, 19, near, far);

    // float time = 0;

    while (SysWindowExists(window))
    {
        // time += 0.020f;

        if (SysWindowKeyDown(window, 'A')) _p0.x -= 0.1f;
        if (SysWindowKeyDown(window, 'D')) _p0.x += 0.1f;
        if (SysWindowKeyDown(window, 'S')) _p0.y -= 0.1f;
        if (SysWindowKeyDown(window, 'W')) _p0.y += 0.1f;
        if (SysWindowKeyDownLEFT(window))  _p1.x -= 0.1f;
        if (SysWindowKeyDownRIGHT(window)) _p1.x += 0.1f;
        if (SysWindowKeyDownDOWN(window))  _p1.y -= 0.1f;
        if (SysWindowKeyDownUP(window))    _p1.y += 0.1f;
        p0 = _p0;
        p1 = _p1;
        // p0 = Clamp(_p0);
        // p1 = Clamp(_p1);
        // p0.x = (float)(int)p0.x;
        // p1.x = (float)(int)p1.x;

        BitmapReset(bitmap);
        // Vector3 eye = { sinf(time)*2, sin(time)+2, cosf(time)*4 };
        // BitmapSetViewByTarget(bitmap, eye, (Vector3){}, (Vector3){0,1,0});
        Draw(bitmap);
        BitmapApplyDepthAdjustedInvert(bitmap);
        SysWindowSetPixelsAutoScaleBw1(window, (uint32_t*)bitmap->buffer, bitmap->width, bitmap->height);
        SysWindowUpdate(window);
        SysHelperHaltLoop(20);
    }

    return 0;
}
