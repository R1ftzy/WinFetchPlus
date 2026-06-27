#include "hardware.h"
#include "sysinfo.h"

int main(){
  printf("==================SYSTEM==================\n");
  printf("Host:     %s@%s\n", get_user(), get_hostname());
  printf("Model:    %s\n", get_device_clean());
  printf("OS:       %s\n", get_os());
  printf("Shell:    %s\n", get_shell());
  printf("Terminal: %s\n", get_terminal());
  printf("====================CPU===================\n");
  printf("CPU: %s (%s)\n", get_cpu(), get_logical_cores());
  printf("Architecture: %s\n", get_architecture());
}