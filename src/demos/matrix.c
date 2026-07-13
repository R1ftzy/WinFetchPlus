#include "../renderer.h"

#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define MAX_COLUMNS 256

typedef struct
{
    int head;
    int length;
    int speed;
    int counter;
} RainColumn;

void matrix_demo(void)
{
    RendererSize size = renderer_size();

    RainColumn cols[MAX_COLUMNS];

    srand((unsigned)time(NULL));

    int width = size.width;

    if (width > MAX_COLUMNS)
        width = MAX_COLUMNS;

    for (int i = 0; i < width; i++)
    {
        cols[i].head = rand() % size.height;
        cols[i].length = 5 + rand() % 20;
        cols[i].speed = 1 + rand() % 3;
        cols[i].counter = 0;
    }

    while (1)
    {
        renderer_clear();

        for (int x = 0; x < width; x++)
        {
            RainColumn *c = &cols[x];

            c->counter++;

            if (c->counter >= c->speed)
            {
                c->head++;
                c->counter = 0;
            }

            if (c->head - c->length > size.height)
            {
                c->head = -(rand() % size.height);
                c->length = 5 + rand() % 20;
                c->speed = 1 + rand() % 3;
            }

            for (int i = 0; i < c->length; i++)
            {
                int y = c->head - i;

                if (y < 0 || y >= size.height)
                    continue;

                char ch;

                int r = rand() % 36;

                if (r < 10)
                    ch = '0' + r;
                else
                    ch = 'A' + (r - 10);

                WORD color;

                if (i == 0)
                {
                    color = FOREGROUND_RED |
                            FOREGROUND_GREEN |
                            FOREGROUND_BLUE |
                            FOREGROUND_INTENSITY;
                }
                else if (i < 3)
                {
                    color = FOREGROUND_GREEN |
                            FOREGROUND_INTENSITY;
                }
                else
                {
                    color = FOREGROUND_GREEN;
                }

                renderer_put(x, y, ch, color);
            }
        }

        renderer_present();

        Sleep(35);
    }
}