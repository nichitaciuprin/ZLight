#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void SysHelperGetConsolePosition(int* x, int* y);
int SysHelperGetPid();
int SysHelperGetCpuUsage();
long SysHelperGetTime();
void SysHelperWait(long milliseconds);
void SysHelperHalt(long milliseconds);
void SysHelperWaitLoop(long timestep);
void SysHelperHaltLoop(long timestep);
void SysHelperCreateEscThread();
int SysHelperGetCurentThreadPriority();
void SysHelperSetCurentThreadPriorityNormal();
void SysHelperSetCurentThreadPriorityHigh();
void SysHelperSetCurentThreadPriorityCritical();

#ifdef __cplusplus
}
#endif
