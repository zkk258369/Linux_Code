//myls.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
	char buff[256] = {0};
	//huoqu mululiu
	getcwd(buff,256);

	DIR *pdir = opendir(buff);
	if( NULL == pdir )
	{
		perror("ls error");
		exit(0);
	}

	struct dirent *p = NULL;
	struct stat st;
	while( (p = readdir(pdir)) != NULL )
	{
		if(strncmp(p->d_name, ".", 1) == 0)
		{
			continue;
		}

		stat(p->d_name,&st);
		if( S_ISDIR(st.st_mode) )
		{
			printf("\033[1;34m%s\033[0m  ", p->d_name);
		}
		else
		{
			if( st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH) )
			{
				printf("\033[1;32m%s\033[0m  ", p->d_name);
			}
			else
			{
				printf("%s  ", p->d_name);
			}
		}
	}
    printf("\n");
	closedir(pdir);

	exit(0);
}
