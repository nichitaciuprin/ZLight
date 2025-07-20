#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <process.h>
#include <time.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windef.h>
#include <winbase.h>
#include <wingdi.h>
#include <winuser.h>
#include <wincon.h>
#include <timeapi.h>

static FILETIME idleOld = {};
static FILETIME idleNew = {};
static FILETIME userOld = {};
static FILETIME userNew = {};
static int cpu = 0;
static int cpuTimer = 0;

__attribute__((constructor))
void _SysHelperInit()
{
    timeBeginPeriod(1);
}

void SysHelperGetConsolePosition(int* x, int* y)
{
    RECT rect = {};

    HWND handle = GetConsoleWindow();

    // GetClientRect(handle, &rect)
    GetWindowRect(handle, &rect);

    *x = rect.left;
    *y = rect.top;

    // TODO fix this
    *x += 7;
}
int SysHelperGetPid()
{
    // printf("Process PID:%ld\n", (long)getpid());
    return getpid();
}
int SysHelperGetCpuUsage()
{
    // TODO
    if (cpuTimer != 100)
    {
        cpuTimer++;
        return cpu;
    }

    cpuTimer = 0;

    FILETIME kernel = {};

    GetSystemTimes(&idleNew, &kernel, &userNew);

    // cpu = GetCpuUsageDiff(idleOld, idleNew, userOld, userNew);

    DWORD idle = idleNew.dwLowDateTime - idleOld.dwLowDateTime;
    DWORD user = userNew.dwLowDateTime - userOld.dwLowDateTime;
    DWORD all = idle + user;
    cpu = all == 0 ? 0 : user * 100 / all;

    idleOld = idleNew;
    userOld = userNew;

    return cpu;
}
long SysHelperGetTime()
{
    // TODO maybe change to QueryPerformanceCounter
    return clock()/(CLOCKS_PER_SEC/1000);
    // return clock();
}
void SysHelperWait(long milliseconds)
{
    long end = SysHelperGetTime() + milliseconds;
    while (SysHelperGetTime() < end) {}
}
void SysHelperHalt(long milliseconds)
{
    // Sleep always wakes about 10 ms late
    Sleep(milliseconds);
}
void SysHelperWaitLoop(long timestep)
{
    static long start = 0;

    // if wait time 0
    long now = SysHelperGetTime();
    long calcTime = now - start;
    long waitTime = timestep - calcTime;
    if (waitTime <= 0)
    {
        start = now;
        return;
    }

    long end = start + timestep;
    while (SysHelperGetTime() < end) {}
    start = end;
}
void SysHelperHaltLoop(long timestep)
{
    static long start = 0;

    // if wait time 0
    long now = SysHelperGetTime();
    long calcTime = now - start;
    long waitTime = timestep - calcTime;
    if (waitTime <= 0)
    {
        start = now;
        return;
    }

    long end = start + timestep;
    Sleep(waitTime);
    start = end;
}

bool EscThreadCreated = false;
DWORD WINAPI EscThread()
{
    while (!(GetKeyState(VK_ESCAPE) & 0x8000)) { SysHelperHalt(100); };
    printf("EXITED BY ESC THREAD\n");
    exit(0);
    return 0;
}
void SysHelperCreateEscThread()
{
    if (EscThreadCreated) return;
        EscThreadCreated = true;

    CreateThread(NULL, 0, EscThread, NULL, 0, NULL);
}

int SysHelperGetCurentThreadPriority()
{
    return GetThreadPriority(GetCurrentThread());
}
void SysHelperSetCurentThreadPriorityNormal()
{
    SetThreadPriority(GetCurrentThread(), 0);
}
void SysHelperSetCurentThreadPriorityHigh()
{
    SetThreadPriority(GetCurrentThread(), 2);
}
void SysHelperSetCurentThreadPriorityCritical()
{
    SetThreadPriority(GetCurrentThread(), 15);
}
