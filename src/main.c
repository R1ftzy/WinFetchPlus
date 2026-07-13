#include <stdio.h>
#include <windows.h>
#include "display.h"
#include "config.h"
#include "demo.h"
#include <string.h>
#include "demos/cube.h"
#include "renderer.h"

/* some cool unicode shi
  ═
  ╠
  ╪
  ╗
  ╤
  ╣
  │
  ╧
  ╔
  ╗
  ╚
  ╝
*/

int main(int argc, char *argv[]){
  SetConsoleOutputCP(CP_UTF8);
  
  if (argc > 1 && run_demo(argv[1]))
    return 0;

  char exe_dir[MAX_PATH];
  GetModuleFileNameA(NULL, exe_dir, MAX_PATH);
  char* last_slash = strrchr(exe_dir, '\\');
  if (last_slash) *last_slash = '\0';
  char path[MAX_PATH];

  const char* filename = (argc >= 2) ? argv[1] : get_logo();
  snprintf(path, MAX_PATH, "%s\\..\\logos\\%s", exe_dir, filename);

  Block logo = parse_logo(path);
  Block info = get_info();
  Block block = render(logo, info);
  for (size_t i = 0; i < block.count; i++)
  {
    printf("%s\n", block.lines[i]);
  }
}
