#include <windows.h>
#include <stdio.h>
#define BtoGiB (1024*1024*1024)

char* get_ram_available(){
  MEMORYSTATUSEX mem;
  mem.dwLength = sizeof(mem);  
  static char free[64];
  GlobalMemoryStatusEx(&mem);
  snprintf(free, sizeof(free), "%.2f GiB", (float)mem.ullAvailPhys / BtoGiB);
  return free;
}

char* get_ram_total(){
  MEMORYSTATUSEX mem;
  mem.dwLength = sizeof(mem);  
  static char total[64];
  GlobalMemoryStatusEx(&mem);
  snprintf(total, sizeof(mem), "%.2f GiB", (float)mem.ullTotalPhys / BtoGiB);
  return total;
}

char* get_ram_used(){
  MEMORYSTATUSEX mem;
  mem.dwLength = sizeof(mem);  
  static char used[64];
  GlobalMemoryStatusEx(&mem);
  snprintf(used, sizeof(used), "%.2f GiB", (float)(mem.ullTotalPhys - mem.ullAvailPhys) / BtoGiB);
  return used;
}