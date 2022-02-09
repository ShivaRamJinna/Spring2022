#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include <string.h>
#define buffLen 1000

int main(int argc, char const *argv[])
{
	char LineBuffer[buffLen];

	//Verify no.of args provided is 3 
	if (argc != 3)
	{
		printf("Invalid File Names");
	}
	if (argv[1] == argv[2])
	{
		printf("Invalid File Names");
	}	
	FILE *fileOne = fopen(argv[1], "a");	
	FILE *fileTwo = fopen(argv[2], "r");
	if(fileOne == NULL || fileTwo == NULL)
	{
		printf("Unable to open File");
	}
	while(fgets(LineBuffer, buffLen, fileTwo))
	{
		fputs(LineBuffer, fileOne);
		//printf("%s", LineBuffer);
	}
	fclose(fileOne);
	fclose(fileTwo);

	return 0;
}