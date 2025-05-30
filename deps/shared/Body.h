#pragma once

#include "BaseMath.h"

void DrawBody1(Bitmap* bitmap, Vector3 footPos, float rotBody)
{
    Vector3 hip     = { 0, 1.10f, 0 };
    Vector3 neck1   = { 0, 1.60f, 0 };
    Vector3 neck2   = { 0, 1.65f, 0 };
    Vector3 h1l     = { -0.15f, 1.55f, 0 };
    Vector3 h1r     = { +0.15f, 1.55f, 0 };
    Vector3 h2l     = { -0.20f, 1.20f, -0.05f };
    Vector3 h2r     = { +0.20f, 1.20f, -0.05f };
    Vector3 h3l     = { -0.30f, 1.00f, +0.20f };
    Vector3 h3r     = { +0.30f, 1.00f, +0.20f };
    Vector3 footl   = { -0.20f, 0, 0 };
    Vector3 footr   = { +0.20f, 0, 0 };
    Vector3 topl    = { -0.10, 1.75f, 0 };
    Vector3 topr    = { +0.10, 1.85f, 0 };

    hip    = Vector3RotateY(hip,   rotBody);
    neck1  = Vector3RotateY(neck1, rotBody);
    neck2  = Vector3RotateY(neck2, rotBody);
    footl  = Vector3RotateY(footl, rotBody);
    footr  = Vector3RotateY(footr, rotBody);
    h1l    = Vector3RotateY(h1l,   rotBody);
    h2l    = Vector3RotateY(h2l,   rotBody);
    h3l    = Vector3RotateY(h3l,   rotBody);
    h1r    = Vector3RotateY(h1r,   rotBody);
    h2r    = Vector3RotateY(h2r,   rotBody);
    h3r    = Vector3RotateY(h3r,   rotBody);
    topl   = Vector3RotateY(topl,  rotBody);
    topr   = Vector3RotateY(topr,  rotBody);

    hip    += footPos;
    neck1  += footPos;
    neck2  += footPos;
    footl  += footPos;
    footr  += footPos;
    h1l    += footPos;
    h2l    += footPos;
    h3l    += footPos;
    h1r    += footPos;
    h2r    += footPos;
    h3r    += footPos;
    topl   += footPos;
    topr   += footPos;

    BitmapDrawLine(bitmap, footl,  hip);
    BitmapDrawLine(bitmap, footr,  hip);
    BitmapDrawLine(bitmap, neck1,  hip);
    BitmapDrawLine(bitmap, neck1,  h1l);
    BitmapDrawLine(bitmap, neck1,  h1r);
    BitmapDrawLine(bitmap, h1l,    h2l);
    BitmapDrawLine(bitmap, h2l,    h3l);
    BitmapDrawLine(bitmap, h1r,    h2r);
    BitmapDrawLine(bitmap, h2r,    h3r);
    BitmapDrawLine(bitmap, topl,   topr);
    BitmapDrawLine(bitmap, neck1,  neck2);
    BitmapDrawLine(bitmap, neck2,  topl);
    BitmapDrawLine(bitmap, neck2,  topr);
}
void DrawBody2(Bitmap* bitmap, Vector3 footPos, float rotBody, float rotHead)
{
    const Matrix scale1 = MatrixScale({ 0.1, 1.75, 0.1 });
    const Matrix scale2 = MatrixScale({ 0.2, 0.2, 0.4 });
    const Matrix trans1 = MatrixTranslate({ 0, 1.75/2, 0 });
    const Matrix trans2 = MatrixTranslate({ 0, 1.70, 0 });
    const Matrix trans3 = MatrixTranslate({ 0, 0, 0.1 });
    const Matrix trans4 = MatrixTranslate(footPos);
    const Matrix rot1 = MatrixRotateY(rotBody);
    const Matrix rot2 = MatrixRotateX(rotHead);

    // body
    {
        Matrix mat = MatrixIdentity();
        mat = MatrixMultiply(mat, scale1);
        mat = MatrixMultiply(mat, rot1);
        mat = MatrixMultiply(mat, trans1);
        mat = MatrixMultiply(mat, trans4);
        BitmapDrawCube2(bitmap, mat);
    }

    // head
    {
        Matrix mat = MatrixIdentity();
        mat = MatrixMultiply(mat, scale2);
        mat = MatrixMultiply(mat, trans3);
        mat = MatrixMultiply(mat, rot2);
        mat = MatrixMultiply(mat, rot1);
        mat = MatrixMultiply(mat, trans2);
        mat = MatrixMultiply(mat, trans4);
        BitmapDrawCube2(bitmap, mat);
    }
}

// const int footmax = 2;
// Vector3 foots[footmax] = {};
// int footi = 0;
// void FootUpdate(Camera* cam)
// {
//     Vector3 pos = cam->position; pos.y = 0;
//     CALLONI(10,
//     {
//         foots[footi] = pos;
//         footi++;
//         if (footi == footmax)
//             footi = 0;
//     })
// }

// void FootDraw(Bitmap* bitmap, Camera* cam)
// {
//     // for (int i = 0; i < footmax; i++)
//     //     BitmapDrawLine(bitmap, cam->position+offset, foots[i]+offset);
//     Vector3 p0 = cam->position; p0.y = 0.80f;
//     Vector3 p1 = cam->position; p1.y = 1.70f;
//     for (int i = 0; i < footmax; i++)
//         BitmapDrawLine(bitmap, p0, foots[i]);
//     BitmapDrawLine(bitmap, p0, p1);
// }
