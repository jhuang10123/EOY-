#include "shell.h"
#include <string.h>
#include <signal.h>

/* sighandler is wrong. need to fix */
/* currently prints out fgets string issues(L31) with ctrl+D & exits*/
void sighandler(int sig)
{
  (void)sig;
  return;
}

/**
 * check_command - searches for command and finds it's corresponding fcn
* @cmd: string to be checked
* Return: 0 if command found, else 1.
*/
int check_command(int fd)
{
  int i = 0;
  char cmd[200];
  int test = 0;

  printf("in check_command\n");

  /* redirect fd */
  dup2 (fd, 0);
  dup2 (fd, 1);
  dup2 (fd, 2);

  printf("redirected fd\n");
  while(1){
    printf("----->Please enter a command:\n");
    if (fgets(cmd, 200, stdin) == NULL)
      err_handle("fgets string issues");
    else
      {
	printf("Command entered: %s", cmd);

	command_t list[] = {
	  {"SHELL", spawn_shell},
	  {"test", test_str}, /* need to change back to uppercase */
	  {"SHUTDOWN", shutdown},
	  {NULL, NULL}
	};

	for (i = 0; list[i].command != NULL; i++)
	  {	  
	    printf("Inside 1st forloop. cmd = %s. list[i].command = %s\n", cmd, list[i].command);
	    test = strcmp(cmd, list[i].command);
	    printf("Strcmp result: %d\n", test);
	    if (test == 0) 
	      {
		list[i].f(fd);
		printf("inside strcmp ==0 \n");
	      }
	    else
		printf("----->Current avail commands: \"SHELL\", \"TEST\", \"SHUTDOWN\"\n"); 
	  }
	memset(cmd, '\0', 200);
      }
  }
  free(cmd);
  return (0);
}

/**
 *
 */
int spawn_shell(int fd)
{
  (void)fd;
  char *shell[3] ;
  pid_t pid = 0;
  int status = 0;

  signal(SIGQUIT, sighandler);
  
  /* fill in shell */
  shell[0] = "/bin/sh";
  shell[1] = "-i";
  shell[2] = NULL;

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
  return(0);
}

/**
 *
 */
int test_str(int fd)
{
  (void)fd;
  printf("Testing string: success\n");
  return (0);
}

/**
 *
 */
int _shutdown(int fd)
{
  (void)fd;
  printf("Shutting down...\n");
  sleep(4);
  /* replace () */
  system("sudo shutdown -h now");
  return (0);
}

/**
 *
 */



          /* Testing output: */
          /* CLIENT-SIDE: */
/* client-side socket success */
/* connected to server */
/* in check_command */

          /* -----WEB1 SERVER SIDE -----*/
          /* -----TESTING WITH "SHELL" -----*/
/* ubuntu@133-web-01:~$ nc -l -p 9090 */
/* redirected fd */
/* ----->Please enter a command: */
/* SHELL */
/* Command entered: SHELL */
/* Inside 1st forloop. cmd = SHELL */
/* . list[i].command = SHELL */
/*   Strcmp result: 10 */
/*   ----->Current avail commands: "SHELL", "TEST", "SHUTDOWN" */
/* Inside 1st forloop. cmd = SHELL */
/* . list[i].command = test */
/*   Strcmp result: -33 */
/*   ----->Current avail commands: "SHELL", "TEST", "SHUTDOWN" */
/* Inside 1st forloop. cmd = SHELL */
/* . list[i].command = SHUTDOWN */
/*   Strcmp result: -16 */
/*   ----->Current avail commands: "SHELL", "TEST", "SHUTDOWN" */


/*           /\*-----TESTING WITH "test" on lower case -----*\/ */
/* ----->Please enter a command: */
/* test */
/* Command entered: test */
/* Inside 1st forloop. cmd = test */
/* . list[i].command = SHELL */
/*   Strcmp result: 33 */
/*   ----->Current avail commands: "SHELL", "TEST", "SHUTDOWN" */
/* Inside 1st forloop. cmd = test */
/* . list[i].command = test */
/*   Strcmp result: 10 */
/*   ----->Current avail commands: "SHELL", "TEST", "SHUTDOWN" */
/* Inside 1st forloop. cmd = test */
/* . list[i].command = SHUTDOWN */
/*   Strcmp result: 33 */
/*   ----->Current avail commands: "SHELL", "TEST", "SHUTDOWN" */
/*   ----->Please enter a command: */
/* ^C */
/*   ubuntu@133-web-01:~$  */


/* need to handle enter */
/*           /\*-----TESTING WITH RETURN-----*\/ */
/*   ----->Please enter a command: */

/*   Command entered: */
/* Inside 1st forloop. cmd = */
/* . list[i].command = SHELL */
/*   Strcmp result: -73 */
/*   ----->Current avail commands: "SHELL", "TEST", "SHUTDOWN" */
/* Inside 1st forloop. cmd = */
/* . list[i].command = test */
/*   Strcmp result: -106 */
/*   ----->Current avail commands: "SHELL", "TEST", "SHUTDOWN" */
/* Inside 1st forloop. cmd = */
/* . list[i].command = SHUTDOWN */
/*   Strcmp result: -73 */
/*   ----->Current avail commands: "SHELL", "TEST", "SHUTDOWN" */



/* fix sighandler */
/*   /\*-----TESTING WITH CTRL+D-----*\/ */
/*   ----->Please enter a command: */
/*   fgets string issues: Success */
/*   ubuntu@133-web-01:~$ */
