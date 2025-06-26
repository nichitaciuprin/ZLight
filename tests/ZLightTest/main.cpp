#include "Perf.h"
#include "SysHelper.h"
#include "SysWindow.h"
#include "ZLight.h"

typedef struct Camera
{
    Vector3 pos;
    float yaw;
    float pitch;
}
Camera;

static inline float MathMod(float x, float div)
{
    return fmodf(x, div);
}
static inline float MathToDegree(float rad)
{
    float _180_div_pi = (float)57.2957795130823208768;
    return _180_div_pi * rad;
}
static inline float MathToRadians(float deg)
{
    float _pi_div_180 = (float)0.01745329251994329576;
    return _pi_div_180 * deg;
}

static inline Vector2 Vector2Sub(Vector2 l, Vector2 r)
{
    l.x -= r.x;
    l.y -= r.y;
    return l;
}
static inline Vector2 Vector2Mul(Vector2 l, float r)
{
    l.x *= r;
    l.y *= r;
    return l;
}
static inline Vector2 Vector2Div(Vector2 l, float r)
{
    l.x /= r;
    l.y /= r;
    return l;
}
static inline float Vector2Length(Vector2 v)
{
    float x = v.x * v.x;
    float y = v.y * v.y;
    return sqrtf(x + y);
}
static inline Vector2 Vector2Normalize(Vector2 v)
{
    // TODO remove "if (length == 0)" ?
    float length = Vector2Length(v);
    if (length == 0) return v;
    return Vector2Div(v, length);
}

static inline Vector3 CameraGetAxisX(Camera* camera)
{
    Vector3 result = { 1, 0, 0 };
    result = Vector3RotateX(result, camera->pitch);
    result = Vector3RotateY(result, -camera->yaw);
    return result;
}
static inline Vector3 CameraGetAxisY(Camera* camera)
{
    Vector3 result = { 0, 1, 0 };
    result = Vector3RotateX(result, camera->pitch);
    result = Vector3RotateY(result, -camera->yaw);
    return result;
}
static inline Vector3 CameraGetAxisZ(Camera* camera)
{
    Vector3 result = { 0, 0, 1 };
    result = Vector3RotateX(result, camera->pitch);
    result = Vector3RotateY(result, -camera->yaw);
    return result;
}

static inline void CameraRotateClamped(Camera* camera, Vector2 rot)
{
    camera->yaw    += rot.x;
    camera->pitch  += rot.y;

    float angle = 90;
    // float angle = 100; // 100 feels better

    camera->yaw = MathMod(camera->yaw, MATH_PI_MUL_2);
    camera->pitch = MathClamp(camera->pitch, MathToRadians(-angle), MathToRadians(angle));
}
static inline void CameraMoveFree(Camera* camera, Vector3 move)
{
    // TODO double check it works

    Vector3 x = CameraGetAxisX(camera);
    Vector3 y = CameraGetAxisY(camera);
    Vector3 z = CameraGetAxisZ(camera);

    x = Vector3Mul(x, move.x);
    y = Vector3Mul(y, move.y);
    z = Vector3Mul(z, move.z);
    // x.x *= move.x; x.y *= move.x; x.z *= move.x;
    // y.x *= move.y; y.y *= move.y; y.z *= move.y;
    // z.x *= move.z; z.y *= move.z; z.z *= move.z;

    camera->pos = Vector3Add(camera->pos, z);
    camera->pos = Vector3Add(camera->pos, y);
    camera->pos = Vector3Add(camera->pos, x);
}
static inline void CameraMovePlane(Camera* camera, Vector2 move)
{
    Vector3 up = { 0, 1, 0 };
    Vector3 forward = { 0, 0, 1 };

    forward = Vector3RotateY(forward, -camera->yaw);

    Vector3 right = Vector3Cross(up, forward);

    forward.x *= move.y;
    forward.z *= move.y;
    right.x *= move.x;
    right.z *= move.x;

    camera->pos = Vector3Add(camera->pos, forward);
    camera->pos = Vector3Add(camera->pos, right);
}

static inline void CameraInputRotateClamped(Camera* camera, float distance, bool left, bool up, bool down, bool right)
{
    int x = (int)right - (int)left;
    int y = (int)up - (int)down;

    Vector2 rot = { (float)x, (float)y };

    rot = Vector2Normalize(rot);
    rot = Vector2Mul(rot, distance);

    CameraRotateClamped(camera, rot);
}
static inline void CameraInputMoveFree(Camera* camera, float distance, bool w, bool a, bool s, bool d, bool e, bool q)
{
    int x = (int)d - (int)a;
    int y = (int)e - (int)q;
    int z = (int)w - (int)s;

    Vector3 move = { (float)x, (float)y, (float)z };

    move = Vector3Normalize(move);
    move = Vector3Mul(move, distance);

    CameraMoveFree(camera, move);
}
static inline void CameraInputMovePlane(Camera* camera, float distance, bool w, bool a, bool s, bool d)
{
    int x = (int)d - (int)a;
    int y = (int)w - (int)s;

    Vector2 move = { (float)x, (float)y };

    move = Vector2Normalize(move);
    move = Vector2Mul(move, distance);

    CameraMovePlane(camera, move);
}

void UpdatePlayerCamera(Camera* camera, SysWindow* window, float delta)
{
    auto w = SysWindowKeyDown(window, 'W');
    auto a = SysWindowKeyDown(window, 'A');
    auto s = SysWindowKeyDown(window, 'S');
    auto d = SysWindowKeyDown(window, 'D');
    CameraInputMovePlane(camera, delta, w, a, s, d);

    auto left = SysWindowKeyDownLEFT(window);
    auto up = SysWindowKeyDownUP(window);
    auto down = SysWindowKeyDownDOWN(window);
    auto right = SysWindowKeyDownRIGHT(window);
    CameraInputRotateClamped(camera, delta, left, up, down, right);

    int x, y; SysWindowGetMouseDelta(window, &x, &y);
    CameraRotateClamped(camera, { x*0.01f, y*0.01f });
}

#define DELTA_TIME 0.020f

Camera cam = { 0, 1.70f, 0 };
Vector3 light = { 0, 1, 0 };

void DrawFunc(Bitmap* bitmap)
{
    // BitmapExtDrawGrid(bitmap);
    BitmapExtDrawPlane(bitmap);
    BitmapExtDrawCube(bitmap, light, {}, { 0.2f, 0.2f, 0.2f });

    for (int x = -10; x < 10; x++)
    for (int z = -10; z < 10; z++)
    {
        float scale = 0.5f;
        BitmapExtDrawCube(bitmap, { (float)x, 0, (float)z }, { (float)x, (float)z, (float)(x+z) }, { scale, scale, scale });
        // BitmapExtDrawCubeWire(bitmap, { (float)x, 0, (float)z }, { (float)x, (float)z, (float)(x+z) }, { scale, scale, scale });
    }
}

int main()
{
    SysHelperCreateEscThread();

    SysWindow* window = SysWindowCreate(1000, 250, 512, 512);
    SysWindowSetFormatBw(window);
    SysWindowShow(window);
    // Bitmap* bitmap = BitmapCreate(128, 128);
    Bitmap* bitmap = BitmapCreate(256, 256);

    while (SysWindowExists(window))
    {
        REC_1
        {
            // animation
            // float time = SysHelperGetTime();
            // time /= 1000;
            // time = MathSin(time);
            // light.y = 1 + time / 4;

            UpdatePlayerCamera(&cam, window, 4*DELTA_TIME);
            BitmapReset(bitmap);

            BitmapSetViewByPyr(bitmap, cam.pos, cam.pitch, cam.yaw, 0);
            // BitmapSetViewByEuler(bitmap, cam.pos, cam.pitch, -cam.yaw, 0);
            // BitmapSetViewByTarget(bitmap, cam.pos, {}, { 0, 1, 0 });

            DrawFunc(bitmap);
            LightData1RemoveLight();
            LightData1AddLight(light, 1);
            LightData1UpdateShadows(DrawFunc);
            LightData1ApplyLight(bitmap);

            // DrawFunc(bitmap);
            // BitmapApplyDepthAdjusted(bitmap);

            SysWindowSetPixelsAutoScaleBw1(window, (uint32_t*)bitmap->buffer, bitmap->width, bitmap->height);
        }
        REC_2

        SysWindowUpdate(window);
        SysHelperHaltLoop(20);
    }

    return 0;
}
