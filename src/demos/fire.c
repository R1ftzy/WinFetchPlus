#include "../renderer.h"

#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define MAX_W 256
#define MAX_H 128

static unsigned char fire[MAX_H][MAX_W];

static const char palette[] = " .:-=+*#%@";

void fire_demo(void)
{
    RendererSize size = renderer_size();

    int w = size.width;
    int h = size.height;

    if (w > MAX_W) w = MAX_W;
    if (h > MAX_H) h = MAX_H;

    srand((unsigned)time(NULL));

    while (1)
    {
        for (int x = 0; x < w; x++)
            fire[h - 1][x] = 9;

        for (int y = 1; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int src = fire[y][x];

                if (src == 0)
                {
                    fire[y - 1][x] = 0;
                    continue;
                }

                int decay = rand() & 3;
                int dst = x + (rand() % 3) - 1;

                if (dst < 0) dst = 0;
                if (dst >= w) dst = w - 1;

                fire[y - 1][dst] = src > decay ? src - decay : 0;
            }
        }

        renderer_clear();

        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int v = fire[y][x];

                WORD color;

                if (v >= 8)
                    color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
                else if (v >= 6)
                    color = FOREGROUND_RED | FOREGROUND_GREEN;
                else if (v >= 4)
                    color = FOREGROUND_RED | FOREGROUND_INTENSITY;
                else
                    color = FOREGROUND_RED;

                renderer_put(
                    x,
                    y,
                    palette[v],
                    color
                );
            }
        }

        renderer_present();

        Sleep(30);
    }
}