#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <unistd.h>
#define argSize (argc - 1)


typedef struct
{
	int arg_S, arg_s, arg_f, arg_t, arg_e, arg_E, fileSize;
	char fileFilter[100],  fileType[2], E_Key[1000];
}terminalArgs;


//File Directory --------- 
typedef void FileHandler(char *filePath, char *dirfile, terminalArgs TerArgs, int Count);

void fileDirectory(char *R_Dir, int Count, FileHandler *pAlg, terminalArgs TerArgs)
{
	struct dirent *dirent;
	DIR *rootDir = opendir(R_Dir);

	if(rootDir == NULL)
	{
		printf("Unable to open Directory");
		exit(-1);
	}
	while((dirent = readdir(rootDir)) != NULL)
	{
		if(strcmp((*dirent).d_name, ".") != 0 && strcmp((*dirent).d_name, "..") != 0)
		{
			char f_Path[500];
			strcpy(f_Path,R_Dir);
            strcat(f_Path,"/");
            strcat(f_Path, (*dirent).d_name);
			//File Directory Function
			pAlg(f_Path, (*dirent).d_name, TerArgs, Count);
			if((*dirent).d_type == DT_DIR)
			{
				Count++;
				fileDirectory(f_Path, Count, pAlg, TerArgs);
				Count--;
			}
		}
	}
	closedir(rootDir);
}


//Prasing Aruguments ------------ 
void 
print_Alg(char *filePath, char *dirFile, terminalArgs TerArgs, int Count)
{
	struct stat buff;
	lstat(filePath, &buff); // filepath == path
	char CompletePath[300];
	strcpy(CompletePath, "");
	strcat(CompletePath, dirFile);
	

	if(TerArgs.arg_S)
	{
		char f_Size[10];
		sprintf(f_Size, " %d", (int)buff.st_size);
		strcat(CompletePath, " - (");
		strcat(CompletePath, f_Size);
		strcat(CompletePath, " )");
	}

	if(TerArgs.arg_s)
		if((int)buff.st_size < TerArgs.fileSize)
			strcpy(CompletePath, "");

	if(TerArgs.arg_f)
		if(strstr(filePath, TerArgs.fileFilter) == NULL)
			strcpy(CompletePath, "");

	if(TerArgs.arg_t)
	{
		int i, arg_tLen = 2;
		for(i = 0; i <= arg_tLen; i++)
		{
			switch(TerArgs.fileType[i])
			{
				case 'f':
				{
					if(!S_ISREG(buff.st_mode))
						strcpy(CompletePath, "");
					break;
				}
				case 'd':
				{
					if(!S_ISDIR(buff.st_mode))
						strcpy(CompletePath, "");
					break;
				}
			}
		}
	}
	if(strcmp(CompletePath, "") != 0)
	{
		for(int i = 0; i < Count; i++)
		{
			printf("\t");
		}
		printf("%s\n", CompletePath);
	}
}

void noRootPath(int argc, char **argv, terminalArgs TerArgs)
{
	if (opendir(argv[argSize]) == NULL)
    { 
    	char cDir[300];
    	getcwd(cDir, 300);
        //printf("%s\n", cDir);
        printf("Root File :%s\n", argv[argSize]); 
        fileDirectory(cDir, 0, print_Alg, TerArgs);
    }
}
int main(int argc, char  **argv)
{
	char Delim; 
	int opt = 0;
	terminalArgs TerArgs;
	TerArgs.arg_S = 0;
	TerArgs.arg_s = 0;
	TerArgs.arg_f = 0;
	TerArgs.arg_t = 0;
	TerArgs.arg_e = 0;
	TerArgs.arg_E = 0;		

	while((opt = getopt(argc, argv, "Ss:f:t:Ee"))!= -1)
	{
		if(opt == 'S')
			TerArgs.arg_S = 1;
		else if(opt == 's')
		{
			TerArgs.arg_s = 1;
			TerArgs.fileSize = atoi(optarg);
		}
		else if(opt == 'f')
		{
			TerArgs.arg_f = 1;
			strcpy(TerArgs.fileFilter, optarg);
		}
		else if(opt == 't')
		{
			TerArgs.arg_t = 1;
			strcpy(TerArgs.fileType, optarg);
		}
		else if(opt == 'e')
		{
			TerArgs.arg_e = 1;
			strcpy(TerArgs.E_Key, optarg);
		}
		else if(opt == 'E')
		{
			TerArgs.arg_E = 1;
			strcpy(TerArgs.E_Key, optarg);
		}
		else
			printf("------ Unrecognised Option ------%c\n", opt);
	}
	
	noRootPath(argc, argv, TerArgs);
    fileDirectory(argv[argSize], 0, print_Alg, TerArgs);
	return 0;	
}