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
#include "ModelForest1.h"
#include "ModelCave.h"

Camera cam = { 0, 1.70f, 0 };
Vector3 light = { 2.00, 2.00f, 0 };

void DrawFunc(Bitmap* bitmap)
{
    BitmapExtDrawPlane2(bitmap, {}, 100);
    ModelCave::Draw(bitmap);
    ModelForest::Draw(bitmap);
    Particle::Draw(bitmap);
    BitmapExtDrawCube(bitmap, light, {}, Vector3One()/5);
}

int main()
{
    SysHelperCreateEscThread();

    SysWindow* window = SysWindowCreate(1000, 250, 512, 512);
    SysWindowSetFormatBw(window);
    SysWindowShow(window);
    Bitmap* bitmap = BitmapCreate(128, 128);

    ModelCave::Init();

    while (SysWindowExists(window))
    {
        REC_1
        {
            {
                UpdatePlayerCamera(&cam, window);

                if (SysWindowKeyDownLBUTTON(window))
                {
                    for (int i = 0; i < 5; i++)
                        Particle::Create(&cam);
                }

                if (SysWindowKeyDownRBUTTON(window))
                    light = Vector3MoveTowards1(light, cam.position, DELTA_TIME*2.0f);

                Particle::Update(DELTA_TIME);

                ModelForest::Push(cam.position);
                ModelCave::Push(cam.position);
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
                        BitmapSetView(bitmap, &cam);
                        DrawFunc(bitmap);
                        BitmapApplyDepthAdjustedInvert(bitmap);
                        break;
                    }
                    case 1:
                    {
                        BitmapReset(bitmap);
                        BitmapSetView(bitmap, &cam);
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
