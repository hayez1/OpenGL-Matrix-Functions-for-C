# OpenGL-Matrix-Library

I couldn't find any good matrix libraries written in C so I made this one.

Taken from a project I'm working on.

## Example

```C
#define MATRIX_USE_DEGREES
#include "matrix4.h"

int main(void)
{
  mat4 transform;
  mat4_identity(transform);
  mat4_translate(transform, 2.0f, 3.0f, 4.0f, transform);
  mat4_rotate(transform, 0.0f, 20.0f, 0.0f, transform);
  
  return 0;
}
```

## Using with OpenGL

If you want to store a matrix into a uniform, use:
```C
glUniformMatrix4fv(uniform, 1, true, &matrix[0][0]);
```
As you can see, the matrix must be transposed.

## Functions

```C
void mat4_identity(mat4 o)
```
```C
void mat4_perspective(float fov, float aspect, float znear, float zfar, mat4 o)
```
```C
void mat4_translate(mat4 M, float x, float y, float z, mat4 o)
```
```C
void mat4_rotate(mat4 M, float x, float y, float z, mat4 o)
```
```C
void mat4_scale(mat4 M, float x, float y, float z, mat4 o)
```
```C
void mat4_mul(mat4 A, mat4 B, mat4 o)
```
