#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 64
#define PATH_MAX 1024
#define PARAM_MAX 128

int main(int argc, char * argv[])
{
	char *saveptr;
	char cwd[(int) PATH_MAX]; // current working directory
	char user_str[(int) BUFF_SIZE]; // raw user input
	char *command[(int) PARAM_MAX]; // tokenized user input
	int i, len, param_count;	
	
	do
	{
		getcwd(cwd, (int) PATH_MAX);
	
		if (ERANGE == errno)
		{	
			perror("getcwd() error");
			/* how should this be handled? */
		}
	 
	
		printf("\n%s%%  ", cwd);
		fgets(user_str, (int) BUFF_SIZE, stdin);
		// need to handle buffer overflow
		
		// strip newline char and add terminating null char
		len = strlen(user_str);
		if ('\n' == *(user_str+len-1))
		{
			*(user_str+len-1) = '\0';
		}
		
		// split user input up into parameters
		param_count = tokenizeIntoArray(user_str, command, (int) PARAM_MAX, " ");
		
		// handle internal commands and anything else is a system call 
		if (0 == strcmp(*(command), "cd"))
		{
			int success = chdir(*(command+1));
			
			if(ENOENT == errno)
			{
				perror("chdir() error");
				errno = 0;
			}	
		}
		
		else
		{	
			// fork and exec command
			runProc(command, param_count);
		}

	} while(strcmp(user_str, "exit") != 0);

	return 0;
}

/* tokenizes str and stores token strings in bufArr        */
/* returns size of filled bufArr (number of token strings) */
int tokenizeIntoArray(char *str, char** buf_arr, const int buf_arr_size, const char* delim)
{
	int i;
	char *token = NULL;
	char *saveptr = NULL;
	
	token = strtok_r(str, delim, &saveptr);
	i = 0;
	while ((NULL != token) && (i < buf_arr_size))
	{
		*(buf_arr+i) = token;
		token = strtok_r(NULL, delim, &saveptr);
		i++;
	}	
	*(buf_arr+i) = NULL;
	return i;	
}


