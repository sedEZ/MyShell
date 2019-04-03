/*
 * builtin.c : check for shell built-in commands
 * structure of file is
 * 1. definition of builtin functions
 * 2. lookup-table
 * 3. definition of is_builtin and do_builtin
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

/****************************************************************************/
/* builtin function definitions                                             */
/****************************************************************************/

static void bi_echo(char **argv) {
  	if(argv[1][0]=='-'&&argv[1][1]=='n'&argv[1][2]=='\0'){	//check -n existance
		int target_index = atoi(argv[2]);			//target token index
		if(argv[2+target_index])				//if it's not out of argv array
			printf("%s\n",argv[2+target_index]);		//echo it
		return;
	}
	else{
		int i=1;						//counter for argv
		while(argv[i]!=NULL){					//visit through argv
			printf("%s",argv[i]);				//echo it
			if(argv[i+1]!=NULL)
				printf(" ");				//if it's not the last,add space
			i++;				
		}
		printf("\n");
	}
}

static void bi_quit(char **argv){
	int i=0;
	while(argv[i]!=NULL){
		if(i==1&&argv[1]!=NULL)
			printf("%s : illegal argument\n",argv[1]);
		free(argv);
	}
	argv=NULL;
	free(argv);
	exit(0);
}


/****************************************************************************/
/* lookup table                                                             */
/****************************************************************************/

static struct cmd {
	char * keyword;				/* When this field is argv[0] ... */
	void (* do_it)(char **);		/* ... this function is executed. */
} inbuilts[] = {	
	{ "exit", bi_quit },
	{ "bye", bi_quit },
	{ "logout", bi_quit },
	{ "quit", bi_quit },
	{ "echo", bi_echo },			/* When "echo" is typed, bi_echo() executes.  */
	{ NULL, NULL }				/* NULL terminated. */
};




/****************************************************************************/
/* is_builtin and do_builtin                                                */
/****************************************************************************/

static struct cmd * this; 		/* close coupling between is_builtin & do_builtin */

/* Check to see if command is in the inbuilts table above.
 * Hold handle to it if it is. 
 */

int is_builtin(char *cmd) {
  	struct cmd *tableCommand;

  	for (tableCommand = inbuilts ; tableCommand->keyword != NULL; tableCommand++)
    		if (strcmp(tableCommand->keyword,cmd) == 0) {
			this = tableCommand;
			return 1;
		}
  	return 0;
}


/* Execute the function corresponding to the builtin cmd found by is_builtin. */
int do_builtin(char **argv) {
  	this->do_it(argv);
}
