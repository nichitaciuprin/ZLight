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
#include "ModelForest3.h"

Camera _cam = { 0, 1.70f, 0 };
Camera* cam = &_cam;
Vector3 light = { 0, 0.25f, 0 };

void DrawFunc(Bitmap* bitmap)
{
    BitmapExtDrawPlane2(bitmap, {}, 100);
    BitmapExtDrawCube(bitmap, light, {}, Vector3One()/5);
    ModelForest::Draw(bitmap, cam->pos);
    Particle::Draw(bitmap);
}

int main()
{
    SysHelperCreateEscThread();

    SysWindow* window = SysWindowCreate(1000, 250, 512, 512);
    SysWindowSetFormatBw(window);
    SysWindowShow(window);
    Bitmap* bitmap = BitmapCreate(128, 128);

    ModelForest::Init();

    while (SysWindowExists(window))
    {
        REC_1
        {
            {
                UpdatePlayerCamera(cam, window);

                if (SysWindowKeyDownLBUTTON(window))
                {
                    for (int i = 0; i < 5; i++)
                        Particle::Create(cam);
                }

                Particle::Update(DELTA_TIME);

                Vector3 pos = cam->pos;
                auto camx = CameraGetAxisX(cam);
                auto camy = CameraGetAxisY(cam);
                auto camz = CameraGetAxisZ(cam);
                pos += camx * 0.50f;
                pos += camy * 0.25f;
                pos += camz;
                light = pos;

                ModelForest::Push(cam->pos);
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
                SysWindowSetPixelsAutoBw1(window, (uint32_t*)bitmap->buffer, bitmap->width, bitmap->height);
            }
        }
        REC_2

        SysWindowUpdate(window);
        SysHelperHaltLoop(DELTA_TIME_MS);
    }

    return 0;
}
