/*
 * is_background.c :  check for & at end
 */

#include <stdio.h>
#include "shell.h"

int is_background(char ** myArgv) {

  	if (*myArgv == NULL)
    		return 0;

  	/* Look for "&" in myArgv, and process it.
  	 *
	 *	- Return TRUE if found.
	 *	- Return FALSE if not found.
	 */
	int i=0;
	while(myArgv[i]!=NULL){
		if(myArgv[i][0]=='&'){
			free(myArgv[i]);			//clean the "&" , or child process would get a wrong argument
			myArgv[i] = NULL;
			return TRUE;	
		}
		i++;
	}
	return FALSE;
}
