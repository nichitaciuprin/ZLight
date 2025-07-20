#include "SysHelperTemp.h"
#include "SysWindowTemp.h"
#include "ZLight.h"

ZlVector3 light = { 0, 1, 0 };

void Draw(ZlBitmap* bitmap)
{
    ZlBitmapExtDrawPlane(bitmap);
    ZlBitmapExtDrawCube(bitmap, light, {}, { 0.2f, 0.2f, 0.2f });

    for (int x = -10; x < 10; x++)
    for (int z = -10; z < 10; z++)
        ZlBitmapExtDrawCube(bitmap, { (float)x, 0, (float)z }, { (float)x, (float)z, (float)(x+z) }, { 0.5f, 0.5f, 0.5f });
}

int main()
{
    ZlBitmap* bitmap = ZlBitmapCreate(256, 256);
    SysWindow* window = SysWindowCreate(1000, 250, 512, 512);
    SysWindowSetFormatBw(window);
    SysWindowShow(window);
    float time = 0;

    while (SysWindowExists(window))
    {
        ZlBitmapReset(bitmap);
        ZlBitmapSetViewByTarget(bitmap, { sinf(time)*2, sin(time)+2, cosf(time)*4 }, light, { 0, 1, 0 });
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
