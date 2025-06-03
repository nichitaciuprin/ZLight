#pragma once

#include "BaseLang.h"
#include "Bitmap.h"

#define LIGHT_MAX_DIST 15
#define SHADOW_MAP_SIZE 128
#define SHADOW_MAP_BIAS 0.001f
// #define SHADOW_MAP_BIAS 0.002f
// #define SHADOW_MAP_BIAS 0.005f
#define SHADOW_MAP_PROJ_MACRO(near, far) ((Matrix)\
{{\
    {1, 0, 0, 0},\
    {0, 1, 0, 0},\
    {0, 0,  ((far+near)   / (far-near)), 1},\
    {0, 0, -((near*2*far) / (far-near)), 0}\
}})
#define SHADOW_MAP_PROJ SHADOW_MAP_PROJ_MACRO(0.1f, LIGHT_MAX_DIST)

typedef struct SpotLight
{
    Vector3 pos;
    float lum;
    float bufl[SHADOW_MAP_SIZE*SHADOW_MAP_SIZE]; Matrix matl;
    float bufr[SHADOW_MAP_SIZE*SHADOW_MAP_SIZE]; Matrix matr;
    float bufd[SHADOW_MAP_SIZE*SHADOW_MAP_SIZE]; Matrix matd;
    float bufu[SHADOW_MAP_SIZE*SHADOW_MAP_SIZE]; Matrix matu;
    float bufb[SHADOW_MAP_SIZE*SHADOW_MAP_SIZE]; Matrix matb;
    float buff[SHADOW_MAP_SIZE*SHADOW_MAP_SIZE]; Matrix matf;
}
SpotLight;
typedef struct LightData
{
    SpotLight* lights; int lightsc;
    // TODO dir lights
}
LightData;

static inline void UpdateShadows1(void (*draw)(Bitmap* bitmap), SpotLight* light)
{
    Camera cf = {}; cf.position = light->pos; cf.yaw = MATH_PI_DIV_2*0;
    Camera cr = {}; cr.position = light->pos; cr.yaw = MATH_PI_DIV_2*1;
    Camera cb = {}; cb.position = light->pos; cb.yaw = MATH_PI_DIV_2*2;
    Camera cl = {}; cl.position = light->pos; cl.yaw = MATH_PI_DIV_2*3;
    Camera cu = {}; cu.position = light->pos; cu.pitch = +MATH_PI_DIV_2;
    Camera cd = {}; cd.position = light->pos; cd.pitch = -MATH_PI_DIV_2;

    light->matf = MatrixView3(&cf);
    light->matr = MatrixView3(&cr);
    light->matb = MatrixView3(&cb);
    light->matl = MatrixView3(&cl);
    light->matu = MatrixView3(&cu);
    light->matd = MatrixView3(&cd);

    Bitmap bf; bf.buffer = light->buff; bf.view = light->matf; bf.proj = SHADOW_MAP_PROJ; bf.width = SHADOW_MAP_SIZE; bf.height = SHADOW_MAP_SIZE; bf.far = LIGHT_MAX_DIST;
    Bitmap br; br.buffer = light->bufr; br.view = light->matr; br.proj = SHADOW_MAP_PROJ; br.width = SHADOW_MAP_SIZE; br.height = SHADOW_MAP_SIZE; br.far = LIGHT_MAX_DIST;
    Bitmap bb; bb.buffer = light->bufb; bb.view = light->matb; bb.proj = SHADOW_MAP_PROJ; bb.width = SHADOW_MAP_SIZE; bb.height = SHADOW_MAP_SIZE; bb.far = LIGHT_MAX_DIST;
    Bitmap bl; bl.buffer = light->bufl; bl.view = light->matl; bl.proj = SHADOW_MAP_PROJ; bl.width = SHADOW_MAP_SIZE; bl.height = SHADOW_MAP_SIZE; bl.far = LIGHT_MAX_DIST;
    Bitmap bu; bu.buffer = light->bufu; bu.view = light->matu; bu.proj = SHADOW_MAP_PROJ; bu.width = SHADOW_MAP_SIZE; bu.height = SHADOW_MAP_SIZE; bu.far = LIGHT_MAX_DIST;
    Bitmap bd; bd.buffer = light->bufd; bd.view = light->matd; bd.proj = SHADOW_MAP_PROJ; bd.width = SHADOW_MAP_SIZE; bd.height = SHADOW_MAP_SIZE; bd.far = LIGHT_MAX_DIST;

    BitmapReset(&bf); draw(&bf);
    BitmapReset(&br); draw(&br);
    BitmapReset(&bb); draw(&bb);
    BitmapReset(&bl); draw(&bl);
    BitmapReset(&bu); draw(&bu);
    BitmapReset(&bd); draw(&bd);
}
static inline void UpdateShadows2(void (*draw)(Bitmap* bitmap), LightData* lightData)
{
    for (int i = 0; i < lightData->lightsc; i++)
        UpdateShadows1(draw, &lightData->lights[i]);
}

static inline float CalcLight1(Vector3 surPos, float lum, Vector3 lightPos)
{
    float t;

    float dist1 = Vector3Distance(surPos, lightPos);
    float dist2 = LIGHT_MAX_DIST;
    t = dist1 / dist2;
    t = t < 1 ? (1 - t) * lum : 0;

    return t;
}
static inline float CalcLight2(Vector3 surPos, float lum, Vector3 lightPos, Vector3 surNormal)
{
    float t;

    float dist1 = Vector3Distance(surPos, lightPos);
    float dist2 = LIGHT_MAX_DIST;
    t = dist1 / dist2;
    t = t < 1 ? (1 - t) * lum : 0;

    Vector3 dirNorm;
    dirNorm = Vector3Sub(lightPos, surPos);
    dirNorm = Vector3Normalize(dirNorm);
    float dot = Vector3Dot(dirNorm, surNormal);
    t = dot > 0 ? t * dot : 0;

    return t;
}
static inline float CalcLight3(Vector3 surPos, float lum, Vector3 lightPos, Bitmap* m)
{
    Vector3 ndc = WorldToNdc(surPos, m->view, m->proj);

    if (ndc.x < -1 || +1 < ndc.x) return 0.0f;
    if (ndc.y < -1 || +1 < ndc.y) return 0.0f;
    if (ndc.z < -1 || +1 < ndc.z) return 0.0f;

    int x = (+ndc.x + 1.0f) / 2.0f * (m->width  - 1);
    int y = (-ndc.y + 1.0f) / 2.0f * (m->height - 1);

    int i = x + y * m->width;

    float z1 = m->buffer[i] + SHADOW_MAP_BIAS;
    float z2 = ndc.z;

    if (z1 < z2) return 0.0f;

    float t;

    float dist1 = Vector3Distance(surPos, lightPos);
    float dist2 = LIGHT_MAX_DIST;
    t = dist1 / dist2;
    t = t < 1 ? (1 - t) * lum : 0;

    return t;
}
static inline float CalcLight4(Vector3 surPos, float lum, Vector3 lightPos, float* buffer, Matrix view)
{
    Vector3 ndc = WorldToNdc(surPos, view, SHADOW_MAP_PROJ);

    if (ndc.x < -1 || +1 < ndc.x) return 0.0f;
    if (ndc.y < -1 || +1 < ndc.y) return 0.0f;
    // if (ndc.z < -1 || +1 < ndc.z) return 0.0f;

    // maybe use this
    if (ndc.z < -1) return lum;
    if (ndc.z > +1) return 0.0f;

    int x = (+ndc.x + 1.0f) / 2.0f * (SHADOW_MAP_SIZE - 1);
    int y = (-ndc.y + 1.0f) / 2.0f * (SHADOW_MAP_SIZE - 1);

    int i = x + y * SHADOW_MAP_SIZE;

    float z1 = buffer[i] + SHADOW_MAP_BIAS;
    float z2 = ndc.z;

    if (z1 < z2) return 0.0f;

    float t;

    float dist1 = Vector3Distance(surPos, lightPos);
    float dist2 = LIGHT_MAX_DIST;
    t = dist1 / dist2;
    t = t < 1 ? (1 - t) * lum : 0;

    return t;
}

static inline float CalcLightSpot(Vector3 surPos, SpotLight* light)
{
    int sectorId = 0;
    {
        Vector3 v = Vector3Sub(surPos, light->pos);

        float absx = MathAbs(v.x);
        float absy = MathAbs(v.y);
        float absz = MathAbs(v.z);

        float max; char axis;

                        { max = absx; axis = 'x'; };
        if (max < absy) { max = absy; axis = 'y'; };
        if (max < absz) { max = absz; axis = 'z'; };

        switch (axis)
        {
            case 'x': sectorId = v.x < 0 ? 0 : 1; break;
            case 'y': sectorId = v.y < 0 ? 2 : 3; break;
            case 'z': sectorId = v.z < 0 ? 4 : 5; break;
        }
    }

    float t = 0;
    {
        switch (sectorId)
        {
            case 0: { t = CalcLight4(surPos, light->lum, light->pos, light->bufl, light->matl); break; }
            case 1: { t = CalcLight4(surPos, light->lum, light->pos, light->bufr, light->matr); break; }
            case 2: { t = CalcLight4(surPos, light->lum, light->pos, light->bufd, light->matd); break; }
            case 3: { t = CalcLight4(surPos, light->lum, light->pos, light->bufu, light->matu); break; }
            case 4: { t = CalcLight4(surPos, light->lum, light->pos, light->bufb, light->matb); break; }
            case 5: { t = CalcLight4(surPos, light->lum, light->pos, light->buff, light->matf); break; }
        }
    }

    return t;
}
static inline float CalcLightSpotNoShadow(Vector3 surPos, SpotLight* light)
{
    return CalcLight1(surPos, light->lum, light->pos);
}

static inline float CalcLight(Vector3 surPos, LightData* lightData)
{
    float result = 0;

    for (int i = 0; i < lightData->lightsc; i++)
    {
        SpotLight* light = &lightData->lights[i];

        float t = CalcLightSpot(surPos, light);

        result =
        result > t ?
        result : t;
    }

    return result;
}
static inline float CalcLightNoShadow(Vector3 surPos, LightData* lightData)
{
    float result = 0;

    for (int i = 0; i < lightData->lightsc; i++)
    {
        SpotLight* light = &lightData->lights[i];

        float t = CalcLightSpotNoShadow(surPos, light);

        result =
        result > t ?
        result : t;
    }

    return result;
}

static inline void ApplyLight(Bitmap* bitmap, LightData* lightData)
{
    uint32_t* pixels = (uint32_t*)bitmap->buffer;

    Matrix viewi = MatrixInvert(bitmap->view);
    Matrix proji = MatrixInvert(bitmap->proj);

    for (int y = 0; y < bitmap->height; y++)
    for (int x = 0; x < bitmap->width;  x++)
    {
        int i = x + y * bitmap->width;
        float z = bitmap->buffer[i];
        if (z == 1) { pixels[i] = ColorCreateBwFloat(0); continue; }
        Vector3 sp = (Vector3){ (float)x, (float)y, z };
        Vector3 ndc = ScreenSpaceToNdc(sp, bitmap->width-1, bitmap->height-1);
        Vector3 surPos = NdcToWorld(ndc, viewi, proji);
        float t = CalcLight(surPos, lightData);
        pixels[i] = ColorCreateBwFloat(t);
    }
}
static inline void ApplyLightNoShadow(Bitmap* bitmap, LightData* lightData)
{
    uint32_t* pixels = (uint32_t*)bitmap->buffer;

    Matrix viewi = MatrixInvert(bitmap->view);
    Matrix proji = MatrixInvert(bitmap->proj);

    for (int y = 0; y < bitmap->height; y++)
    for (int x = 0; x < bitmap->width;  x++)
    {
        int i = x + y * bitmap->width;
        float z = bitmap->buffer[i];
        if (z == 1) { pixels[i] = ColorCreateBwFloat(0); continue; }
        Vector3 sp = (Vector3){ (float)x, (float)y, z };
        Vector3 ndc = ScreenSpaceToNdc(sp, bitmap->width-1, bitmap->height-1);
        Vector3 surPos = NdcToWorld(ndc, viewi, proji);
        float t = CalcLightNoShadow(surPos, lightData);
        pixels[i] = ColorCreateBwFloat(t);
    }
}

LightData _LightData1_data = {};
int _LightData1_max = 0;
static inline void LightData1RemoveLight()
{
    _LightData1_data.lightsc = 0;
}
static inline void LightData1AddLight(Vector3 pos, float lum)
{
    int size = _LightData1_data.lightsc + 1;

    if (_LightData1_max < size)
    {
        _LightData1_max = size * 2;
        _LightData1_data.lights = (SpotLight*)realloc(_LightData1_data.lights, _LightData1_max*sizeof(SpotLight));
    }

    SpotLight* light = &_LightData1_data.lights[_LightData1_data.lightsc];

    light->pos = pos;
    light->lum = lum;

    _LightData1_data.lightsc++;
}
static inline void LightData1UpdateShadows(void (*draw)(Bitmap* bitmap))
{
    UpdateShadows2(draw, &_LightData1_data);
}
static inline void LightData1ApplyLight(Bitmap* bitmap)
{
    ApplyLight(bitmap, &_LightData1_data);
}
static inline void LightData1ApplyLightNoShadow(Bitmap* bitmap)
{
    ApplyLightNoShadow(bitmap, &_LightData1_data);
}
