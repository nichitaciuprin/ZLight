#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef short SHORT;
typedef uint64_t SIZE_T;
typedef int WINBOOL;
typedef char CHAR;
typedef const CHAR *LPCSTR,*PCSTR;
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
#define VOID void
#define WINUSERAPI __declspec(dllimport)
#define WINAPI __stdcall
#define LOWORD(l) ((WORD)(((size_t)(l)) & 0xffff))
#define HIWORD(l) ((WORD)((((size_t)(l)) >> 16) & 0xffff))
#define IDC_ARROW (char*)((size_t)((WORD)(32512)))
#define WINBASEAPI __declspec(dllimport)
typedef LRESULT(__stdcall *WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef void* LPVOID;
typedef DWORD *LPDWORD;
typedef DWORD (WINAPI *PTHREAD_START_ROUTINE) (LPVOID lpThreadParameter);
typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;

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
typedef struct _FILETIME
{
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
}
FILETIME,*PFILETIME,*LPFILETIME;
typedef struct _SECURITY_ATTRIBUTES
{
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    WINBOOL bInheritHandle;
}
SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

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

WINBASEAPI UINT      WINAPI timeBeginPeriod(UINT uPeriod);
WINBASEAPI HWND      WINAPI GetConsoleWindow(VOID);
WINBASEAPI WINBOOL   WINAPI GetSystemTimes(LPFILETIME lpIdleTime, LPFILETIME lpKernelTime, LPFILETIME lpUserTime);
WINBASEAPI VOID      WINAPI Sleep(DWORD dwMilliseconds);
WINUSERAPI SHORT     WINAPI GetKeyState(int nVirtKey);
WINBASEAPI HANDLE    WINAPI GetCurrentThread(VOID);
WINBASEAPI HANDLE    WINAPI CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
WINBASEAPI int       WINAPI GetThreadPriority(HANDLE hThread);
WINBASEAPI WINBOOL   WINAPI SetThreadPriority(HANDLE hThread, int nPriority);
