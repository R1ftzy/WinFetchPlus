#include <stdio.h>
#include <windows.h>
#include "hardware.h"
#include "sysinfo.h"
#include "memory.h"
#include "gpu.h"
#include "battery.h"

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

int main(){
  SetConsoleOutputCP(CP_UTF8);
  printf("╔═══════════╤═══%s@%s═══════════════╗\n", get_user(), get_hostname());
  printf("  Model     │ %s\n", get_device_clean());
  printf("╠═══════════╪═══════════════════════════════════════╣\n");
  printf("  OS        │ %s\n", get_os_clean());
  printf("  Shell     │ %s\n", get_shell());
  printf("  Terminal  │ %s\n", get_terminal());
  printf("╠═══════════╪═══════════════════════════════════════╣\n");
  printf("  CPU       │ %s (%s)\n", get_cpu(), get_logical_cores());
  printf("  Arch      │ %s\n", get_architecture());
  printf("  Display   │ %s@%shz\n", get_resolution_primary(), get_refresh_rate());
  printf("  Memory    │ %s/%s (free)\n", get_ram_available(), get_ram_total());
  printf("  GPU       │ %s\n", gpuName());
  printf("  VRAM      │ %.2f GiB (total)\n", vramSpecs());
  printf("╠═══════════╪═══════════════════════════════════════╣\n");
  printf("  Battery   │ %s (%s) @ %s\n", get_battery_percentage(), get_battery_status(), get_battery_rate());
  printf("╚═══════════╧═══════════════════════════════════════╝\n");

}
