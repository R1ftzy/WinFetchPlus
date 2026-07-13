#ifndef MATH3D_H
#define MATH3D_H

typedef struct
{
    float x;
    float y;
    float z;
} Vec3;

Vec3 vec3(float x, float y, float z);

Vec3 rotate_x(Vec3 p, float angle);
Vec3 rotate_y(Vec3 p, float angle);
Vec3 rotate_z(Vec3 p, float angle);

typedef struct{
    int x;
    int y;
    float depth;
} ScreenPoint;

ScreenPoint project(Vec3 p, float fov, float distance, int width, int height);

#endif
