#pragma once

#include "SysWindow.h"
#include "BaseLang.hpp"
#include "BaseMath.hpp"

void UpdatePlayerCamera(Camera* camera, SysWindow* window)
{
    auto w = SysWindowKeyDown(window, 'W');
    auto a = SysWindowKeyDown(window, 'A');
    auto s = SysWindowKeyDown(window, 'S');
    auto d = SysWindowKeyDown(window, 'D');
    CameraInputMovePlane(camera, DELTA_TIME*4, w, a, s, d);

    auto left = SysWindowKeyDownLEFT(window);
    auto up = SysWindowKeyDownUP(window);
    auto down = SysWindowKeyDownDOWN(window);
    auto right = SysWindowKeyDownRIGHT(window);
    CameraInputRotateClamped(camera, DELTA_TIME*4, left, up, down, right);

    int x, y; SysWindowGetMouseDelta(window, &x, &y);
    CameraRotateClamped(camera, { x*0.01f, y*0.01f });
}
void UpdatePlayerCameraFree(Camera* camera, SysWindow* window)
{
    auto w = SysWindowKeyDown(window, 'W');
    auto a = SysWindowKeyDown(window, 'A');
    auto s = SysWindowKeyDown(window, 'S');
    auto d = SysWindowKeyDown(window, 'D');
    auto q = SysWindowKeyDown(window, 'Q');
    auto e = SysWindowKeyDown(window, 'E');
    CameraInputMoveFree(camera, DELTA_TIME*4, w, a, s, d, e, q);

    auto left = SysWindowKeyDownLEFT(window);
    auto up = SysWindowKeyDownUP(window);
    auto down = SysWindowKeyDownDOWN(window);
    auto right = SysWindowKeyDownRIGHT(window);
    CameraInputRotateClamped(camera, DELTA_TIME*4, left, up, down, right);

    int x, y; SysWindowGetMouseDelta(window, &x, &y);
    CameraRotateClamped(camera, { x*0.01f, y*0.01f });
}
Vector3 GetPlayerLightPos(Camera* cam)
{
    Vector3 pos = cam->position;
    auto camx = CameraGetAxisX(cam);
    auto camy = CameraGetAxisY(cam);
    auto camz = CameraGetAxisZ(cam);
    pos += camx * 0.5f;
    pos += camy * 0.25f;
    pos += camz;
    return pos;
}
Vector3 GetLightOffset(Vector3 light)
{
    Vector3 randDir = {};
    randDir.x = Subgen1FractionSigned();
    randDir.y = Subgen1FractionSigned();
    randDir.z = Subgen1FractionSigned();
    randDir = Vector3Normalize(randDir) / 10;
    return light + randDir;
}
