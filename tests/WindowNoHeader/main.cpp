#include "SysWindowWin.h"

void Draw(SysWindow* window, int width, int height)
{
    static int iteration = 0;
    iteration++;

    for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
        uint32_t a = 0;
        uint32_t r = (uint8_t)(iteration / 9);
        uint32_t g = (uint8_t)(iteration / 6);
        uint32_t b = (uint8_t)(iteration / 3);

        uint32_t pixel =
            (a << (8 * 3)) +
            (r << (8 * 2)) +
            (g << (8 * 1)) +
            (b << (8 * 0));

        SysWindowSetPixelRgb(window, x, y, pixel);
    }
}

int main()
{
    int size = 512;

    SysWindow* window = SysWindowCreate(0, 0, size, size);
    SysWindowSetFormatRgb(window);
    SysWindowShow(window);

    while (SysWindowExists(window))
    {
        Draw(window, size, size);
        SysWindowUpdate(window);
    }

    SysWindowDestroy(window);

    return 0;
}
