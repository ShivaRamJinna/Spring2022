#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

//Functions File
//#include "inBuiltFunctions.h"

//Array Size
#define cmd_len 256
#define no_of_args 16

//Global Variables
char InputString[cmd_len];//Input String.
char* Parsed[no_of_args];
int flag;

//Functions
int builtInCommands(char **postParse);
void ProcessInput(char* str, char** postParse);



/*
FUNCTIONS
*/
void Help()
{
	printf("***************************\n");
	printf("List of Commands Supported:\n"
		   "***************************\n"
		   "\tlist – list all the files in the current directory.\n"
		   "\tcd <directory> – change the current directory to the <directory>.\n"
		   "\thelp – display the internal commands and a short description on how to use them\n"
		   "\tquit – quit the shell program.\n");
	printf("***************************\n");

}

void hello()
{
	printf("Hello World!\n");
}

void fibonacci()
{
	//Implement if argv == 1 -> Fibonacci no args
			  //Else if argv == 2 -> Fibonacci with args 
	int n, i;
	int n1 = 0, n2 = 1, next = n1+n2;
	printf("How many elements you want to display:\t");
	scanf("%d", &n);
	if(n<0)
	{
		printf("Invalid input\n");
		return;
	}
	else
	{
		printf("The first %d values: %d, %d",n , n1, n2);
		for (i = 3; i <= n; ++i)
		{
		    printf(",%d ", next);
		    n1 = n2;
		    n2 = next;
		    next = n1 + n2;
  		}
  		return;
	}
	printf("\n");
}
/*
int fibonacci_Args(char **postParse)
{
	int n = atoi(postParse);	
	if (n<=1)
	{
        return n;
	}
	else
	{
    	return fibonacci_Args(n - 1) + fibonacci_Args(n - 2);
    }
}
*/
////////////////

//Main Function---------------
int main(int argc, char const *argv[])
{
	while(1)
	{
		ProcessInput(InputString, Parsed);

	}
	return 0;
}

int builtInCommands(char **postParse)
{
	if(!strcmp("quit", postParse[0]))
	{
		exit(0);
		return 0;
	}
	else if(!strcmp("help", postParse[0]))
	{
		Help();
		return 0;
	}
	else if(!strcmp("hello", postParse[0]))
	{
		hello();
		return 0;
	}
	/*
	else if(!strcmp("fibonacci", postParse[0]))
	{
		size_t lenofArray = strlen(postParse);
		if(lenofArray > 1)
		{
			fibonacci_Args(postParse[1]);
		}
		else 
		{
			fibonacci();
		}
		return 0;
	}
	*/
	else
	{
		printf("Not A Built-in Command, proceeding system Command\n");
		return 1;
	}

}

void systemCommands(char **postParse)
{
	pid_t pid = fork();
	if(pid == 0)
	{
		execvp(postParse[0], postParse);
		printf("execvp failed\n");
		perror("execvp");
	}
	else if(pid > 0)
	{
		printf("Wait for Command to execute");
	}
	else
	{
		perror("fork");
	}
}

void ProcessInput(char* str, char** postParse)  
{
	//Takes Input from "uab_sh >"and assigns it to Char Args
	char* Buffer = readline("uab_sh >");
	if(strlen(Buffer) > 0)
	{
		strcpy(Buffer, str);  
	}
	int i;
	for (i = 0; i < no_of_args; i++)
	{
		//split Input string into tokens and store it in "postparse"
		//postParse[i] = strsep(&Args, " ");
		postParse[i] = strtok(str, " "); 
		/*
		if(postParse[i] == NULL)//check if input is NULL, exit program
		{
			break;
		}
		*/
		if(strlen(postParse[i]) == 0)//if parsing fails, repeat the same iteration.
			i--;
	}

	//Run Built-in Commands
	
	flag = builtInCommands(postParse);
	if(flag == 1)
	{
		systemCommands(postParse);
	}
}
