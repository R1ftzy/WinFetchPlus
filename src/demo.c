#include <string.h>

#include "demo.h"
#include "renderer.h"

#include "demos/cube.h"

int run_demo(const char *arg)
{
    if (!renderer_init())
        return 0;

    if (strcmp(arg, "--cube") == 0)
    {
        cube_demo();
        renderer_shutdown();
        return 1;
    }

    renderer_shutdown();
    return 0;
}