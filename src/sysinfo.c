#include <windows.h>
#include <string.h>

char* get_os(){
  HKEY hkey;
  static char product[128];
  char build[16];
  DWORD size;

  RegOpenKeyEx(HKEY_LOCAL_MACHINE,
               "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
               0, KEY_READ, &hkey);

  size = sizeof(product);
  RegQueryValueEx(hkey, "ProductName", NULL, NULL, (LPBYTE)product, &size);

  size = sizeof(build);
  RegQueryValueEx(hkey, "CurrentBuildNumber", NULL, NULL, (LPBYTE)build, &size);

  RegCloseKey(hkey);

  if (atoi(build) >= 22000)
    product[9] = '1';

  return product;
}

char* get_os_clean(){
  char *product = get_os();
  product[10] = '\0';
  return product;
}

char* get_user(){
  static char name[64];
  DWORD size = sizeof(name);
  GetUserName(name, &size);
  return name;
}

char* get_hostname(){
  static char name[64];
  DWORD size = sizeof(name);
  GetComputerName(name, &size);
  return name;
}

// char* shell_is_powershell(){
//   HKEY hkey;
//   static char shell[32] = "PowerShell ";
//   char version[16];
//   DWORD size;

//   RegOpenKeyEx(HKEY_LOCAL_MACHINE,
//                "SOFTWARE\\Microsoft\\PowerShellCore\\InstalledVersions\\{GUID}",
//                0, KEY_READ, &hkey);
//   size = sizeof(version);
//   RegQueryValueEx(hkey, "SemanticVersion", NULL, NULL, (LPBYTE)version, &size);
//   RegCloseKey(hkey);
//   strcat(shell, version);
//   return shell;
// }

char* get_shell(){
  if (getenv("PSModulePath"))     
    // return shell_is_powershell(); 
    return "PowerShell";
  else 
    return getenv("ComSpec");
}

char* get_terminal(){
  if (getenv("WT_SESSION"))
    return "Windows Terminal";
  else
    return getenv("TERM_PROGRAM");
}
