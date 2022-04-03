#include<stdio.h>
#include <stdlib.h>
#include <string.h>
int i=0;
//Creating Structure
struct Keyword_Struct
{
	char *KeyWords;
	int Rep_Count;
};
void init_table(struct Keyword_Struct ** KeyWords_Array, char ** argv, int size)
{
	for(i=0; i < size; i++)
	{
		KeyWords_Array[i] = malloc(sizeof(struct Keyword_Struct));
		KeyWords_Array[i] ->KeyWords = argv[i+1];
		KeyWords_Array[i] -> Rep_Count = 0;
	}
}
void Split_Words(char * str, struct Keyword_Struct **KeyWords_Array, int size)
{
	char Delim[]=" ";
		char * InputMessage_Words = strtok(str, Delim);

		while(InputMessage_Words != NULL)
		{
			for(i=0; i < size-1; i++)
			{
				if(strcmp(InputMessage_Words, KeyWords_Array[i]->KeyWords)==0)
				{
					KeyWords_Array[i]->Rep_Count += 1;
				}
			}
			InputMessage_Words = strtok(NULL, Delim);
		}
}
void Display_Count(struct Keyword_Struct** KeyWords_Array, int size)
{

	for(i=0;i<size-1;i++)
	{
		printf("%s:%d\n", KeyWords_Array[i]->KeyWords, KeyWords_Array[i]->Rep_Count);
	}	

}
//Main Method, Program starts here
int main(int argc, char **argv)
{
	
	//Initialize Loop Variable
	int i=0;
	char *line;
	size_t size = 40, getLine = 0; 
	line =(char * ) malloc(size);
	char ** lptr =&line;
	struct Keyword_Struct * KeyWords_Array[argc - 1];
	init_table(KeyWords_Array, argv, argc);
	while(1)
	{
		getLine = getline(lptr, &size, stdin);
		line[strlen(line) -1] = '\0';
		Split_Words(line, KeyWords_Array, argc);
		if (feof(stdin))
		{
      		free(line);
      		break;
    	}
	}
	Display_Count(KeyWords_Array, argc);
	return 0;
}