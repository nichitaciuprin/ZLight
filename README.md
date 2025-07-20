ZLight is a header only library for 3D graphics.

It's focus is depth, light and shadows.

Writen in C99, from scratch, without graphic API.

Inspired by Raylib.

Used in https://nichitaciuprin.itch.io/frostwhite.

![](.gif)

example
--------
Example uses SysWindow for window and SysHelper for basic loop
```c
#include "SysHelper.h"
#include "SysWindow.h"
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
```

api
--------
```c
// === Core ===
static inline ZlBitmap* ZlBitmapCreate(int width, int height);
static inline void ZlBitmapDestroy(ZlBitmap* bitmap);
static inline void ZlBitmapReset(ZlBitmap* bitmap);
static inline void ZlBitmapSetViewByEuler(ZlBitmap* bitmap, ZlVector3 eye, float x, float y, float z);
static inline void ZlBitmapSetViewByPyr(ZlBitmap* bitmap, ZlVector3 eye, float pitch, float yaw, float roll);
static inline void ZlBitmapSetViewByTarget(ZlBitmap* bitmap, ZlVector3 eye, ZlVector3 target, ZlVector3 up);
static inline void ZlBitmapSetProj(ZlBitmap* bitmap, float near, float far);
static inline void ZlBitmapSetPixel(ZlBitmap* bitmap, int x, int y, uint32_t color);
static inline void ZlBitmapDrawVertex(ZlBitmap* bitmap, ZlVector3 v0);
static inline void ZlBitmapDrawLine(ZlBitmap* bitmap, ZlVector3 v0, ZlVector3 v1);
static inline void ZlBitmapDrawTriangle(ZlBitmap* bitmap, ZlVector3 v0, ZlVector3 v1, ZlVector3 v2);
static inline void ZlBitmapApplyDepth(ZlBitmap* bitmap);
static inline void ZlBitmapApplyDepthInvert(ZlBitmap* bitmap);
static inline void ZlBitmapApplyDepthAdjusted(ZlBitmap* bitmap);
static inline void ZlBitmapApplyDepthAdjustedInvert(ZlBitmap* bitmap);

// === Light and Shadow ===
static inline void ZlLightRemove();
static inline void ZlLightAdd(ZlVector3 pos, float lum);
static inline void ZlLightUpdate(void (*draw)(ZlBitmap* bitmap));
static inline void ZlLightApply(ZlBitmap* bitmap);

// === Extra Draw ===
static inline void ZlBitmapExtDrawGrid(ZlBitmap* bitmap);
static inline void ZlBitmapExtDrawPlane(ZlBitmap* bitmap);
static inline void ZlBitmapExtDrawCube(ZlBitmap* bitmap, ZlVector3 pos, ZlVector3 rot, ZlVector3 scale);
static inline void ZlBitmapExtDrawCubeWire(ZlBitmap* bitmap, ZlVector3 pos, ZlVector3 rot, ZlVector3 scale);
static inline void ZlBitmapExtDrawChar(ZlBitmap* bitmap, int x, int y, char c);

```

how to run
--------
```
Windows
Depends on MinGW version x86_64-14.2.0-release-posix-seh-ucrt-rt_v12-rev1
MSVC is not suported, but should work
How to build and run?
cd tests/Scene1
build
run

Linux
Depends on GCC
How to build and run?
cd tests/Scene1
bash build.bash
bash run.bash
```
