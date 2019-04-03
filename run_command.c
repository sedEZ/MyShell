/*
 * run_command.c :    do the fork, exec stuff, call other functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include "shell.h"

static int whether_background;
static int current_child_pid=0;
void run_command(char **myArgv) {
    pid_t pid;
    int stat;

    /* Set the initial child pid to be the parent's pid , it will increased via the running of myshell */
    if(current_child_pid==0)
	    current_child_pid = getpid();

    /* Check if it's mean to run in background */
    whether_background = is_background(myArgv);

    /* Create a new child process.*/
    pid = fork();    

    switch (pid) {

        /* Error. */
        case -1 :
            perror("fork");
            exit(errno);

        /* Parent. */
        default :
	    /* Set target child's pid , or the pid of last child process which argument line had a '&' in it would be revieved by waitpid(-1,&stat,0) */
	    current_child_pid++;

	    /* If myArgv has '&' in arguments,no waiting. */
	    if(whether_background == TRUE)
	    	return;
	    

	    /* Wait for child to terminate.*/
	    waitpid(current_child_pid,&stat,0);
	    whether_background = FALSE;
	    /*Exit state*/
	    if (WIFEXITED(stat)) {
    		int exit_stat = WEXITSTATUS(stat);
		printf("Exit state : %d\n",exit_stat);
	    }

            return;

        /* Child. */
        case 0 :
	    
            /* Run command in child process. */
	    if(!is_builtin(myArgv[0]))
	    	execvp(myArgv[0],myArgv);
            /* Handle error return from execvp */
		exit(errno);
    }
}
