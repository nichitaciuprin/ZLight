#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#include <X11/extensions/Xfixes.h>
#include <X11/extensions/XInput2.h>

int main()
{
    int width = 512;
    int height = 512;
    Display* display = XOpenDisplay(NULL);
    int screen = DefaultScreen(display);
    Window windowRoot = DefaultRootWindow(display);
    Visual* visual = DefaultVisual(display, screen);
    int depth = DefaultDepth(display, screen);
    GC gc = DefaultGC(display, screen);
    Window window = XCreateSimpleWindow(display, windowRoot, 500, 500, width, height, 0, 0, 0xffffffff);

    XSelectInput(display, window, KeyPressMask | ResizeRedirectMask);
    XMapWindow(display, window);
    uint32_t* pixels = (uint32_t*)malloc(width * height * sizeof(uint32_t));
    XImage* image = XCreateImage(display, visual, depth, ZPixmap, 0, (char*)pixels, width, height, 32, 0);

    while (true)
    {
        XEvent event;

        while (XPending(display))
        {
            XNextEvent(display, &event);

            switch (event.type)
            {
                case ResizeRequest:
                {
                    XDestroyImage(image);

                    width = event.xresizerequest.width;
                    height = event.xresizerequest.height;

                    pixels = (uint32_t*)malloc(width * height * sizeof(uint32_t));
                    image = XCreateImage(display, visual, depth, ZPixmap, 0, (char*)pixels, width, height, 32, 0);

                    break;
                }
                case KeyPress:
                {
                    if (event.xkey.keycode == 0x09)
                        return 0;
                }
            }
        }

        for (int y = 0; y < height; y++)
        for (int x = 0; x < width;  x++)
            XPutPixel(image, x, y, 0x0000FF00);

        XPutImage(display, window, gc, image, 0, 0, 0, 0, width, height);

        XFlush(display);
    }

    return 0;
}
