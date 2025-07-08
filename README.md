ZLight is a header only library for 3D graphics.

It's focus is depth, light and shadows.

Writen in C99, from scratch, without graphic API.

Inspired by Raylib.

Used in https://nichitaciuprin.itch.io/frostwhite.

![](.gif)

example
--------
Example uses SysWindow to display bitmap and SysHelper for basic loop
```c
#include "SysHelper.h"
#include "SysWindow.h"
#include "ZLight.h"

Vector3 light = { 0, 1, 0 };

void Draw(Bitmap* bitmap)
{
    ZLightBitmapExtDrawPlane(bitmap);
    ZLightBitmapExtDrawCube(bitmap, light, {}, { 0.2f, 0.2f, 0.2f });

    for (int x = -10; x < 10; x++)
    for (int z = -10; z < 10; z++)
        ZLightBitmapExtDrawCube(bitmap, { (float)x, 0, (float)z }, { (float)x, (float)z, (float)(x+z) }, { 0.5f, 0.5f, 0.5f });
}

int main()
{
    Bitmap* bitmap = ZLightBitmapCreate(256, 256);
    SysWindow* window = SysWindowCreate(1000, 250, 512, 512);
    SysWindowSetFormatBw(window);
    SysWindowShow(window);
    float time = 0;

    while (SysWindowExists(window))
    {
        ZLightBitmapReset(bitmap);
        ZLightBitmapSetViewByTarget(bitmap, { sinf(time)*2, sin(time)+2, cosf(time)*4 }, light, { 0, 1, 0 });
        Draw(bitmap);
        ZLightLightRemove();
        ZLightLightAdd(light, 1);
        ZLightLightUpdate(Draw);
        ZLightLightApply(bitmap);
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
static inline Bitmap* ZLightBitmapCreate(int width, int height);
static inline void ZLightBitmapDestroy(Bitmap* bitmap);
static inline void ZLightBitmapReset(Bitmap* bitmap);
static inline void ZLightBitmapSetViewByEuler(Bitmap* bitmap, Vector3 eye, float x, float y, float z);
static inline void ZLightBitmapSetViewByPyr(Bitmap* bitmap, Vector3 eye, float pitch, float yaw, float roll);
static inline void ZLightBitmapSetViewByTarget(Bitmap* bitmap, Vector3 eye, Vector3 target, Vector3 up);
static inline void ZLightBitmapSetProj(Bitmap* bitmap, float near, float far);
static inline void ZLightBitmapSetPixel(Bitmap* bitmap, int x, int y, uint32_t color);
static inline void ZLightBitmapDrawVertex(Bitmap* bitmap, Vector3 v0);
static inline void ZLightBitmapDrawLine(Bitmap* bitmap, Vector3 v0, Vector3 v1);
static inline void ZLightBitmapDrawTriangle(Bitmap* bitmap, Vector3 v0, Vector3 v1, Vector3 v2);
static inline void ZLightBitmapApplyDepth(Bitmap* bitmap);
static inline void ZLightBitmapApplyDepthInvert(Bitmap* bitmap);
static inline void ZLightBitmapApplyDepthAdjusted(Bitmap* bitmap);
static inline void ZLightBitmapApplyDepthAdjustedInvert(Bitmap* bitmap);

// === Light and Shadow ===
static inline void ZLightLightRemove();
static inline void ZLightLightAdd(Vector3 pos, float lum);
static inline void ZLightLightUpdate(void (*draw)(Bitmap* bitmap));
static inline void ZLightLightApply(Bitmap* bitmap);

// === Extra Draw ===
static inline void ZLightBitmapExtDrawGrid(Bitmap* bitmap);
static inline void ZLightBitmapExtDrawPlane(Bitmap* bitmap);
static inline void ZLightBitmapExtDrawCube(Bitmap* bitmap, Vector3 pos, Vector3 rot, Vector3 scale);
static inline void ZLightBitmapExtDrawCubeWire(Bitmap* bitmap, Vector3 pos, Vector3 rot, Vector3 scale);
static inline void ZLightBitmapExtDrawChar(Bitmap* bitmap, int x, int y, char c);

```

how to run
--------
```
Windows
Depends on MinGW version x86_64-14.2.0-release-posix-seh-ucrt-rt_v12-rev1
MSVC is not suported, but should work
How to build and run?
cd tests/ZLightTest
build
run

Linux
Depends on GCC
How to build and run?
cd tests/ZLightTest
bash build.bash
bash run.bash
```
