#include <string.h>

#include "demo.h"
#include "renderer.h"

#include "demos/cube.h"
#include "demos/starfield.h"

static const Demo demos[] =
{
    { "--cube",      cube_demo },
    { "--starfield", starfield_demo },
};

#define DEMO_COUNT (sizeof(demos) / sizeof(demos[0]))

int run_demo(const char *arg)
{
    for (size_t i = 0; i < DEMO_COUNT; i++)
    {
        if (strcmp(arg, demos[i].flag) == 0)
        {
            if (!renderer_init())
                return 0;

            demos[i].run();

            renderer_shutdown();
            return 1;
        }
    }

    return 0;
}