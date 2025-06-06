#pragma once

#include "BaseMath.h"

static inline bool ClipLineBack(Vector3* v0, Vector3* v1, float offset)
{
    int flags = 0;

    if (v0->z < offset) flags += 1;
    if (v1->z < offset) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t = MathLerpInverse(v0->z, v1->z, offset);

            v0->x = MathLerp(v0->x, v1->x, t);
            v0->y = MathLerp(v0->y, v1->y, t);
            v0->z = offset;

            return false;
        }
        case 2:
        {
            float t = MathLerpInverse(v0->z, v1->z, offset);

            v1->x = MathLerp(v0->x, v1->x, t);
            v1->y = MathLerp(v0->y, v1->y, t);
            v1->z = offset;

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool ClipLineFront(Vector3* v0, Vector3* v1, float offset)
{
    int flags = 0;

    if (v0->z > offset) flags += 1;
    if (v1->z > offset) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t = MathLerpInverse(v0->z, v1->z, offset);

            v0->x = MathLerp(v0->x, v1->x, t);
            v0->y = MathLerp(v0->y, v1->y, t);
            v0->z = offset;

            return false;
        }
        case 2:
        {
            float t = MathLerpInverse(v0->z, v1->z, offset);

            v1->x = MathLerp(v0->x, v1->x, t);
            v1->y = MathLerp(v0->y, v1->y, t);
            v1->z = offset;

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool ClipLineLeft(Vector3* v0, Vector3* v1, float offset)
{
    int flags = 0;

    if (v0->x < offset) flags += 1;
    if (v1->x < offset) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t = MathLerpInverse(v0->x, v1->x, offset);

            v0->x = offset;
            v0->y = MathLerp(v0->y, v1->y, t);
            v0->z = MathLerp(v0->z, v1->z, t);

            return false;
        }
        case 2:
        {
            float t = MathLerpInverse(v0->x, v1->x, offset);

            v1->x = offset;
            v1->y = MathLerp(v0->y, v1->y, t);
            v1->z = MathLerp(v0->z, v1->z, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool ClipLineRight(Vector3* v0, Vector3* v1, float offset)
{
    int flags = 0;

    if (v0->x > offset) flags += 1;
    if (v1->x > offset) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t = MathLerpInverse(v0->x, v1->x, offset);

            v0->x = offset;
            v0->y = MathLerp(v0->y, v1->y, t);
            v0->z = MathLerp(v0->z, v1->z, t);

            return false;
        }
        case 2:
        {
            float t = MathLerpInverse(v0->x, v1->x, offset);

            v1->x = offset;
            v1->y = MathLerp(v0->y, v1->y, t);
            v1->z = MathLerp(v0->z, v1->z, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool ClipLineDown(Vector3* v0, Vector3* v1, float offset)
{
    int flags = 0;

    if (v0->y < offset) flags += 1;
    if (v1->y < offset) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t = MathLerpInverse(v0->y, v1->y, offset);

            v0->x = MathLerp(v0->x, v1->x, t);
            v0->y = offset;
            v0->z = MathLerp(v0->z, v1->z, t);

            return false;
        }
        case 2:
        {
            float t = MathLerpInverse(v0->y, v1->y, offset);

            v1->x = MathLerp(v0->x, v1->x, t);
            v1->y = offset;
            v1->z = MathLerp(v0->z, v1->z, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool ClipLineUp(Vector3* v0, Vector3* v1, float offset)
{
    int flags = 0;

    if (v0->y > offset) flags += 1;
    if (v1->y > offset) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t = MathLerpInverse(v0->y, v1->y, offset);

            v0->x = MathLerp(v0->x, v1->x, t);
            v0->y = offset;
            v0->z = MathLerp(v0->z, v1->z, t);

            return false;
        }
        case 2:
        {
            float t = MathLerpInverse(v0->y, v1->y, offset);

            v1->x = MathLerp(v0->x, v1->x, t);
            v1->y = offset;
            v1->z = MathLerp(v0->z, v1->z, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}

static inline void ClipPoligonBack(Vector3* input, Vector3* output, int* vertexCount, float offset)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector3* p0 = &input[initCount - 1];
    if (p0->z < offset) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector3* p1 = &input[i];
        if (p1->z < offset) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector3 newPoint;

                float t = MathLerpInverse(p0->z, p1->z, offset);

                newPoint.x = MathLerp(p0->x, p1->x, t);
                newPoint.y = MathLerp(p0->y, p1->y, t);
                newPoint.z = offset;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector3 newPoint;

                float t = MathLerpInverse(p0->z, p1->z, offset);

                newPoint.x = MathLerp(p0->x, p1->x, t);
                newPoint.y = MathLerp(p0->y, p1->y, t);
                newPoint.z = offset;

                output[index] = *p0; index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
static inline void ClipPoligonFront(Vector3* input, Vector3* output, int* vertexCount, float offset)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector3* p0 = &input[initCount - 1];
    if (p0->z > offset) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector3* p1 = &input[i];
        if (p1->z > offset) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector3 newPoint;

                float t = MathLerpInverse(p0->z, p1->z, offset);

                newPoint.x = MathLerp(p0->x, p1->x, t);
                newPoint.y = MathLerp(p0->y, p1->y, t);
                newPoint.z = offset;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector3 newPoint;

                float t = MathLerpInverse(p0->z, p1->z, offset);

                newPoint.x = MathLerp(p0->x, p1->x, t);
                newPoint.y = MathLerp(p0->y, p1->y, t);
                newPoint.z = offset;

                output[index] = *p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
static inline void ClipPoligonLeft(Vector3* input, Vector3* output, int* vertexCount, float offset)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector3* p0 = &input[initCount - 1];
    if (p0->x < offset) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector3* p1 = &input[i];
        if (p1->x < offset) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector3 newPoint;

                float t = MathLerpInverse(p0->x, p1->x, offset);

                newPoint.x = offset;
                newPoint.y = MathLerp(p0->y, p1->y, t);
                newPoint.z = MathLerp(p0->z, p1->z, t);

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector3 newPoint;

                float t = MathLerpInverse(p0->x, p1->x, offset);

                newPoint.x = offset;
                newPoint.y = MathLerp(p0->y, p1->y, t);
                newPoint.z = MathLerp(p0->z, p1->z, t);

                output[index] = *p0; index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
static inline void ClipPoligonRight(Vector3* input, Vector3* output, int* vertexCount, float offset)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector3* p0 = &input[initCount - 1];
    if (p0->x > offset) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector3* p1 = &input[i];
        if (p1->x > offset) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector3 newPoint;

                float t = MathLerpInverse(p0->x, p1->x, offset);

                newPoint.x = offset;
                newPoint.y = MathLerp(p0->y, p1->y, t);
                newPoint.z = MathLerp(p0->z, p1->z, t);

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector3 newPoint;

                float t = MathLerpInverse(p0->x, p1->x, offset);

                newPoint.x = offset;
                newPoint.y = MathLerp(p0->y, p1->y, t);
                newPoint.z = MathLerp(p0->z, p1->z, t);

                output[index] = *p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
static inline void ClipPoligonDown(Vector3* input, Vector3* output, int* vertexCount, float offset)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector3* p0 = &input[initCount - 1];
    if (p0->y < offset) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector3* p1 = &input[i];
        if (p1->y < offset) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector3 newPoint;

                float t = MathLerpInverse(p0->y, p1->y, offset);

                newPoint.x = MathLerp(p0->x, p1->x, t);
                newPoint.y = offset;
                newPoint.z = MathLerp(p0->z, p1->z, t);

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector3 newPoint;

                float t = MathLerpInverse(p0->y, p1->y, offset);

                newPoint.x = MathLerp(p0->x, p1->x, t);
                newPoint.y = offset;
                newPoint.z = MathLerp(p0->z, p1->z, t);

                output[index] = *p0; index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
static inline void ClipPoligonUp(Vector3* input, Vector3* output, int* vertexCount, float offset)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector3* p0 = &input[initCount - 1];
    if (p0->y > offset) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector3* p1 = &input[i];
        if (p1->y > offset) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector3 newPoint;

                float t = MathLerpInverse(p0->y, p1->y, offset);

                newPoint.x = MathLerp(p0->x, p1->x, t);
                newPoint.y = offset;
                newPoint.z = MathLerp(p0->z, p1->z, t);

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector3 newPoint;

                float t = MathLerpInverse(p0->y, p1->y, offset);

                newPoint.x = MathLerp(p0->x, p1->x, t);
                newPoint.y = offset;
                newPoint.z = MathLerp(p0->z, p1->z, t);

                output[index] = *p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}

static inline bool ClipInFrustum(Vector4 p)
{
    return
    (-p.w <= p.x && p.x <= p.w) &&
    (-p.w <= p.y && p.y <= p.w) &&
    (-p.w <= p.z && p.z <= p.w);
}

static inline bool ClipLineWClipSpace(Vector4* p0, Vector4* p1)
{
    int flags = 0;

    if (p0->w < 0) flags += 1;
    if (p1->w < 0) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t0 = p0->w;
            float t1 = p1->w;

            float t = t0 / (t0 - t1);

            *p0 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w;
            float t1 = p1->w;

            float t = t0 / (t0 - t1);

            *p1 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool ClipLineBackClipSpace(Vector4* p0, Vector4* p1)
{
    int flags = 0;

    if (p0->z < -p0->w) flags += 1;
    if (p1->z < -p1->w) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t0 = p0->w + p0->z;
            float t1 = p1->w + p1->z;

            float t = t0 / (t0 - t1);

            *p0 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w + p0->z;
            float t1 = p1->w + p1->z;

            float t = t0 / (t0 - t1);

            *p1 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool ClipLineFrontClipSpace(Vector4* p0, Vector4* p1)
{
    int flags = 0;

    if (p0->z > p0->w) flags += 1;
    if (p1->z > p1->w) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t0 = p0->w - p0->z;
            float t1 = p1->w - p1->z;

            float t = t0 / (t0 - t1);

            *p0 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w - p0->z;
            float t1 = p1->w - p1->z;

            float t = t0 / (t0 - t1);

            *p1 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool ClipLineLeftClipSpace(Vector4* p0, Vector4* p1)
{
    int flags = 0;

    if (p0->x < -p0->w) flags += 1;
    if (p1->x < -p1->w) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t0 = p0->w + p0->x;
            float t1 = p1->w + p1->x;

            float t = t0 / (t0 - t1);

            *p0 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w + p0->x;
            float t1 = p1->w + p1->x;

            float t = t0 / (t0 - t1);

            *p1 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool ClipLineRightClipSpace(Vector4* p0, Vector4* p1)
{
    int flags = 0;

    if (p0->x > p0->w) flags += 1;
    if (p1->x > p1->w) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t0 = p0->w - p0->x;
            float t1 = p1->w - p1->x;

            float t = t0 / (t0 - t1);

            *p0 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w - p0->x;
            float t1 = p1->w - p1->x;

            float t = t0 / (t0 - t1);

            *p1 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool ClipLineDownClipSpace(Vector4* p0, Vector4* p1)
{
    int flags = 0;

    if (p0->y < -p0->w) flags += 1;
    if (p1->y < -p1->w) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t0 = p0->w + p0->y;
            float t1 = p1->w + p1->y;

            float t = t0 / (t0 - t1);

            *p0 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w + p0->y;
            float t1 = p1->w + p1->y;

            float t = t0 / (t0 - t1);

            *p1 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}
static inline bool ClipLineUpClipSpace(Vector4* p0, Vector4* p1)
{
    int flags = 0;

    if (p0->y > p0->w) flags += 1;
    if (p1->y > p1->w) flags += 2;

    switch (flags)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            float t0 = p0->w - p0->y;
            float t1 = p1->w - p1->y;

            float t = t0 / (t0 - t1);

            *p0 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        case 2:
        {
            float t0 = p0->w - p0->y;
            float t1 = p1->w - p1->y;

            float t = t0 / (t0 - t1);

            *p1 = Vector4Lerp(*p0, *p1, t);

            return false;
        }
        default:
        {
            return true;
        }
    }
}

static inline void ClipPoligonWClipSpace(Vector4* input, Vector4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector4* p0 = &input[initCount - 1];
    if (p0->w < 0) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector4* p1 = &input[i];
        if (p1->w < 0) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector4 newPoint;

                float t0 = p0->w;
                float t1 = p1->w;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.w = 0;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector4 newPoint;

                float t0 = p0->w;
                float t1 = p1->w;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.w = 0;

                output[index] = *p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
static inline void ClipPoligonBackClipSpace(Vector4* input, Vector4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector4* p0 = &input[initCount - 1];
    if (p0->z < -p0->w) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector4* p1 = &input[i];
        if (p1->z < -p1->w) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector4 newPoint;

                float t0 = p0->w + p0->z;
                float t1 = p1->w + p1->z;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.z = -newPoint.w;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector4 newPoint;

                float t0 = p0->w + p0->z;
                float t1 = p1->w + p1->z;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.z = -newPoint.w;

                output[index] = *p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
static inline void ClipPoligonFrontClipSpace(Vector4* input, Vector4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector4* p0 = &input[initCount - 1];
    if (p0->z > p0->w) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector4* p1 = &input[i];
        if (p1->z > p1->w) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector4 newPoint;

                float t0 = p0->w - p0->z;
                float t1 = p1->w - p1->z;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.z = newPoint.w;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector4 newPoint;

                float t0 = p0->w - p0->z;
                float t1 = p1->w - p1->z;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.z = newPoint.w;

                output[index] = *p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
static inline void ClipPoligonLeftClipSpace(Vector4* input, Vector4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector4* p0 = &input[initCount - 1];
    if (p0->x < -p0->w) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector4* p1 = &input[i];
        if (p1->x < -p1->w) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector4 newPoint;

                float t0 = p0->w + p0->x;
                float t1 = p1->w + p1->x;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.x = -newPoint.w;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector4 newPoint;

                float t0 = p0->w + p0->x;
                float t1 = p1->w + p1->x;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.x = -newPoint.w;

                output[index] = *p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
static inline void ClipPoligonRightClipSpace(Vector4* input, Vector4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector4* p0 = &input[initCount - 1];
    if (p0->x > p0->w) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector4* p1 = &input[i];
        if (p1->x > p1->w) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector4 newPoint;

                float t0 = p0->w - p0->x;
                float t1 = p1->w - p1->x;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.x = newPoint.w;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector4 newPoint;

                float t0 = p0->w - p0->x;
                float t1 = p1->w - p1->x;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.x = newPoint.w;

                output[index] = *p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
static inline void ClipPoligonDownClipSpace(Vector4* input, Vector4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector4* p0 = &input[initCount - 1];
    if (p0->y < -p0->w) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector4* p1 = &input[i];
        if (p1->y < -p1->w) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector4 newPoint;

                float t0 = p0->w + p0->y;
                float t1 = p1->w + p1->y;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.y = -newPoint.w;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector4 newPoint;

                float t0 = p0->w + p0->y;
                float t1 = p1->w + p1->y;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.y = -newPoint.w;

                output[index] = *p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
static inline void ClipPoligonUpClipSpace(Vector4* input, Vector4* output, int* vertexCount)
{
    int flags = 0;
    int index = 0;
    int initCount = *vertexCount;
    int finalCount = 0;

    Vector4* p0 = &input[initCount - 1];
    if (p0->y > p0->w) flags += 2;

    for (int i = 0; i < initCount; i++)
    {
        flags >>= 1;

        Vector4* p1 = &input[i];
        if (p1->y > p1->w) flags += 2;

        switch (flags)
        {
            case 0:
            {
                output[index] = *p0; index++;

                finalCount += 1;

                break;
            }
            case 1:
            {
                Vector4 newPoint;

                float t0 = p0->w - p0->y;
                float t1 = p1->w - p1->y;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.y = newPoint.w;

                output[index] = newPoint; index++;

                finalCount += 1;

                break;
            }
            case 2:
            {
                Vector4 newPoint;

                float t0 = p0->w - p0->y;
                float t1 = p1->w - p1->y;

                float t = t0 / (t0 - t1);

                newPoint = Vector4Lerp(*p0, *p1, t);
                newPoint.y = newPoint.w;

                output[index] = *p0;       index++;
                output[index] = newPoint; index++;

                finalCount += 2;

                break;
            }
            default:
            {
                break;
            }
        }

        p0 = p1;
    }

    *vertexCount = finalCount;
}
static inline void ClipPoligonClipSpaceDiv(Vector4* vs, int vertexCount)
{
    for (int i = 0; i < vertexCount; i++)
    {
        vs[i].x /= vs[i].w;
        vs[i].y /= vs[i].w;
        vs[i].z /= vs[i].w;

        // linear interpolation, in clipping, accumulates error
        // values, in NDC, can become slightly outside
        // duno what to do about that, I just clamp them
        vs[i].x = MathClamp(vs[i].x, -1, +1);
        vs[i].y = MathClamp(vs[i].y, -1, +1);
        vs[i].z = MathClamp(vs[i].z, -1, +1);
    }
}
