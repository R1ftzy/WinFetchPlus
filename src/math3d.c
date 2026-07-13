#include "math3d.h"
#include <math.h>

Vec3 vec3(float x, float y, float z)
{
    Vec3 v = {x, y, z};
    return v;
}

Vec3 rotate_x(Vec3 p, float a)
{
    float c = cosf(a);
    float s = sinf(a);

    return vec3(
        p.x,
        p.y * c - p.z * s,
        p.y * s + p.z * c
    );
}

Vec3 rotate_y(Vec3 p, float a)
{
    float c = cosf(a);
    float s = sinf(a);

    return vec3(
        p.x * c + p.z * s,
        p.y,
        -p.x * s + p.z * c
    );
}

Vec3 rotate_z(Vec3 p, float a)
{
    float c = cosf(a);
    float s = sinf(a);

    return vec3(
        p.x * c - p.y * s,
        p.x * s + p.y * c,
        p.z
    );
}

ScreenPoint project(Vec3 p, float fov, float distance, int width, int height)
{
    ScreenPoint s;

    float z = p.z + distance;

    if (z <= 0.01f)
    {
        s.x = -1;
        s.y = -1;
        s.depth = 0.0f;
        return s;
    }

    float inv = fov / z;

    s.x = (int)(width * 0.5f + p.x * inv);
    s.y = (int)(height * 0.5f - p.y * inv);
    s.depth = inv;

    return s;
}