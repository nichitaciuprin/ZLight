#include "SysHelper.h"
#include "SysWindow.h"
#include "Bitmap.h"
#include "BitmapExt.h"
#include "Print.h"
#include "Perf.h"

#define DELTA_TIME_MS 20
#define DELTA_TIME DELTA_TIME_MS*0.001f

#include "Subgen.h"
#include "Helper.h"

#define UNIT 20
uint8_t voxels[UNIT][UNIT][UNIT];
void SetVoxel(int x, int y, int z, uint8_t value)
{
    // x += 10; if (x < 0 || x >= UNIT) return;
    // y += 10; if (y < 0 || y >= UNIT) return;
    // z += 10; if (z < 0 || z >= UNIT) return;
    // voxels[x][y][z] = value;
}
uint8_t GetVoxel(int x, int y, int z)
{
    // x += 10; if (x < 0 || x >= UNIT) return 1;
    // y += 10; if (y < 0 || y >= UNIT) return 1;
    // z += 10; if (z < 0 || z >= UNIT) return 1;
    return voxels[x][y][z];
    // return 0;
}
void InitVoxels()
{
    for (int z = 0; z < UNIT; z++)
    for (int y = 0; y < UNIT; y++)
    for (int x = 0; x < UNIT; x++)
    {
        voxels[x][y][z] = 0;
    }
}

bool Trace(Vector3 p0, Vector3 p1, Vector3& pos, float& dist)
{
    Vector3 diff = Vector3Sub(p1, p0);
    float length = Vector3Length(diff);
    Vector3 dir = Vector3Div(diff, length);

    float dx = length / fabsf(diff.x);
    float dy = length / fabsf(diff.y);
    float dz = length / fabsf(diff.z);

    int sx = signbit(diff.x) == 0 ? +1 : -1;
    int sy = signbit(diff.y) == 0 ? +1 : -1;
    int sz = signbit(diff.z) == 0 ? +1 : -1;

    int ix = (int)floorf(p0.x);
    int iy = (int)floorf(p0.y);
    int iz = (int)floorf(p0.z);

    float ox = p0.x < p1.x ? 1.0f - (p0.x - floorf(p0.x)) : p0.x - floorf(p0.x);
    float oy = p0.y < p1.y ? 1.0f - (p0.y - floorf(p0.y)) : p0.y - floorf(p0.y);
    float oz = p0.z < p1.z ? 1.0f - (p0.z - floorf(p0.z)) : p0.z - floorf(p0.z);

    float tx = dx*ox;
    float ty = dy*oy;
    float tz = dz*oz;

    for (int i = 0; i < 99; i++)
    {
        if (length < tx && length < ty) break;

        int state;

        if (tx < ty) { if (tx < tz) { state = 0; } else { state = 2; } }
        else         { if (ty < tz) { state = 1; } else { state = 2; } }

        switch (state)
        {
            case 0: { if (GetVoxel(ix, iy, iz) == 1) { pos = Vector3Add(p0, Vector3Mul(dir, tx)); dist = tx; return true; } tx += dx; ix += sx; break; }
            case 1: { if (GetVoxel(ix, iy, iz) == 1) { pos = Vector3Add(p0, Vector3Mul(dir, ty)); dist = ty; return true; } ty += dy; iy += sy; break; }
            case 2: { if (GetVoxel(ix, iy, iz) == 1) { pos = Vector3Add(p0, Vector3Mul(dir, tz)); dist = tz; return true; } tz += dz; iz += sz; break; }
        }
    }

    return false;
}
bool GetPlanePos(Vector3 ro, Vector3 rd, Vector3& pos, float& dist)
{
    if (rd.y == 0) return false;
    float f = -ro.y / rd.y;
    if (f <= 0) return false;
    float x = ro.x + rd.x * f;
    float z = ro.z + rd.z * f;
    // printf("%f\n", x);
    // printf("float f = %f / %f;\n", ro.y, rd.y);
    // printf("float x = %f + %f * %f;\n", ro.x, rd.x, f);
    pos = { x, 0, z };
    dist = f;
    return true;
}
void DrawPlaneInf(Camera* camera, Bitmap* bitmap)
{
    Vector3 ro = camera->pos;

    Matrix view = MatrixView1({}, camera->yaw, camera->pitch);

    int w = bitmap->width;
    int h = bitmap->height;

    for (int y = 0; y < h; y++)
    for (int x = 0; x < w; x++)
    {
        Vector3 sp = { (float)x, (float)y, 1 };
        Vector3 ndc = ScreenSpaceToNdc(sp, bitmap->width, bitmap->height);
        Vector3 rd = view * Vector3Normalize(ndc);

        Vector3 pos;
        float t;
        if (GetPlanePos(ro, rd, pos, t))
        {
            Vector3 ndc = WorldToNdc(pos, bitmap->view, bitmap->proj);
            t = ndc.z;
            t = MathClamp(t, -1, +1);
            BitmapSetDepth(bitmap, x, y, t);

            // BitmapSetDepth(bitmap, x, y, +0.9);

            // BitmapDrawVertex(bitmap, pos);
        }
    }
}
void DrawPlaneInf2(Camera* camera, Bitmap* bitmap)
{
    Vector3 ro = camera->pos;

    Matrix view = MatrixView1({}, camera->yaw, camera->pitch);

    int w = bitmap->width;
    int h = bitmap->height;

    for (int y = 0; y < h; y++)
    for (int x = 0; x < w; x++)
    {
        // BitmapSetDepth(bitmap, x, y, 0);

        Vector3 sp = { (float)x, (float)y, 1 };
        Vector3 ndc = ScreenSpaceToNdc(sp, bitmap->width, bitmap->height);
        Vector3 rd = view * Vector3Normalize(ndc);

        Vector3 p0 = ro;
        Vector3 p1 = ro+rd*10;

        Vector3 pos;
        float t;
        if (Trace(p0, p1, pos, t))
        {
            Vector3 ndc = WorldToNdc(pos, bitmap->view, bitmap->proj);
            t = ndc.z;
            t = MathClamp(t, -1, +1);
            BitmapSetDepth(bitmap, x, y, t);

            // BitmapSetDepth(bitmap, x, y, +0.9);

            // BitmapDrawVertex(bitmap, pos);
            // BitmapSetDepth(bitmap, x, y, 0);
        }
    }
}

Camera camera = { 0, 1.70f, -1 };

void Draw(Bitmap* bitmap)
{
    // BitmapExtDrawPlane(bitmap);
    BitmapExtDrawCube(bitmap, {}, {}, {1,1,1});
    // DrawPlaneInf(&camera, bitmap);
    DrawPlaneInf2(&camera, bitmap);
}

int main()
{
    InitVoxels();

    Bitmap* bitmap = BitmapCreate(512, 512);
    SysWindow* window = SysWindowCreate(1000, 250, 512, 512);
    SysWindowSetFormatBw(window);
    SysWindowSetFullscreen(window, true);
    SysWindowShow(window);

    while (SysWindowExists(window))
    {
        UpdatePlayerCamera(&camera, window);

        REC_1
        BitmapSetView(bitmap, &camera);
        BitmapReset(bitmap);
        Draw(bitmap);
        BitmapApplyDepthAdjustedInvert(bitmap);
        REC_2

        SysWindowSetPixelsAutoScaleBw1(window, (uint32_t*)bitmap->buffer, bitmap->width, bitmap->height);

        SysWindowUpdate(window);
        SysHelperHaltLoop(20);
    }

    return 0;
}
