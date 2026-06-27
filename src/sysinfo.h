#ifndef SYSINFO_H
#define SYSINFO_H

#include <windows.h>
#include <stdio.h>

char* get_os();

char* get_os_clean();

char* get_user();

char* get_hostname();

char* get_shell();

char* get_terminal();

#endif