//mkdir.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if( argc == 1 )
	{
		printf("no dirent name");
		exit(0);
	}

	int i = 1;
	for(; i < argc; i++)
	{
		if( mkdir(argv[i],0775) == -1 )
		{
			perror("mkdir error");
			continue;
		}
	}
	exit(0);
}
