#include<stdio.h>
#include <stdlib.h>
#include <string.h>

int Total_Count=0;
int End_Word_Count=0;

//Creating Structure
struct Struct_Keywords
{
	char KeyWords[25];
	int Rep_Count;
};
//Function to Initialise Table:
void init_table(struct Struct_Keywords KeyWords_Array[], char KeyWords[])
{
	int i = 0;
	for(i=0; i<Total_Count;++i)
	{
		if(!strcmp(KeyWords_Array[i].KeyWords,KeyWords))
		{
			KeyWords_Array[i].Rep_Count+=1;
		}
	}
	if(End_Word_Count==0)
	{
		strcpy(KeyWords_Array[Total_Count].KeyWords, KeyWords);
		KeyWords_Array[Total_Count].Rep_Count=0;
		Total_Count+=1;
	}

}
//Displaying Similar keyWord Count##
void display_table(struct Struct_Keywords KeyWords_Array[])
{
	for(int i=0;i<Total_Count;++i)
	{
		printf("%s:%d\n", KeyWords_Array[i].KeyWords, KeyWords_Array[i].Rep_Count);
	}	

}
//Main Method
int main(int argc, char *argv[])
{
	//initial WordCount
		struct Struct_Keywords KeyWords_Array[100];
	//Initialize Loop Variable
	int i;
	//Initializing Variable to store Words from the message.
	char *InputMessage_Words;
	for (int i=1;i<argc;++i)
	{
		init_table(KeyWords_Array, argv[i]);
	}
	End_Word_Count=1;
	char *InputMessage;
	char Words[25];
	size_t len = 248;
	int bytes_read = 0;
	InputMessage = (char *) malloc(sizeof(char) * len);
	printf("Enter Message to search for Similar Words: ");

	//Input Message Using GetLine KeyWord

	getline(&InputMessage, &len, stdin);
	InputMessage_Words = strtok(InputMessage, " ");

	//iterating through Message if it is not NULL and calling init_Table Function.

	while(InputMessage_Words != NULL)
	{
		init_table(KeyWords_Array,InputMessage_Words);
		InputMessage_Words = strtok(NULL, " ");
	}
	//Calling Display function to Printout Similar words count.
	display_table(KeyWords_Array);

}

