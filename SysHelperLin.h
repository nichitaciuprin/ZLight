#pragma once

// TODO remove std=gnu99 ?
// #define __USE_POSIX199309

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>

static struct timespec initSpec;

// static long clock2()
// {
//     return clock()/(CLOCKS_PER_SEC/1000);
// }

__attribute__((constructor))
void SysHelperInit()
{
    clock_gettime(CLOCK_REALTIME, &initSpec);
}

void SysHelperGetConsolePosition(int* x, int* y)
{
    // #error SysHelperGetConsolePosition not implemented
    *x = 0;
    *y = 0;
}
int SysHelperGetPid()
{
    return getpid();
}
int SysHelperGetCpuUsage()
{
    // #error GetCpuUsage not implemented
    return 100;
}
long SysHelperGetTime()
{
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    unsigned long ms1 = initSpec.tv_sec * 1000 + (double)(int)(initSpec.tv_nsec / 1.0e6);
    unsigned long ms2 =     spec.tv_sec * 1000 + (double)(int)(    spec.tv_nsec / 1.0e6);

    long ms = ms2 - ms1;

    return ms;
}
void SysHelperWait(long milliseconds)
{
    long end = SysHelperGetTime() + milliseconds;
    while (SysHelperGetTime() < end) {}
}
void SysHelperHalt(long milliseconds)
{
    // TODO review

    struct timespec ts;
    int res;

    if (milliseconds < 0)
        errno = EINVAL;

    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;

    do
    {
        res = nanosleep(&ts, &ts);
    }
    while (res && errno == EINTR);

    // usleep(milliseconds * 1000);
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
    SysHelperHalt(waitTime);
    start = end;
}
void SysHelperCreateEscThread()
{
}

int SysHelperGetCurentThreadPriority()
{
    return 0;
}
void SysHelperSetCurentThreadPriorityNormal()
{
}
void SysHelperSetCurentThreadPriorityHigh()
{
}
void SysHelperSetCurentThreadPriorityCritical()
{
}
