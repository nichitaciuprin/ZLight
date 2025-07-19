#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SysWindow SysWindow;

SysWindow* SysWindowCreate(int x, int y, int clientWidth, int clientHeight);
bool SysWindowExists(SysWindow* instance);
void SysWindowDestroy(SysWindow* instance);
void SysWindowUpdate(SysWindow* instance);

void SysWindowSetFormatRgb(SysWindow* instance);
void SysWindowSetFormatBw(SysWindow* instance);

void SysWindowShow(SysWindow* instance);
void SysWindowHide(SysWindow* instance);
void SysWindowSetFullscreen(SysWindow* instance, bool enable);
int SysWindowGetWidth(SysWindow* instance);
int SysWindowGetHeight(SysWindow* instance);
void SysWindowSetName(SysWindow* instance, const char* name);

void SysWindowSetPixelRgb(SysWindow* instance, int x, int y, uint32_t pixel);
void SysWindowSetPixelsAutoScaleRgb1(SysWindow* instance, uint32_t* pixels, int width, int height);
void SysWindowSetPixelsAutoScaleRgb2(SysWindow* instance, uint8_t* pixels, int width, int height);

void SysWindowSetPixelBw(SysWindow* instance, int x, int y, uint8_t pixel);
void SysWindowSetPixelsAutoScaleBw1(SysWindow* instance, uint32_t* pixels, int width, int height);
void SysWindowSetPixelsAutoScaleBw2(SysWindow* instance, uint8_t* pixels, int width, int height);

void SysWindowGetMouseDelta(SysWindow* instance, int* dx, int* dy);

bool SysWindowKeyDown(SysWindow* instance, char key);
bool SysWindowKeyPressed(SysWindow* instance, char key);

bool SysWindowKeyDownUP(SysWindow* instance);
bool SysWindowKeyDownLEFT(SysWindow* instance);
bool SysWindowKeyDownDOWN(SysWindow* instance);
bool SysWindowKeyDownRIGHT(SysWindow* instance);
bool SysWindowKeyDownLBUTTON(SysWindow* instance);
bool SysWindowKeyDownRBUTTON(SysWindow* instance);
bool SysWindowKeyPressedUP(SysWindow* instance);
bool SysWindowKeyPressedLEFT(SysWindow* instance);
bool SysWindowKeyPressedDOWN(SysWindow* instance);
bool SysWindowKeyPressedRIGHT(SysWindow* instance);
bool SysWindowKeyPressedLBUTTON(SysWindow* instance);
bool SysWindowKeyPressedRBUTTON(SysWindow* instance);

#ifdef __cplusplus
}
#endif
