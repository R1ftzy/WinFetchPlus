#include "renderer.h"

#include <stdlib.h>
#include <string.h>

static HANDLE hConsole;
static CHAR_INFO *buffer = NULL;

static SMALL_RECT writeRegion;
static COORD bufferSize;
static COORD bufferPos = {0, 0};

static CONSOLE_CURSOR_INFO oldCursor;
static RendererSize size;


void renderer_line(
    int x0,
    int y0,
    int x1,
    int y1,
    char c,
    WORD color){
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;

    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;

    int err = dx + dy;

    while (1){
        renderer_put(x0, y0, c, color);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if (e2 >= dy){
            err += dy;
            x0 += sx;
        }

        if (e2 <= dx){
            err += dx;
            y0 += sy;
        }
    }
}

int renderer_init(void){

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hConsole == INVALID_HANDLE_VALUE)
        return 0;

    CONSOLE_SCREEN_BUFFER_INFO info;
    if (!GetConsoleScreenBufferInfo(hConsole, &info))
        return 0;

    size.width  = info.srWindow.Right  - info.srWindow.Left + 1;
    size.height = info.srWindow.Bottom - info.srWindow.Top + 1;

    bufferSize.X = size.width;
    bufferSize.Y = size.height;

    writeRegion.Left   = 0;
    writeRegion.Top    = 0;
    writeRegion.Right  = size.width - 1;
    writeRegion.Bottom = size.height - 1;

    buffer = (CHAR_INFO *)malloc(sizeof(CHAR_INFO) * size.width * size.height);

    if (!buffer)
        return 0;

    GetConsoleCursorInfo(hConsole, &oldCursor);

    CONSOLE_CURSOR_INFO cursor = oldCursor;
    cursor.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursor);

    renderer_clear();

    return 1;
}

void renderer_put_string(int x, int y, const char *str, WORD color){
    while (*str){
        renderer_put(x++, y, *str++, color);
    }
}

void renderer_shutdown(void){
    SetConsoleCursorInfo(hConsole, &oldCursor);

    if (buffer){
        free(buffer);
        buffer = NULL;
    }
}

void renderer_clear(void){
    int total = size.width * size.height;

    for (int i = 0; i < total; i++){
        buffer[i].Char.AsciiChar = ' ';
        buffer[i].Attributes = FOREGROUND_RED |
                               FOREGROUND_GREEN |
                               FOREGROUND_BLUE;
    }
}

void renderer_put(int x, int y, char c, WORD color){
    if (x < 0 || y < 0)
        return;

    if (x >= size.width || y >= size.height)
        return;

    int idx = y * size.width + x;

    buffer[idx].Char.AsciiChar = c;
    buffer[idx].Attributes = color;
}

void renderer_present(void){
    WriteConsoleOutputA(
        hConsole,
        buffer,
        bufferSize,
        bufferPos,
        &writeRegion
    );
}

RendererSize renderer_size(void){
    return size;
}