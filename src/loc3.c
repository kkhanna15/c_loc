/*
 ============================================================================
 Name        : loc3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Count LOC for all files in specified directory
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>


int main(int argc, char *argv[])
{
	DIR *dp;
	int c,count = 0;
	struct dirent *ep;
	char *filePath;
	FILE *fin;


	if (argc <= 1)
	{
		printf("Please specify input directory\n");
		return 0;
	}

	printf("Directory name:\n%s\n", argv[1]);

	if(!(dp = opendir(argv[1])))
	{
		printf("Directory not found\n");
		return 0;
	}
	while(ep = readdir(dp))
	{
		filePath = strcat(argv[1],ep->d_name);
		printf("file:%s",filePath);
		fin = fopen(filePath,"r");
		while((c = fgetc(fin)) != EOF)
			{
				if(c == '/')
				{
					c = fgetc(fin);
					if(c == '/')
					{
						while((c = fgetc(fin)) != '\n');
					}
					else if(c == '*')
					{
						c = fgetc(fin);
						while(c != '/')
						{
							c = fgetc(fin);
							if(c == '*')
							{
								c = fgetc(fin);
								if(c == '/')
								{
									break;
								}
							}
						}
						//printf("%c",c);
					}
					//printf("%c",c);
				}
				else if(c != ' ' && c != '\t' && c != '\n')
				{
					count++;
					//printf("c: %c ,count at this point: %d\n",c,count);
					while((c = fgetc(fin)) != '\n');

				}

			}
		fclose(fin);
		(void) closedir(dp);
	}

	printf("LOC = %d\n",count);
	return EXIT_SUCCESS;
}

