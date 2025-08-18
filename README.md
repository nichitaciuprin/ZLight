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
```

api
--------
```c
// === Core ===
static inline zlbitmap* ZlBitmapCreate(int width, int height);
static inline void ZlBitmapDestroy(zlbitmap* bitmap);
static inline void ZlBitmapReset(zlbitmap* bitmap);
static inline void ZlBitmapSetViewByEuler(zlbitmap* bitmap, zlvec3 eye, float x, float y, float z);
static inline void ZlBitmapSetViewByPyr(zlbitmap* bitmap, zlvec3 eye, float pitch, float yaw, float roll);
static inline void ZlBitmapSetViewByTarget(zlbitmap* bitmap, zlvec3 eye, zlvec3 target, zlvec3 up);
static inline void ZlBitmapSetProj(zlbitmap* bitmap, float near, float far);
static inline void ZlBitmapSetPixel(zlbitmap* bitmap, int x, int y, uint32_t color);
static inline void ZlBitmapDrawVertex(zlbitmap* bitmap, zlvec3 v0);
static inline void ZlBitmapDrawLine(zlbitmap* bitmap, zlvec3 v0, zlvec3 v1);
static inline void ZlBitmapDrawTriangle(zlbitmap* bitmap, zlvec3 v0, zlvec3 v1, zlvec3 v2);
static inline void ZlBitmapApplyDepth(zlbitmap* bitmap);
static inline void ZlBitmapApplyDepthInvert(zlbitmap* bitmap);
static inline void ZlBitmapApplyDepthAdjusted(zlbitmap* bitmap);
static inline void ZlBitmapApplyDepthAdjustedInvert(zlbitmap* bitmap);

// === Light and Shadow ===
static inline void ZlLightRemove();
static inline void ZlLightAdd(zlvec3 pos, float lum);
static inline void ZlLightUpdate(void (*draw)(zlbitmap* bitmap));
static inline void ZlLightApply(zlbitmap* bitmap);

// === Extra Draw ===
static inline void ZlBitmapExtDrawGrid(zlbitmap* bitmap);
static inline void ZlBitmapExtDrawPlane(zlbitmap* bitmap);
static inline void ZlBitmapExtDrawCube(zlbitmap* bitmap, zlvec3 pos, zlvec3 rot, zlvec3 scale);
static inline void ZlBitmapExtDrawCubeWire(zlbitmap* bitmap, zlvec3 pos, zlvec3 rot, zlvec3 scale);
static inline void ZlBitmapExtDrawChar(zlbitmap* bitmap, int x, int y, char c);
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
