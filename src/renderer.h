#ifndef RENDERER_H
#define RENDERER_H

#include <windows.h>

typedef struct {
    SHORT width;
    SHORT height;
} RendererSize;

// Initialization 
int renderer_init(void);
void renderer_shutdown(void);

// Frame operations 
void renderer_clear(void);
void renderer_present(void);

// Drawing 
void renderer_put(int x, int y, char c, WORD color);
void renderer_put_string(int x, int y, const char *str, WORD color);
void renderer_line(
    int x0,
    int y0,
    int x1,
    int y1,
    char c,
    WORD color
);

// Utility 
RendererSize renderer_size(void);

#endif