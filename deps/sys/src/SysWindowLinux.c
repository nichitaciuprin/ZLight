#include "SysWindow.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/keysym.h>

#include <X11/extensions/Xfixes.h>

typedef struct SysWindow
{
    Display*   display;
    Window     window;
    XImage*    image;
    Atom       wm_delete_window;

    bool       windowClosed;
    int        width;
    int        height;
    uint32_t*  pixels;

    bool keystates_new[256];
    bool keystates_old[256];
}
SysWindow;

SysWindow* SysWindowCreate(int x, int y, int clientWidth, int clientHeight)
{
    SysWindow* instance = (SysWindow*)calloc(1, sizeof(SysWindow));

    instance->width = clientWidth;
    instance->height = clientHeight;

    instance->display = XOpenDisplay(NULL);
    int screen = DefaultScreen(instance->display);
    Window root = DefaultRootWindow(instance->display);
    instance->window = XCreateSimpleWindow(instance->display, root, x, y, instance->width, instance->height, 0, 0, 0xffffffff);
    long mask = KeyPressMask | KeyReleaseMask;
    XSelectInput(instance->display, instance->window, mask);
    XMapWindow(instance->display, instance->window);
    instance->wm_delete_window = XInternAtom(instance->display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(instance->display, instance->window, &instance->wm_delete_window, 1);

    Visual* visual = DefaultVisual(instance->display, screen);
    int depth = DefaultDepth(instance->display, screen);

    instance->pixels = (uint32_t*)malloc(instance->width * instance->height * sizeof(uint32_t));

    instance->image = XCreateImage
    (
        instance->display, visual, depth, ZPixmap, 0,
        (char*)instance->pixels, instance->width, instance->height, 32, 0
    );

    return instance;
}
bool SysWindowExists(SysWindow* instance)
{
    return !instance->windowClosed;
}
void SysWindowDestroy(SysWindow* instance)
{
    if (!SysWindowExists(instance)) return;

    instance->windowClosed = true;
    XDestroyWindow(instance->display, instance->window);
}
void SysWindowUpdate(SysWindow* instance)
{
    if (!SysWindowExists(instance)) return;

    XEvent event;

    while (XPending(instance->display))
    {
        XNextEvent(instance->display, &event);

        switch (event.type)
        {
            case ClientMessage:
            {
                if (event.xclient.data.l[0] == (int64_t)instance->wm_delete_window)
                {
                    instance->windowClosed = true;
                    XDestroyWindow(instance->display, instance->window);
                }
                break;
            }
            case KeyRelease:
            {
                KeyCode keyCode = event.xkey.keycode;
                instance->keystates_new[(int)keyCode] = false;
                break;
            }
            case KeyPress:
            {
                KeyCode keyCode = event.xkey.keycode;
                instance->keystates_new[(int)keyCode] = true;
                // ESC
                if (keyCode == 0x09)
                {
                    instance->windowClosed = true;
                    XDestroyWindow(instance->display, instance->window);
                }
                break;
            }
        }
    }

    if (!instance->windowClosed)
    {
        int screen = DefaultScreen(instance->display);
        GC defaultGc = DefaultGC(instance->display, screen);
        XPutImage(instance->display, instance->window, defaultGc, instance->image, 0, 0, 0, 0, instance->width, instance->height);
    }
}

void SysWindowShow(SysWindow* instance)
{
}
void SysWindowHide(SysWindow* instance)
{
}

int SysWindowGetWidth(SysWindow* instance)
{
    return 0;
}
int SysWindowGetHeight(SysWindow* instance)
{
    return 0;
}

void SysWindowSetFullscreen(SysWindow* instance, bool enable)
{
}

void SysWindowSetName(SysWindow* instance, const char* name)
{
}

void SysWindowSetPixel(SysWindow* instance, int x, int y, uint32_t pixel)
{
    if (!SysWindowExists(instance)) return;
    instance->pixels[x + y * instance->width] = pixel;
}
void SysWindowSetPixelsAutoScale1(SysWindow* instance, uint32_t* pixels, int width, int height)
{
    if (!SysWindowExists(instance)) return;

    int _width = instance->width;
    int _height = instance->height;

    int widthScale = _width / width;
    int heightScale = _height / height;

    int scale =
        widthScale < heightScale ?
        widthScale : heightScale;

    int offsetx = (_width  - scale * width)  / 2;
    int offsety = (_height - scale * height) / 2;

    for (int y = 0; y < height; y++)
    for (int x = 0; x < width;  x++)
    {
        uint32_t pixel = pixels[x + y * width];
        int x2 = x * scale;
        int y2 = y * scale;
        for (int i = 0; i < scale; i++)
        for (int j = 0; j < scale; j++)
        {
            int _x = x2+i+offsetx;
            int _y = y2+j+offsety;
            instance->pixels[_x + _y * _width] = pixel;
        }
    }
}
void SysWindowSetPixelsAutoScale2(SysWindow* instance, uint8_t* pixels, int width, int height)
{
    if (!SysWindowExists(instance)) return;

    int _width = instance->width;
    int _height = instance->height;

    int widthScale = _width / width;
    int heightScale = _height / height;

    int scale =
        widthScale < heightScale ?
        widthScale : heightScale;

    int offsetx = (_width  - scale * width)  / 2;
    int offsety = (_height - scale * height) / 2;

    for (int y = 0; y < height; y++)
    for (int x = 0; x < width;  x++)
    {
        uint8_t pixel = pixels[x + y * width];
        int x2 = x * scale;
        int y2 = y * scale;
        for (int i = 0; i < scale; i++)
        for (int j = 0; j < scale; j++)
        {
            int _x = x2+i+offsetx;
            int _y = y2+j+offsety;
            instance->pixels[_x + _y * _width] = 0x00FFFFFF * ((float)pixel / 255);
        }
    }
}

void SysWindowDrawDebugBorder(SysWindow* instance)
{
}

void SysWindowGetMouseDelta(SysWindow* instance, int* dx, int* dy)
{
    *dx = 0;
    *dy = 0;
}

bool SysWindowKeyDown(SysWindow* instance, char key)
{
    char str[2] = { key, '\0' };
    KeySym keySync = XStringToKeysym((char*)&str);
    KeyCode keyCode = XKeysymToKeycode(instance->display, keySync);
    int index = (int)keyCode;
    return
    instance->keystates_new[index];
}
bool SysWindowKeyPressed(SysWindow* instance, char key)
{
    char str[2] = { key, '\0' };
    KeySym keySync = XStringToKeysym((char*)&str);
    KeyCode keyCode = XKeysymToKeycode(instance->display, keySync);
    int index = (int)keyCode;
    return
    instance->keystates_new[index] == true &&
    instance->keystates_old[index] == false;
}

bool SysWindowKeyDownUP         (SysWindow* instance) { return instance->keystates_new[(int)0x6f]; }
bool SysWindowKeyDownLEFT       (SysWindow* instance) { return instance->keystates_new[(int)0x71]; }
bool SysWindowKeyDownDOWN       (SysWindow* instance) { return instance->keystates_new[(int)0x74]; }
bool SysWindowKeyDownRIGHT      (SysWindow* instance) { return instance->keystates_new[(int)0x72]; }
bool SysWindowKeyDownLBUTTON    (SysWindow* instance) { return false; }
bool SysWindowKeyDownRBUTTON    (SysWindow* instance) { return false; }
bool SysWindowKeyPressedUP      (SysWindow* instance) { return false; }
bool SysWindowKeyPressedLEFT    (SysWindow* instance) { return false; }
bool SysWindowKeyPressedDOWN    (SysWindow* instance) { return false; }
bool SysWindowKeyPressedRIGHT   (SysWindow* instance) { return false; }
bool SysWindowKeyPressedLBUTTON (SysWindow* instance) { return false; }
bool SysWindowKeyPressedRBUTTON (SysWindow* instance) { return false; }