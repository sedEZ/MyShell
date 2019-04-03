/*
 * parse.c : use whitespace to tokenise a line
 * Initialise a vector big enough
 */
#define MAX_TOKEN 255 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"shell.h"

//void copy(char*,const char*);

/* Parse a commandline string into an argv array. */
char ** parse(char *line) {

  	static char delim[] = " \t\n"; /* SPACE or TAB or NL */
  	int count = 0;
  	char * token;
  	char **newArgv;		/*??????????????????????????????????????????*/

  	/* Nothing entered. */
  	if (line == NULL) {					
    		return NULL;
  	}

  	/* Init strtok with commandline, then get first token.
     	 * Return NULL if no tokens in line.
         */
	
	token = strtok(line,delim);						//get first token

	if(token == (char*)NULL)
		return (char**)NULL;						//if no token there,return null


	/* Create array with room for first token.*/
	newArgv = (char **)malloc(sizeof(char*)+1);				//init newArgv
	count++;								//add first token,so increase count
	char* temp = (char*)malloc(MAX_TOKEN);
	newArgv[count-1] = temp;						//space for token
	memcpy(newArgv[count-1],token,MAX_TOKEN);				//put it in
	printf("[%d] : %s\n",count-1,newArgv[count-1]);				//check content

  	/* While there are more tokens...
	 *
	 *  - Get next token.
	 *	- Resize array.
	 *  - Give token its own memory, then install it.
	 */
	while(token = strtok(NULL,delim)){
		//count++;							//increase # of tokens
		newArgv = (char **)realloc(newArgv,(count++)*sizeof(char*)+1);	//resize
		temp = (char*)malloc(MAX_TOKEN);
		newArgv[count-1] = temp;					//request a space for new token	
		memcpy(newArgv[count-1],token,MAX_TOKEN);			//put it in
		printf("[%d] : %s\n",count-1,newArgv[count-1]);			//check content
	}

	newArgv = (char **)realloc(newArgv,count*sizeof(char*)+1);		//space for last element
	newArgv[count]=NULL;							//null the end of newArgv
  	return newArgv;
}


/*
 * Free memory associated with argv array passed in.
 * Argv array is assumed created with parse() above.
 */
void free_argv(char **oldArgv) {

	int i = 0;								//index of oldArgv

	/* Free each string hanging off the array.
	 * Free the oldArgv array itself.
	 */
	while(oldArgv[i]){						//visit through oldArgv
		free(oldArgv[i]);					//free stirng pointer
		i++;
	}
		
	free(oldArgv);							//free oldArgv
}
