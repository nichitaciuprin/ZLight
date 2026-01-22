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

void DrawCollision(Bitmap* bitmap, Vector3 p0, Vector3 p1)
{
    // Vector3 diff = Vector3Sub(p1, p0);
    // float length = Vector3Length(diff);
    // Vector3 dir = Vector3Div(diff, length);

    // float dx = length / fabsf(diff.x);
    // float dy = length / fabsf(diff.y);

    // float ox = p0.x < p1.x ? 1.0f - (p0.x - floorf(p0.x)) : p0.x - floorf(p0.x);
    // float oy = p0.y < p1.y ? 1.0f - (p0.y - floorf(p0.y)) : p0.y - floorf(p0.y);

    // float tx = dx*ox;
    // float ty = dy*oy;

    // // TODO maybe calc loop count
    // for (int i = 0; i < 99; i++)
    // {
    //     if (length < tx && length < ty) break;

    //     if (tx < ty)
    //     {
    //         Vector3 cp = Vector3Add(p0, Vector3Mul(dir, tx));
    //         DrawPoint(bitmap, cp);
    //         tx += dx;
    //     }
    //     else
    //     {
    //         Vector3 cp = Vector3Add(p0, Vector3Mul(dir, ty));
    //         DrawPoint(bitmap, cp);
    //         ty += dy;
    //     }
    // }
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

Camera camera = { 0, 1.70f, -1 };

void Draw(Bitmap* bitmap)
{
    // BitmapExtDrawPlane(bitmap);
    BitmapExtDrawCube(bitmap, {}, {}, {1,1,1});
    DrawPlaneInf(&camera, bitmap);
}

int main()
{
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
