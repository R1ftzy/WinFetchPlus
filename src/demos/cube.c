#include "../renderer.h"
#include "../math3d.h"

#include <windows.h>

static Vec3 vertices[8] =
{
    {-1,-1,-1},
    { 1,-1,-1},
    { 1, 1,-1},
    {-1, 1,-1},

    {-1,-1, 1},
    { 1,-1, 1},
    { 1, 1, 1},
    {-1, 1, 1}
};

static const int edges[12][2] =
{
    {0,1},
    {1,2},
    {2,3},
    {3,0},

    {4,5},
    {5,6},
    {6,7},
    {7,4},

    {0,4},
    {1,5},
    {2,6},
    {3,7}
};

void cube_demo(void)
{
    RendererSize size = renderer_size();

    float rx = 0.0f;
    float ry = 0.0f;
    float rz = 0.0f;

    while (1)
    {
        renderer_clear();

        ScreenPoint projected[8];

        for (int i = 0; i < 8; i++)
        {
            Vec3 p = vertices[i];

            p = rotate_x(p, rx);
            p = rotate_y(p, ry);
            p = rotate_z(p, rz);

            projected[i] = project(
                p,
                55.0f,
                5.0f,
                size.width,
                size.height
            );
        }

        for (int i = 0; i < 12; i++)
        {
            ScreenPoint a = projected[edges[i][0]];
            ScreenPoint b = projected[edges[i][1]];

            renderer_line(
                a.x,
                a.y,
                b.x,
                b.y,
                '#',
                FOREGROUND_GREEN |
                FOREGROUND_INTENSITY
            );
        }

        renderer_present();

        rx += 0.015f;
        ry += 0.025f;
        rz += 0.010f;

        Sleep(16);
    }
}