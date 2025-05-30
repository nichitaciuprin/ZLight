#pragma once

#include "BaseMath.h"

inline bool operator == (Vector2 l, Vector2 r) { return Vector2Equal(l, r); }
inline bool operator == (Vector3 l, Vector3 r) { return Vector3Equal(l, r); }
inline bool operator == (Vector4 l, Vector4 r) { return Vector4Equal(l, r); }

inline Vector2 operator - (Vector2 r) { return Vector2Neg(r); }
inline Vector3 operator - (Vector3 r) { return Vector3Neg(r); }
inline Vector4 operator - (Vector4 r) { return Vector4Neg(r); }

inline Vector2 operator + (Vector2 l, Vector2 r) { return Vector2Add(l, r); }
inline Vector3 operator + (Vector3 l, Vector3 r) { return Vector3Add(l, r); }
inline Vector4 operator + (Vector4 l, Vector4 r) { return Vector4Add(l, r); }

inline Vector2 operator - (Vector2 l, Vector2 r) { return Vector2Sub(l, r); }
inline Vector3 operator - (Vector3 l, Vector3 r) { return Vector3Sub(l, r); }
inline Vector4 operator - (Vector4 l, Vector4 r) { return Vector4Sub(l, r); }

inline Vector2 operator * (Vector2 l, float r) { return Vector2Mul(l, r); }
inline Vector3 operator * (Vector3 l, float r) { return Vector3Mul(l, r); }
inline Vector4 operator * (Vector4 l, float r) { return Vector4Mul(l, r); }

inline Vector2 operator / (Vector2 l, float r) { return Vector2Div(l, r); }
inline Vector3 operator / (Vector3 l, float r) { return Vector3Div(l, r); }
inline Vector4 operator / (Vector4 l, float r) { return Vector4Div(l, r); }

inline Vector2 operator * (Vector2 v, Matrix m) { return MatrixMultiply2L(v, m); }
inline Vector3 operator * (Vector3 v, Matrix m) { return MatrixMultiply3L(v, m); }
inline Vector4 operator * (Vector4 v, Matrix m) { return MatrixMultiply4L(v, m); }

inline Vector2 operator * (Matrix m, Vector2 v) { return MatrixMultiply2R(m, v); }
inline Vector3 operator * (Matrix m, Vector3 v) { return MatrixMultiply3R(m, v); }
inline Vector4 operator * (Matrix m, Vector4 v) { return MatrixMultiply4R(m, v); }

inline Matrix operator * (Matrix l, Matrix r) { return MatrixMultiply(l, r); }

inline void operator += (Vector2& l, Vector2 r) { l = Vector2Add(l, r); }
inline void operator += (Vector3& l, Vector3 r) { l = Vector3Add(l, r); }
inline void operator += (Vector4& l, Vector4 r) { l = Vector4Add(l, r); }

inline void operator -= (Vector2& l, Vector2 r) { l = Vector2Sub(l, r); }
inline void operator -= (Vector3& l, Vector3 r) { l = Vector3Sub(l, r); }
inline void operator -= (Vector4& l, Vector4 r) { l = Vector4Sub(l, r); }

inline void operator *= (Vector2& l, float r) { l = Vector2Mul(l, r); }
inline void operator *= (Vector3& l, float r) { l = Vector3Mul(l, r); }
inline void operator *= (Vector4& l, float r) { l = Vector4Mul(l, r); }

inline void operator /= (Vector2& l, float r) { l = Vector2Div(l, r); }
inline void operator /= (Vector3& l, float r) { l = Vector3Div(l, r); }
inline void operator /= (Vector4& l, float r) { l = Vector4Div(l, r); }

inline void operator *= (Vector2& v, Matrix m) { v = MatrixMultiply2L(v, m); }
inline void operator *= (Vector3& v, Matrix m) { v = MatrixMultiply3L(v, m); }
inline void operator *= (Vector4& v, Matrix m) { v = MatrixMultiply4L(v, m); }

inline void operator *= (Matrix m, Vector2& v) { v = MatrixMultiply2R(m, v); }
inline void operator *= (Matrix m, Vector3& v) { v = MatrixMultiply3R(m, v); }
inline void operator *= (Matrix m, Vector4& v) { v = MatrixMultiply4R(m, v); }

inline void operator *= (Matrix& l, Matrix r) { l = MatrixMultiply(l, r); }
