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
    x += 10; if (x < 0 || x >= UNIT) return;
    y += 10; if (y < 0 || y >= UNIT) return;
    z += 10; if (z < 0 || z >= UNIT) return;
    voxels[x][y][z] = value;
}
uint8_t GetVoxel(int x, int y, int z)
{
    x += 10; if (x < 0 || x >= UNIT) return 1;
    y += 10; if (y < 0 || y >= UNIT) return 1;
    z += 10; if (z < 0 || z >= UNIT) return 1;
    return voxels[x][y][z];
    // return 0;
}
bool VoxelExists(int x, int y, int z)
{
    return GetVoxel(x, y, z) != 0;
}
void InitVoxels()
{
    // for (int z = 0; z < UNIT; z++)
    // for (int y = 0; y < UNIT; y++)
    // for (int x = 0; x < UNIT; x++)
    // {
    //     voxels[x][y][z] = 0;
    // }

    for (int z = 0; z < UNIT; z++)
    for (int y = 0; y < UNIT; y++)
    for (int x = 0; x < UNIT; x++)
        voxels[x][y][z] = Subgen1FractionUnsigned() < 0.95f ? 0 : 1;

    for (int z = -1; z <= 1; z++)
    for (int y = -1; y <= 1; y++)
    for (int x = -1; x <= 1; x++)
        SetVoxel(x, y, z, 0);

    SetVoxel(0, 2, 0, 2);
    SetVoxel(0, 3, 0, 0);
}

bool Intersects(Vector3 p0, Vector3 p1)
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

    float ox = p0.x <= p1.x ? 1.0f - (p0.x - floorf(p0.x)) : p0.x - floorf(p0.x);
    float oy = p0.y <= p1.y ? 1.0f - (p0.y - floorf(p0.y)) : p0.y - floorf(p0.y);
    float oz = p0.z <= p1.z ? 1.0f - (p0.z - floorf(p0.z)) : p0.z - floorf(p0.z);

    float tx = dx*ox;
    float ty = dy*oy;
    float tz = dz*oz;

    for (int i = 0; i < 99; i++)
    {
        if (length < tx && length < ty && length < tz) break;

        if (VoxelExists(ix, iy, iz)) return true;

        int state;

        if (tx < ty) { if (tx < tz) { state = 0; } else { state = 2; } }
        else         { if (ty < tz) { state = 1; } else { state = 2; } }

        switch (state)
        {
            case 0: { ix += sx; tx += dx; break; }
            case 1: { iy += sy; ty += dy; break; }
            case 2: { iz += sz; tz += dz; break; }
        }
    }

    if (VoxelExists(ix, iy, iz)) return true;

    return false;
}
bool Trace(Vector3 p0, Vector3 p1, Vector3& pos, float& dist, int& vox)
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

    float ox = p0.x <= p1.x ? 1.0f - (p0.x - floorf(p0.x)) : p0.x - floorf(p0.x);
    float oy = p0.y <= p1.y ? 1.0f - (p0.y - floorf(p0.y)) : p0.y - floorf(p0.y);
    float oz = p0.z <= p1.z ? 1.0f - (p0.z - floorf(p0.z)) : p0.z - floorf(p0.z);

    float tx = dx*ox;
    float ty = dy*oy;
    float tz = dz*oz;

    // DrawSquare(bitmap, ix, iy);

    for (int i = 0; i < 99; i++)
    {
        if (length < tx && length < ty && length < tz) break;

        int state;

        if (tx < ty) { if (tx < tz) { state = 0; } else { state = 2; } }
        else         { if (ty < tz) { state = 1; } else { state = 2; } }

        switch (state)
        {
            case 0:
            {
                ix += sx;
                vox = GetVoxel(ix, iy, iz);
                if (vox != 0)
                {
                    pos = Vector3Add(p0, Vector3Mul(dir, tx));
                    dist = tx;
                    return true;
                }
                tx += dx;
                break;
            }
            case 1:
            {
                iy += sy;
                vox = GetVoxel(ix, iy, iz);
                if (vox != 0)
                {
                    pos = Vector3Add(p0, Vector3Mul(dir, ty));
                    dist = ty;
                    return true;
                }
                ty += dy;
                break;
            }
            case 2:
            {
                iz += sz;
                vox = GetVoxel(ix, iy, iz);
                if (vox != 0)
                {
                    pos = Vector3Add(p0, Vector3Mul(dir, tz));
                    dist = tz;
                    return true;
                }
                tz += dz;
                break;
            }
        }

        // DrawSquare(bitmap, ix, iy);
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

    // Vector3 lightPos = camera->pos + CameraGetAxisZ(camera);

    Matrix view = MatrixView1({}, camera->yaw, camera->pitch);

    int w = bitmap->width;
    int h = bitmap->height;

    uint32_t* pixels = (uint32_t*)bitmap->buffer;

    for (int y = 0; y < h; y++)
    for (int x = 0; x < w; x++)
    {
        int i = x + y * bitmap->width;

        pixels[i] = 0;

        Vector3 rd;
        rd = { (float)x, (float)y, 1 };
        rd = ScreenSpaceToNdc(rd, w, h);
        rd = Vector3Normalize(rd);
        rd = view * rd;

        Vector3 p0 = ro;
        Vector3 p1 = ro+rd*100;

        Vector3 pos;
        int vox;
        float dist;
        if (!Trace(p0, p1, pos, dist, vox)) continue;

        if (vox == 2)
        {
            pixels[i] = COLOR_WHITE;
            continue;
        }

        pos = Vector3MoveTowards1(pos, p0, 0.01f);

        if (Intersects(pos, {})) continue;
        // if (Intersects(pos, {1,0,0})) continue;

        // BitmapSetDepth(bitmap, x, y, +0.9);

        float t = Vector3Length(pos) * 0.070f;
        // float t = Vector3LengthSqrt(pos) * 0.070f;
        t = 1 - (t > 1 ? 1 : t);
        pixels[i] = ColorCreateBwFloat(t);
        // pixels[i] = ColorSetLightValueFloat(COLOR_YELLOW, t);
        // pixels[i] = ColorCreateBwFloat(1);

        // Vector3 ndc = WorldToNdc(pos, bitmap->view, bitmap->proj);
        // t = ndc.z;
        // t = MathClamp(t, -1, +1);
        // BitmapSetDepth(bitmap, x, y, t);

        // BitmapSetDepth(bitmap, x, y, +0.9);

        // BitmapDrawVertex(bitmap, pos);
        // BitmapSetDepth(bitmap, x, y, 0);
    }
}

// Camera camera = { 0, 1.70f, -1 };
Camera camera = {};

void Draw(Bitmap* bitmap)
{
    // BitmapExtDrawPlane(bitmap);
    // BitmapExtDrawCube(bitmap, {}, {}, {1,1,1});
    // DrawPlaneInf(&camera, bitmap);
    DrawPlaneInf2(&camera, bitmap);
}

int main()
{
    InitVoxels();

    // Bitmap* bitmap = BitmapCreate(128, 128);
    Bitmap* bitmap = BitmapCreate(256, 256);
    SysWindow* window = SysWindowCreate(1000, 250, 512, 512);
    // SysWindowSetFormatBw(window);
    SysWindowSetFormatRgb(window);
    // SysWindowSetFullscreen(window, true);
    SysWindowShow(window);

    while (SysWindowExists(window))
    {
        // UpdatePlayerCamera(&camera, window);
        UpdatePlayerCameraFree(&camera, window);

        REC_1
        BitmapSetView(bitmap, &camera);
        BitmapReset(bitmap);
        Draw(bitmap);
        // BitmapApplyDepthInvert(bitmap);
        // BitmapApplyDepthAdjustedInvert(bitmap);
        // BitmapApplyDepthAdjusted(bitmap);
        REC_2

        // SysWindowSetPixelsAutoScaleBw1(window, (uint32_t*)bitmap->buffer, bitmap->width, bitmap->height);
        SysWindowSetPixelsAutoScaleRgb1(window, (uint32_t*)bitmap->buffer, bitmap->width, bitmap->height);

        SysWindowUpdate(window);
        SysHelperHaltLoop(20);
    }

    return 0;
}
