/*
Copyright (c) 2018 Ewan Hayes

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#ifdef MATRIX_USE_DEGREES
inline float __deg_to_rad(float deg)
{
	const float MY_PI = 3.14159265359f;
	return (deg/180.0f)*MY_PI;
}
#endif

typedef float mat4[4][4];

inline void mat4_identity(mat4 o)
{
	o[0][0] = 1.0f; o[0][1] = 0.0f; o[0][2] = 0.0f; o[0][3] = 0.0f;
	o[1][0] = 0.0f; o[1][1] = 1.0f; o[1][2] = 0.0f; o[1][3] = 0.0f;
	o[2][0] = 0.0f; o[2][1] = 0.0f; o[2][2] = 1.0f; o[2][3] = 0.0f;
	o[3][0] = 0.0f; o[3][1] = 0.0f; o[3][2] = 0.0f; o[3][3] = 1.0f;
}

inline void mat4_mul(mat4 A, mat4 B, mat4 o)
{
	mat4 tmp;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tmp[i][j] = 0.0f;
			for (int k = 0; k < 4; k++) {
				tmp[i][j] += A[i][k]*B[k][j];
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			o[i][j] = tmp[i][j];
		}
	}
}

inline void mat4_perspective(float fov, float aspect, float znear, float zfar, mat4 o)
{
	identity(o);

	float zrange = znear - zfar;

	float half_fov = fov/2.0f;

	#ifdef MATRIX_USE_DEGREES
	half_fov = __deg_to_rad(half_fov);
	#endif

	float thf = tanf(half_fov);

	o[0][0] = 1.0f/(thf*aspect);
	o[1][1] = 1.0f/thf;
	o[2][2] = (-znear - zfar)/zrange;
	o[2][3] = (2.0f*zfar*znear)/zrange;
	o[3][2] = 1.0f;
	o[3][3] = 0.0f;
}

inline void mat4_translate(mat4 M, float x, float y, float z, mat4 o)
{
	mat4 n;
	identity(n);

	n[0][3] = x;
	n[1][3] = y;
	n[2][3] = z;

	mul(M, n, o);
}

inline void mat4_rotate(mat4 M, float x, float y, float z, mat4 o)
{
#ifdef MATRIX_USE_DEGREES
	x = __deg_to_rad(x);
	y = __deg_to_rad(y);
	z = __deg_to_rad(z);
#endif

	float sinx = sinf(x);
	float cosx = cosf(x);

	float siny = sinf(y);
	float cosy = cosf(y);

	float sinz = sinf(z);
	float cosz = cosf(z);

	mat4 rx;
	identity(rx);
	rx[1][1] =  cosx;
	rx[1][2] = -sinx;
	rx[2][1] =  sinx;
	rx[2][2] =  cosx;

	mat4 ry;
	identity(ry);
	ry[0][0] =  cosy;
	ry[0][2] =  siny;
	ry[2][0] = -siny;
	ry[2][2] =  cosy;

	mat4 rz;
	identity(rz);
	rz[0][0] =  cosz;
	rz[0][1] = -sinz;
	rz[1][0] =  sinz;
	rz[1][1] =  cosz;

	mul(M, rx, o);
	mul(o, ry, o);
	mul(o, rz, o);
}

inline void mat4_scale(mat4 M, float x, float y, float z, mat4 o)
{
	mat4 n;
	identity(n);

	n[0][0] = x;
	n[1][1] = y;
	n[2][2] = z;

	mul(M, n, o);
}
