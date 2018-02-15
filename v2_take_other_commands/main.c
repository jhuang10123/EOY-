#include "shell.h"

int main ()
{
  int sock = client_mode();
  check_command(sock);
  return 0;
}
