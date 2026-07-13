#include "../renderer.h"
#include "../math3d.h"

#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define STAR_COUNT 500

typedef struct
{
    Vec3 pos;
} Star;

static Star stars[STAR_COUNT];

static float randf(float min, float max)
{
    return min + ((float)rand() / RAND_MAX) * (max - min);
}

static void respawn(int i)
{
    stars[i].pos = vec3(
        randf(-40.0f, 40.0f),
        randf(-20.0f, 20.0f),
        80.0f
    );
}

void starfield_demo(void)
{
    RendererSize size = renderer_size();

    srand((unsigned)time(NULL));

    for (int i = 0; i < STAR_COUNT; i++)
    {
        stars[i].pos = vec3(
            randf(-40.0f, 40.0f),
            randf(-20.0f, 20.0f),
            randf(1.0f, 80.0f)
        );
    }

    while (1)
    {
        renderer_clear();

        for (int i = 0; i < STAR_COUNT; i++)
        {
            stars[i].pos.z -= 0.6f;

            if (stars[i].pos.z <= 0.1f)
            {
                respawn(i);
            }

            ScreenPoint p = project(
                stars[i].pos,
                55.0f,
                1.0f,
                size.width,
                size.height
            );

            if (p.x < 0 || p.x >= size.width)
                continue;

            if (p.y < 0 || p.y >= size.height)
                continue;

            char ch;
            WORD color;

            if (stars[i].pos.z > 60.0f)
            {
                ch = '.';
                color = FOREGROUND_BLUE;
            }
            else if (stars[i].pos.z > 40.0f)
            {
                ch = '*';
                color = FOREGROUND_BLUE |
                        FOREGROUND_GREEN;
            }
            else if (stars[i].pos.z > 20.0f)
            {
                ch = 'o';
                color = FOREGROUND_RED |
                        FOREGROUND_GREEN |
                        FOREGROUND_BLUE;
            }
            else
            {
                ch = '@';
                color = FOREGROUND_RED |
                        FOREGROUND_GREEN |
                        FOREGROUND_BLUE |
                        FOREGROUND_INTENSITY;
            }

            renderer_put(
                p.x,
                p.y,
                ch,
                color
            );
        }

        renderer_present();

        Sleep(16);
    }
}