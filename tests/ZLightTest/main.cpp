#include "Perf.h"
#include "SysHelper.h"
#include "SysWindow.h"
#include "ZLight.h"

#define DELTA_TIME 0.020f

Camera cam = { 0, 1.70f, 0 };
Vector3 light = { 0, 1, 0 };

void UpdatePlayerCamera(Camera* camera, SysWindow* window, float delta)
{
    auto w = SysWindowKeyDown(window, 'W');
    auto a = SysWindowKeyDown(window, 'A');
    auto s = SysWindowKeyDown(window, 'S');
    auto d = SysWindowKeyDown(window, 'D');
    CameraInputMovePlane(camera, delta, w, a, s, d);

    auto left = SysWindowKeyDownLEFT(window);
    auto up = SysWindowKeyDownUP(window);
    auto down = SysWindowKeyDownDOWN(window);
    auto right = SysWindowKeyDownRIGHT(window);
    CameraInputRotateClamped(camera, delta, left, up, down, right);

    int x, y; SysWindowGetMouseDelta(window, &x, &y);
    CameraRotateClamped(camera, { x*0.01f, y*0.01f });
}

void DrawFunc(Bitmap* bitmap)
{
    // BitmapExtDrawGrid(bitmap);
    BitmapExtDrawPlane(bitmap);
    BitmapExtDrawCube(bitmap, light, {}, { 0.2f, 0.2f, 0.2f });

    for (int x = -10; x < 10; x++)
    for (int z = -10; z < 10; z++)
    {
        float scale = 0.5f;
        BitmapExtDrawCube(bitmap, { (float)x, 0, (float)z }, { (float)x, (float)z, (float)(x+z) }, { scale, scale, scale });
        // BitmapExtDrawCubeWire(bitmap, { (float)x, 0, (float)z }, { (float)x, (float)z, (float)(x+z) }, { scale, scale, scale });
    }
}

int main()
{
    SysHelperCreateEscThread();

    SysWindow* window = SysWindowCreate(1000, 250, 512, 512);
    SysWindowSetFormatBw(window);
    SysWindowShow(window);
    // Bitmap* bitmap = BitmapCreate(128, 128);
    Bitmap* bitmap = BitmapCreate(256, 256);

    while (SysWindowExists(window))
    {
        REC_1
        {
            UpdatePlayerCamera(&cam, window, 4*DELTA_TIME);

            BitmapReset(bitmap);
            BitmapSetView(bitmap, &cam);
            DrawFunc(bitmap);
            LightData1RemoveLight();
            LightData1AddLight(light, 1);
            LightData1UpdateShadows(DrawFunc);
            LightData1ApplyLight(bitmap);

            SysWindowSetPixelsAutoScaleBw1(window, (uint32_t*)bitmap->buffer, bitmap->width, bitmap->height);
        }
        REC_2

        SysWindowUpdate(window);
        SysHelperHaltLoop(20);
    }

    return 0;
}
