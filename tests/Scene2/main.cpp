#include "SysHelper.h"
#include "SysWindow.h"
#include "BaseLang.hpp"
#include "BaseMath.hpp"
#include "Print.h"
#include "Perf.h"
#include "Subgen.h"
#include "BitmapExt.h"
#include "LightData.h"

#define DELTA_TIME_MS 10
#define DELTA_TIME (DELTA_TIME_MS / 1000.0f)

#include "Helper.h"
#include "Fire.h"
#include "ModelForest2.h"
#include "Snow.h"
#include "Body.h"

Camera _cam = { 0, 1.70f, 0 };
Camera* cam = &_cam;
Vector3 light = { 0, 0.25f, 0 };

void DrawFunc(Bitmap* bitmap)
{
    BitmapExtDrawPlane2(bitmap, {}, 100);
    BitmapExtDrawCube(bitmap, light, {}, Vector3One()/2);
    ModelForest::Draw(bitmap);
    Particle::Draw(bitmap);
    Snow::Draw(bitmap);
    Vector3 foot = { cam->position.x, 0, cam->position.z };
    DrawBody2(bitmap, foot, -cam->yaw, cam->pitch);
}

int main()
{
    SysHelperCreateEscThread();

    SysWindow* window = SysWindowCreate(1000, 250, 512, 512);
    SysWindowSetFormatBw(window);
    SysWindowShow(window);
    Bitmap* bitmap = BitmapCreate(128, 128);

    cam->position = { +5.88, 1.70, +7.26 };
    cam->yaw = -2.48;
    cam->pitch = 0.20;

    while (SysWindowExists(window))
    {
        REC_1
        {
            {
                UpdatePlayerCamera(cam, window);
                ModelForest::Push(cam->position);
                Snow::Update();
            }
            {
                static int drawMode = 0;
                {
                    if (SysWindowKeyPressed(window, '1')) drawMode = 0;
                    if (SysWindowKeyPressed(window, '2')) drawMode = 1;
                }
                switch (drawMode)
                {
                    case 0:
                    {
                        BitmapReset(bitmap);
                        BitmapSetView(bitmap, cam);
                        DrawFunc(bitmap);
                        BitmapApplyDepthAdjustedInvert(bitmap);
                        break;
                    }
                    case 1:
                    {
                        BitmapReset(bitmap);
                        BitmapSetView(bitmap, cam);
                        DrawFunc(bitmap);
                        LightData1RemoveLight();
                        LightData1AddLight(light, 1);
                        LightData1UpdateShadows(DrawFunc);
                        LightData1ApplyLight(bitmap);
                        break;
                    }
                }
                SysWindowSetPixelsAutoScaleBw1(window, (uint32_t*)bitmap->buffer, bitmap->width, bitmap->height);
            }
        }
        REC_2

        SysWindowUpdate(window);
        SysHelperHaltLoop(DELTA_TIME_MS);
    }

    return 0;
}
