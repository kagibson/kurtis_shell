#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>
#include "shell.h"

int runProc(char **command, int param_count)
{
	int ret_code;
	int pid;

	pid = fork();

	if (0 != pid)
	{
		// parent process comes here
		wait(NULL);
	}

	else
	{
		// child process comes here
		ret_code = execvp(*command, command); 
		if(ret_code != 0)
		{
			printf("Error executing %s.\n", *(*command));
		}
	}
	
	return ret_code;
}
