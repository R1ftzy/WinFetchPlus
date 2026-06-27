#include<windows.h>
#include<stdio.h>

char* get_device_clean(){
  HKEY hkey;
  static char device[128];
  DWORD size;

  RegOpenKeyEx(HKEY_LOCAL_MACHINE,
               "HARDWARE\\DESCRIPTION\\System\\BIOS",
               0, KEY_READ, &hkey);

  size = sizeof(device);
  RegQueryValueEx(hkey, "SystemFamily", NULL, NULL, (LPBYTE)device, &size);

  RegCloseKey(hkey);

  return device;
}

char* get_device(){
  HKEY hkey;
  static char device[128];
  DWORD size;

  RegOpenKeyEx(HKEY_LOCAL_MACHINE,
               "HARDWARE\\DESCRIPTION\\System\\BIOS",
               0, KEY_READ, &hkey);

  size = sizeof(device);
  RegQueryValueEx(hkey, "SystemProductName", NULL, NULL, (LPBYTE)device, &size);

  RegCloseKey(hkey);

  return device;
}

char* get_architecture(){
  SYSTEM_INFO si;
  GetSystemInfo(&si);
  if(si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
    return "x86-64";
  else if(si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_INTEL)
    return "x86";
  else if(si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_ARM64)
    return "ARM64";
  else if(si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_ARM)
    return "ARM";
  else 
    return "Unknown Architecture (feel free to add it and contribute)";
}

char* get_logical_cores(){
  SYSTEM_INFO si;
  GetSystemInfo(&si);
  static char lcores[4];
  snprintf(lcores, sizeof(lcores), "%lu", si.dwNumberOfProcessors);
  return lcores;
}

char* get_cpu(){
  HKEY hkey;
  static char cpu[64];
  DWORD size;

  RegOpenKeyEx(HKEY_LOCAL_MACHINE,
               "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
               0, KEY_READ, &hkey);

  size = sizeof(cpu);
  RegQueryValueEx(hkey, "ProcessorNameString", NULL, NULL, (LPBYTE)cpu, &size);

  RegCloseKey(hkey);

  return cpu;
}