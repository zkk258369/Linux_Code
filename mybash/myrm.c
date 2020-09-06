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
		printf("no dirent name\n");
		exit(0);
	}

	int i = 1;
	for(; i < argc; i++)
	{
	    
    	if( rmdir(argv[i]) == -1 )
		{
			perror("rmdir error");
			continue;
		}
	}
	exit(0);
}
