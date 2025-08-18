#include "SysHelper.h"
#include "SysWindow.h"
#include "ZLight.h"

zlvec3 light = { 0, 1, 0 };

void Draw(zlbitmap* bitmap)
{
    ZlBitmapExtDrawPlane(bitmap);
    ZlBitmapExtDrawCube(bitmap, light, (zlvec3){}, (zlvec3){ 0.2f, 0.2f, 0.2f });

    for (int x = -10; x < 10; x++)
    for (int z = -10; z < 10; z++)
    {
        zlvec3 pos = { (float)x, 0, (float)z };
        zlvec3 rot = { (float)x, (float)z, (float)(x+z) };
        zlvec3 scale = { 0.5f, 0.5f, 0.5f };
        ZlBitmapExtDrawCube(bitmap, pos, rot, scale);
    }
}

int main()
{
    zlbitmap* bitmap = ZlBitmapCreate(256, 256);
    SysWindow* window = SysWindowCreate(1000, 250, 512, 512);
    SysWindowSetFormatBw(window);
    SysWindowShow(window);
    float time = 0;

    while (SysWindowExists(window))
    {
        ZlBitmapReset(bitmap);
        zlvec3 eye = { sinf(time)*2, sin(time)+2, cosf(time)*4 };
        zlvec3 up = { 0, 1, 0 };
        ZlBitmapSetViewByTarget(bitmap, eye, light, up);
        Draw(bitmap);
        ZlLightRemove();
        ZlLightAdd(light, 1);
        ZlLightUpdate(Draw);
        ZlLightApply(bitmap);
        SysWindowSetPixelsAutoScaleBw1(window, (uint32_t*)bitmap->buffer, bitmap->width, bitmap->height);
        SysWindowUpdate(window);
        SysHelperHaltLoop(20);
        time += 0.020f;
    }

    return 0;
}
