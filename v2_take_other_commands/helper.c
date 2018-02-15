#include "shell.h"
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

int client_mode()
{
  int sock = 0;
  struct sockaddr_in serv;

  if ((sock = socket (AF_INET, SOCK_STREAM, 0)) < 0)
    err_handle("socket");

  printf("client-side socket success\n");

  serv.sin_family = AF_INET;
  serv.sin_port = htons(PORT);
  serv.sin_addr.s_addr = inet_addr(IP);

  if (connect (sock, (struct sockaddr *) &serv, sizeof(serv)) < 0) 
    err_handle("client-side connection");

  printf("connected to server\n");
  return (sock);
}
