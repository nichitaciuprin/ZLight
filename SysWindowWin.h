#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <memory.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef size_t WPARAM;
typedef int64_t LPARAM;
typedef int64_t LRESULT;
typedef void* HANDLE;
typedef void* HINSTANCE;
typedef void* HMODULE;
typedef void* HWND;
typedef void* HGDIOBJ;
typedef void* HBITMAP;
typedef void* HBRUSH;
typedef void* HDC;
typedef void* HICON;
typedef void* HMENU;
typedef void* HCURSOR;
typedef long long LONG_PTR,*PLONG_PTR;
typedef char CHAR;
typedef const CHAR *LPCSTR,*PCSTR;

#define LOWORD(l) ((WORD)(((size_t)(l)) & 0xffff))
#define HIWORD(l) ((WORD)((((size_t)(l)) >> 16) & 0xffff))
#define IDC_ARROW (char*)((size_t)((WORD)(32512)))

typedef LRESULT(__stdcall *WNDPROC)(HWND, UINT, WPARAM, LPARAM);

typedef struct tagRECT
{
    long left;
    long top;
    long right;
    long bottom;
}
RECT, *PRECT, *NPRECT, *LPRECT;
typedef struct tagPOINT
{
    long x;
    long y;
}
POINT, *PPOINT, *NPPOINT, *LPPOINT;
typedef struct tagRGBQUAD
{
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved;
}
RGBQUAD;
typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize;
    long biWidth;
    long biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    long biXPelsPerMeter;
    long biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
}
BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;
typedef struct tagBITMAPINFO
{
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD bmiColors[1];
}
BITMAPINFO, *LPBITMAPINFO, *PBITMAPINFO;
typedef struct tagWNDCLASSA
{
    UINT style;
    WNDPROC lpfnWndProc;
    int cbClsExtra;
    int cbWndExtra;
    HINSTANCE hInstance;
    HICON hIcon;
    HCURSOR hCursor;
    HBRUSH hbrBackground;
    const char * lpszMenuName;
    const char * lpszClassName;
}
WNDCLASSA, *PWNDCLASSA, *NPWNDCLASSA, *LPWNDCLASSA;
typedef struct tagMSG
{
    HWND hwnd;
    UINT message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD time;
    POINT pt;
}
MSG, *PMSG, *NPMSG, *LPMSG;
typedef struct tagMINMAXINFO
{
    POINT ptReserved;
    POINT ptMaxSize;
    POINT ptMaxPosition;
    POINT ptMinTrackSize;
    POINT ptMaxTrackSize;
}
MINMAXINFO, *PMINMAXINFO, *LPMINMAXINFO;
typedef struct tagPAINTSTRUCT
{
    HDC hdc;
    bool fErase;
    RECT rcPaint;
    bool fRestore;
    bool fIncUpdate;
    BYTE rgbReserved[32];
}
PAINTSTRUCT, *PPAINTSTRUCT, *NPPAINTSTRUCT, *LPPAINTSTRUCT;

#define SRCCOPY (DWORD)0x00CC0020
#define HWND_TOP ((HWND)0)
#define BI_RGB 0l
#define DIB_RGB_COLORS 0
#define VK_ESCAPE 0x1B
#define VK_LEFT 0x25
#define VK_UP 0x26
#define VK_RIGHT 0x27
#define VK_DOWN 0x28
#define VK_RETURN 0x0D
#define VK_LBUTTON 0x01
#define VK_RBUTTON 0x02
#define GWL_STYLE (-16)
#define GWLP_USERDATA (-21)
#define WM_DESTROY 0x0002
#define WM_SIZE 0x0005
#define WM_PAINT 0x000F
#define WM_QUIT 0x0012
#define WM_GETMINMAXINFO 0x0024
#define WM_KEYDOWN 0x0100
#define WM_KEYUP 0x0101
#define WM_SYSKEYDOWN 0x0104
#define WM_SETFOCUS 0x0007
#define WM_KILLFOCUS 0x0008
#define WM_LBUTTONDOWN 0x0201
#define WM_LBUTTONUP 0x0202
#define WM_RBUTTONUP 0x0205
#define WM_RBUTTONDOWN 0x0204
#define WM_RBUTTONUP 0x0205
#define WS_VISIBLE 0x10000000l
#define WS_POPUP 0x80000000l
#define WS_EX_TOPMOST 0x00000008l
#define SWP_NOSIZE 0x0001
#define SWP_NOMOVE 0x0002
#define SWP_NOZORDER 0x0004
#define SWP_NOREDRAW 0x0008
#define SWP_NOACTIVATE 0x0010
#define SWP_FRAMECHANGED 0x0020
#define SWP_SHOWWINDOW 0x0040
#define SWP_HIDEWINDOW 0x0080
#define SWP_NOCOPYBITS 0x0100
#define SWP_NOOWNERZORDER 0x0200
#define SWP_NOSENDCHANGING 0x0400
#define PM_REMOVE 0x0001
#define GWL_EXSTYLE (-20)
#define SW_HIDE 0
#define SW_SHOWNORMAL 1
#define SW_SHOWMAXIMIZED 3

#define WINUSERAPI __declspec(dllimport)
#define WINAPI __stdcall

WINUSERAPI HMODULE   WINAPI GetModuleHandleA(const char* lpModuleName);
WINUSERAPI bool      WINAPI BitBlt(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop);
WINUSERAPI bool      WINAPI DeleteObject(HGDIOBJ ho);
WINUSERAPI HDC       WINAPI CreateCompatibleDC(HDC hdc);
WINUSERAPI HGDIOBJ   WINAPI SelectObject(HDC hdc, HGDIOBJ h);
WINUSERAPI HBITMAP   WINAPI CreateDIBSection(HDC hdc, const BITMAPINFO* lpbmi, UINT usage, void** ppvBits, HANDLE hSection, DWORD offset);
WINUSERAPI LRESULT   WINAPI DispatchMessageA(const MSG *lpMsg);
WINUSERAPI bool      WINAPI PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
WINUSERAPI WORD      WINAPI RegisterClassA(const WNDCLASSA *lpWndClass);
WINUSERAPI LRESULT   WINAPI DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
WINUSERAPI HWND      WINAPI CreateWindowExA(DWORD dwExStyle, const char* lpClassName, const char* lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, void* lpParam);
WINUSERAPI bool      WINAPI DestroyWindow(HWND hWnd);
WINUSERAPI bool      WINAPI CloseWindow(HWND hWnd);
WINUSERAPI bool      WINAPI SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags);
WINUSERAPI bool      WINAPI UpdateWindow(HWND hWnd);
WINUSERAPI bool      WINAPI SetWindowTextA(HWND hWnd,LPCSTR lpString);
WINUSERAPI HDC       WINAPI BeginPaint(HWND hWnd, LPPAINTSTRUCT lpPaint);
WINUSERAPI bool      WINAPI EndPaint(HWND hWnd, const PAINTSTRUCT* lpPaint);
WINUSERAPI bool      WINAPI InvalidateRect(HWND hWnd, const RECT *lpRect, bool bErase);
WINUSERAPI bool      WINAPI AdjustWindowRect(LPRECT lpRect, DWORD dwStyle, bool bMenu);
WINUSERAPI long      WINAPI GetWindowLongA(HWND hWnd, int nIndex);
WINUSERAPI long      WINAPI SetWindowLongA(HWND hWnd, int nIndex, long dwNewLong);
WINUSERAPI int64_t   WINAPI GetWindowLongPtrA(HWND hWnd, int nIndex);
WINUSERAPI int64_t   WINAPI SetWindowLongPtrA(HWND hWnd, int nIndex, int64_t dwNewLong);
WINUSERAPI HCURSOR   WINAPI LoadCursorA(HINSTANCE hInstance, const char * lpCursorName);
WINUSERAPI bool      WINAPI GetWindowRect(HWND hWnd, LPRECT lpRect);
WINUSERAPI LONG_PTR  WINAPI SetWindowLongPtrA(HWND hWnd,int nIndex,LONG_PTR dwNewLong);
WINUSERAPI bool      WINAPI ShowWindow(HWND hWnd, int nCmdShow);
WINUSERAPI int       WINAPI ShowCursor(bool bShow);
WINUSERAPI bool      WINAPI GetCursorPos(LPPOINT lpPoint);
WINUSERAPI bool      WINAPI SetCursorPos(int X,int Y);
WINUSERAPI bool      WINAPI ClipCursor(const RECT *lpRect);
WINUSERAPI HWND      WINAPI GetFocus(void);

// #include <stdint.h>
// #include <assert.h>

// #define WIN32_LEAN_AND_MEAN
// #ifndef NOMINMAX
// #define NOMINMAX
// #endif

// #include <windef.h>
// #include <winuser.h>
// #include <wingdi.h>
// #include <windowsx.h>

typedef struct SysWindow
{
    HWND       hwnd;
    DWORD      style;
    HDC        hdc;
    HBITMAP    hbitmap;
    int        pixelFormat;
    bool       fullScreen;
    bool       visible;
    uint32_t*  pixels;
    int        width;
    int        height;
    int        widthRem;
    int        heightRem;
    int        posX;
    int        posY;

    int mouseX;
    int mouseY;
    int mouseXRem;
    int mouseYRem;
    int mouseDX;
    int mouseDY;

    bool keystates_new[256];
    bool keystates_old[256];
}
SysWindow;

bool _SysWindowRegistered = false;
void _SysWindowBitmapInit(SysWindow* instance)
{
    instance->hdc = CreateCompatibleDC(0);
}
void _SysWindowBitmapResetRgb(SysWindow* instance, int clientWidth, int clientHeight)
{
    instance->width  = clientWidth;
    instance->height = clientHeight;

    BITMAPINFO bitmapinfo = {};
    bitmapinfo.bmiHeader.biSize = sizeof(bitmapinfo.bmiHeader);
    bitmapinfo.bmiHeader.biPlanes = 1;
    bitmapinfo.bmiHeader.biBitCount = 32;
    bitmapinfo.bmiHeader.biCompression = BI_RGB;
    bitmapinfo.bmiHeader.biWidth  = clientWidth;
    bitmapinfo.bmiHeader.biHeight = clientHeight;

    // switches bottom-up to top-down
    bitmapinfo.bmiHeader.biHeight = -bitmapinfo.bmiHeader.biHeight;

    if (instance->hbitmap)
        DeleteObject(instance->hbitmap);

    instance->hbitmap = CreateDIBSection(NULL, &bitmapinfo, DIB_RGB_COLORS, (void**)&instance->pixels, 0, 0);

    assert(instance->hbitmap != 0);

    SelectObject(instance->hdc, instance->hbitmap);
}
void _SysWindowBitmapResetBw(SysWindow* instance, int clientWidth, int clientHeight)
{
    instance->width  = clientWidth;
    instance->height = clientHeight;

    int headerSize = sizeof(BITMAPINFOHEADER);
    int palleteSize = sizeof(RGBQUAD)*256;

    void* data = calloc(1, headerSize+palleteSize);

    BITMAPINFOHEADER* header = (BITMAPINFOHEADER*)data;
    header->biSize = headerSize;
    header->biPlanes = 1;
    header->biBitCount = 8;
    header->biCompression = BI_RGB;
    header->biWidth  = clientWidth;
    header->biHeight = clientHeight;
    // switches bottom-up to top-down
    header->biHeight = -header->biHeight;

    RGBQUAD* pallete = (RGBQUAD*)(((char*)data)+headerSize);
    for (int i = 0; i < 256; i++)
    {
        pallete[i].rgbBlue   = i;
        pallete[i].rgbGreen  = i;
        pallete[i].rgbRed    = i;
    }

    if (instance->hbitmap)
        DeleteObject(instance->hbitmap);

    instance->hbitmap = CreateDIBSection(NULL, (BITMAPINFO*)data, DIB_RGB_COLORS, (void**)&instance->pixels, 0, 0);

    assert(instance->hbitmap != 0);

    SelectObject(instance->hdc, instance->hbitmap);

    free(data);
}
void _SysWindowBitmapReset(SysWindow* instance, int clientWidth, int clientHeight)
{
    if (instance->pixelFormat == 0)
        _SysWindowBitmapResetRgb(instance, clientWidth, clientHeight);
    else
        _SysWindowBitmapResetBw(instance, clientWidth, clientHeight);
}
void _SysWindowBitmapPaint(SysWindow* instance)
{
    PAINTSTRUCT paint;

    HDC device_context = BeginPaint(instance->hwnd, &paint);

    BitBlt(device_context,
            paint.rcPaint.left, paint.rcPaint.top,
            paint.rcPaint.right - paint.rcPaint.left,
            paint.rcPaint.bottom - paint.rcPaint.top,
            instance->hdc,
            paint.rcPaint.left, paint.rcPaint.top,
            SRCCOPY);

    EndPaint(instance->hwnd, &paint);
}
void _SysWindowFullscreenEnable(SysWindow* instance)
{
    HWND hwnd = instance->hwnd;

    RECT rect;
    GetWindowRect(hwnd, &rect);

    instance->posX = rect.left;
    instance->posY = rect.top;
    instance->widthRem = rect.right - rect.left;
    instance->heightRem = rect.bottom - rect.top;

    SetWindowLongPtrA(hwnd, GWL_STYLE, WS_POPUP);
    SetWindowLongPtrA(hwnd, GWL_EXSTYLE, WS_EX_TOPMOST);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

    if (instance->visible)
        ShowWindow(hwnd, SW_SHOWMAXIMIZED);

    instance->fullScreen = true;
}
void _SysWindowFullscreenDisable(SysWindow* instance)
{
    HWND hwnd = instance->hwnd;
    DWORD style = instance->style;

    int posX = instance->posX;
    int posY = instance->posY;
    int width = instance->widthRem;
    int height = instance->heightRem;

    SetWindowLongPtrA(hwnd, GWL_STYLE, style);
    SetWindowLongPtrA(hwnd, GWL_EXSTYLE, 0);
    SetWindowPos(hwnd, HWND_TOP, posX, posY, width, height, SWP_NOZORDER | SWP_FRAMECHANGED);

    if (instance->visible)
        ShowWindow(hwnd, SW_SHOWNORMAL);

    instance->fullScreen = false;
}
void _SysWindowMouseOnFocus(SysWindow* instance)
{
    ShowCursor(false);

    POINT point; GetCursorPos(&point);
    instance->mouseXRem = point.x;
    instance->mouseYRem = point.y;

    RECT rect; GetWindowRect(instance->hwnd, &rect);
    instance->mouseX = (rect.left+rect.right) / 2;
    instance->mouseY = (rect.top+rect.bottom) / 2;

    SetCursorPos(instance->mouseX, instance->mouseY);

    ClipCursor(&rect);
}
void _SysWindowMouseOnUnfocus(SysWindow* instance)
{
    ClipCursor(NULL);

    instance->mouseX = instance->mouseXRem;
    instance->mouseY = instance->mouseYRem;

    SetCursorPos(instance->mouseX, instance->mouseY);

    ShowCursor(true);
}
void _SysWindowMouseOnSize(SysWindow* instance)
{
    ClipCursor(NULL);

    RECT rect; GetWindowRect(instance->hwnd, &rect);
    instance->mouseX = (rect.left+rect.right) / 2;
    instance->mouseY = (rect.top+rect.bottom) / 2;

    SetCursorPos(instance->mouseX, instance->mouseY);

    ClipCursor(&rect);
}
void _SysWindowMouseOnExit(SysWindow* instance)
{
    ClipCursor(NULL);

    instance->mouseX = instance->mouseXRem;
    instance->mouseY = instance->mouseYRem;

    SetCursorPos(instance->mouseX, instance->mouseY);

    ShowCursor(true);
}
void _SysWindowMouseOnUpdate(SysWindow* instance)
{
    bool focused = instance->hwnd == GetFocus();
    if (!focused) return;

    POINT point; GetCursorPos(&point);
    instance->mouseDX = point.x - instance->mouseX;
    instance->mouseDY = point.y - instance->mouseY;

    RECT rect; GetWindowRect(instance->hwnd, &rect);
    instance->mouseX = (rect.left+rect.right) / 2;
    instance->mouseY = (rect.top+rect.bottom) / 2;

    SetCursorPos(instance->mouseX, instance->mouseY);
}

LRESULT __stdcall _SysWindowMessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    SysWindow* instance = (SysWindow*)(GetWindowLongPtrA(hwnd, GWLP_USERDATA));

    if (instance == NULL)
        return DefWindowProcA(hwnd, message, wParam, lParam);

    switch(message)
    {
        case WM_QUIT:
        case WM_DESTROY:
        {
            _SysWindowMouseOnExit(instance);
            instance->hwnd = 0;
            break;
        }
        case WM_PAINT:
        {
            _SysWindowBitmapPaint(instance);
            break;
        }
        case WM_SYSKEYDOWN:
        {
            // alt+enter fullscreen toggle
            int altDown = (lParam & 0x60000000) == 0x20000000;
            int enterDown = wParam == VK_RETURN;
            if (!(altDown && enterDown)) break;

            if (instance->fullScreen)
                _SysWindowFullscreenDisable(instance);
            else
                _SysWindowFullscreenEnable(instance);

            break;
        }
        case WM_SIZE:
        {
            int clientWidth = LOWORD(lParam);
            int clientHeight = HIWORD(lParam);

            bool samew = instance->width == clientWidth;
            bool sameh = instance->height == clientHeight;

            if (samew && sameh) break;

            instance->width = clientWidth;
            instance->height = clientHeight;

            _SysWindowBitmapReset(instance, clientWidth, clientHeight);

            _SysWindowMouseOnSize(instance);

            break;
        }
        case WM_GETMINMAXINFO:
        {
            // Sets windows size defaults
            LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
            lpMMI->ptMinTrackSize.x = 10;
            lpMMI->ptMinTrackSize.y = 10;
            break;
        }
        case WM_SETFOCUS:
        {
            _SysWindowMouseOnFocus(instance);

            break;
        }
        case WM_KILLFOCUS:
        {
            _SysWindowMouseOnUnfocus(instance);
            break;
        }
        case WM_KEYDOWN:
        {
            // TODO remove?
            switch (wParam)
            {
                case VK_ESCAPE:
                    DestroyWindow(hwnd);
                    break;
            }

            instance->keystates_new[(int)wParam] = true;
            break;
        }
        case WM_KEYUP:       { instance->keystates_new[(int)wParam]     = false; break; }
        case WM_LBUTTONDOWN: { instance->keystates_new[(int)VK_LBUTTON] = true;  break; }
        case WM_LBUTTONUP:   { instance->keystates_new[(int)VK_LBUTTON] = false; break; }
        case WM_RBUTTONDOWN: { instance->keystates_new[(int)VK_RBUTTON] = true;  break; }
        case WM_RBUTTONUP:   { instance->keystates_new[(int)VK_RBUTTON] = false; break; }
        default: return DefWindowProcA(hwnd, message, wParam, lParam);
    }

    return 0;
}

SysWindow* SysWindowCreate(int x, int y, int clientWidth, int clientHeight)
{
    SysWindow* instance = (SysWindow*)calloc(1, sizeof(SysWindow));

    HINSTANCE hInstance = GetModuleHandleA(0);

    const char* className = "SysWindowClass";
    const char* windowName = "SysWindow";

    if (!_SysWindowRegistered)
    {
        _SysWindowRegistered = true;
        WNDCLASSA window_class = {};
        window_class.lpfnWndProc = _SysWindowMessageHandler;
        window_class.hInstance = hInstance;
        window_class.lpszClassName = className;
        window_class.hCursor = LoadCursorA(0, IDC_ARROW);
        RegisterClassA(&window_class);
    }

    DWORD style = 0;

    // DWORD style = WS_VISIBLE;

    // Makes default window
    // style += WS_OVERLAPPEDWINDOW;

    instance->style = style;

    RECT rect = { 0, 0, (long)clientWidth, (long)clientHeight };
    AdjustWindowRect(&rect, style, false);

    int windowX = (long)x;
    int windowY = (long)y;
    int windowWidth = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;

    _SysWindowBitmapInit(instance);
    _SysWindowBitmapResetRgb(instance, clientWidth, clientHeight);

    HWND hwnd = CreateWindowExA
    (
        0, className, windowName, 0,
        windowX, windowY, windowWidth, windowHeight,
        NULL, NULL, hInstance, NULL
    );

    assert(hwnd != NULL);

    instance->hwnd = hwnd;

    SetWindowLongPtrA(hwnd, GWLP_USERDATA, (int64_t)(instance));

    SetWindowLongPtrA(hwnd, GWL_STYLE, style);
    SetWindowLongPtrA(hwnd, GWL_EXSTYLE, 0);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    // ShowWindow(hwnd, SW_SHOWNORMAL);
    // ShowWindow(hwnd, SW_HIDE);

    return instance;
}
bool SysWindowExists(SysWindow* instance)
{
    return instance->hwnd != 0;
}
void SysWindowDestroy(SysWindow* instance)
{
    if (!SysWindowExists(instance)) return;
    DestroyWindow(instance->hwnd);
    instance->hwnd = 0;
}
void SysWindowUpdate(SysWindow* instance)
{
    if (!SysWindowExists(instance)) return;

    MSG message = {};

    memcpy(instance->keystates_old, instance->keystates_new, 256);

    _SysWindowMouseOnUpdate(instance);

    while (PeekMessageA(&message, NULL, 0, 0, PM_REMOVE))
        DispatchMessageA(&message);

    InvalidateRect(instance->hwnd, NULL, false);
    UpdateWindow(instance->hwnd);
}

void SysWindowSetFormatRgb(SysWindow* instance)
{
    if (instance->pixelFormat == 0) return;
        instance->pixelFormat = 0;

    _SysWindowBitmapResetRgb(instance, instance->width, instance->height);
}
void SysWindowSetFormatBw(SysWindow* instance)
{
    if (instance->pixelFormat == 1) return;
        instance->pixelFormat = 1;

    _SysWindowBitmapResetBw(instance, instance->width, instance->height);
}

void SysWindowShow(SysWindow* instance)
{
    instance->visible = true;
    ShowWindow(instance->hwnd, instance->fullScreen ? SW_SHOWMAXIMIZED : SW_SHOWNORMAL);
}
void SysWindowHide(SysWindow* instance)
{
    instance->visible = false;
    ShowWindow(instance->hwnd, SW_HIDE);
}
int SysWindowGetWidth(SysWindow* instance)
{
    return instance->width;
}
int SysWindowGetHeight(SysWindow* instance)
{
    return instance->height;
}
void SysWindowSetFullscreen(SysWindow* instance, bool enable)
{
    if (enable)
    {
        if (instance->fullScreen) return;
        _SysWindowFullscreenEnable(instance);
    }
    else
    {
        if (!instance->fullScreen) return;
        _SysWindowFullscreenDisable(instance);
    }
}
void SysWindowSetName(SysWindow* instance, const char* name)
{
    SetWindowTextA(instance->hwnd, name);
}

void SysWindowSetPixelRgb(SysWindow* instance, int x, int y, uint32_t pixel)
{
    if (!SysWindowExists(instance)) return;
    uint32_t* pixels = instance->pixels;
    pixels[x + y * instance->width] = pixel;
}
void SysWindowSetPixelsAutoScaleRgb1(SysWindow* instance, uint32_t* pixels, int width, int height)
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
void SysWindowSetPixelsAutoScaleRgb2(SysWindow* instance, uint8_t* pixels, int width, int height)
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

void SysWindowSetPixelBw(SysWindow* instance, int x, int y, uint8_t pixel)
{
    if (!SysWindowExists(instance)) return;
    uint8_t* pixels = (uint8_t*)instance->pixels;
    pixels[x + y * instance->width] = pixel;
}
void SysWindowSetPixelsAutoScaleBw1(SysWindow* instance, uint32_t* pixels, int width, int height)
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
            // int r = (uint8_t)(pixel >> 8 * 2);
            // int g = (uint8_t)(pixel >> 8 * 1);
            // int b = (uint8_t)(pixel >> 8 * 0);
            // ((uint8_t*)instance->pixels)[_x + _y * _width] = (r + g + b) / 3;
            ((uint8_t*)instance->pixels)[_x + _y * _width] = (uint8_t)(pixel >> 8 * 0);
        }
    }
}
void SysWindowSetPixelsAutoScaleBw2(SysWindow* instance, uint8_t* pixels, int width, int height)
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
            ((uint8_t*)instance->pixels)[_x + _y * _width] = pixel;
        }
    }
}

void SysWindowGetMouseDelta(SysWindow* instance, int* dx, int* dy)
{
    *dx = +instance->mouseDX;
    *dy = -instance->mouseDY;
}

bool SysWindowKeyDown(SysWindow* instance, char key)
{
    return instance->keystates_new[(int)key];
}
bool SysWindowKeyPressed(SysWindow* instance, char key)
{
    return instance->keystates_new[(int)key] == true && instance->keystates_old[(int)key] == false;
}

bool SysWindowKeyDownUP         (SysWindow* instance) { return instance->keystates_new[(int)VK_UP];      }
bool SysWindowKeyDownLEFT       (SysWindow* instance) { return instance->keystates_new[(int)VK_LEFT];    }
bool SysWindowKeyDownDOWN       (SysWindow* instance) { return instance->keystates_new[(int)VK_DOWN];    }
bool SysWindowKeyDownRIGHT      (SysWindow* instance) { return instance->keystates_new[(int)VK_RIGHT];   }
bool SysWindowKeyDownLBUTTON    (SysWindow* instance) { return instance->keystates_new[(int)VK_LBUTTON]; }
bool SysWindowKeyDownRBUTTON    (SysWindow* instance) { return instance->keystates_new[(int)VK_RBUTTON]; }
bool SysWindowKeyPressedUP      (SysWindow* instance) { return instance->keystates_new[(int)VK_UP]      == true && instance->keystates_old[(int)VK_UP]      == false; }
bool SysWindowKeyPressedLEFT    (SysWindow* instance) { return instance->keystates_new[(int)VK_LEFT]    == true && instance->keystates_old[(int)VK_LEFT]    == false; }
bool SysWindowKeyPressedDOWN    (SysWindow* instance) { return instance->keystates_new[(int)VK_DOWN]    == true && instance->keystates_old[(int)VK_DOWN]    == false; }
bool SysWindowKeyPressedRIGHT   (SysWindow* instance) { return instance->keystates_new[(int)VK_RIGHT]   == true && instance->keystates_old[(int)VK_RIGHT]   == false; }
bool SysWindowKeyPressedLBUTTON (SysWindow* instance) { return instance->keystates_new[(int)VK_LBUTTON] == true && instance->keystates_old[(int)VK_LBUTTON] == false; }
bool SysWindowKeyPressedRBUTTON (SysWindow* instance) { return instance->keystates_new[(int)VK_RBUTTON] == true && instance->keystates_old[(int)VK_RBUTTON] == false; }

#ifdef __cplusplus
}
#endif
