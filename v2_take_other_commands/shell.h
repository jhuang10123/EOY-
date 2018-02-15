#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT 9090
#define IP "142.44.167.241"

/**
 * struct command - struct storing commands & fcn pointer
 * @command: command
 * @f: function pointer to command
 */
typedef struct command
{
  char *command;
  int (*f)();
} command_t;

void err_handle(char* s);
int client_mode();
int commandline(int fd);
int spawn_shell(int fd);
int test_str(int fd);
int _shutdown(int fd);
int check_command(int fd);
void sighandler(int sig);

#endif
