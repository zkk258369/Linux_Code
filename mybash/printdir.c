#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

void printdir(char *dir, int depth)
{
    DIR *dp;
    struct dirent * entry;
    struct stat statbuf;

    if(( dp = opendir(dir)) == NULL )
    {
        fprintf(stderr, "file to open the directory: %s\n", dir);
        return;
    }
    
    chdir(dir);
    while(( entry = readdir(dp)) != NULL )
    {
        stat(entry->d_name, &statbuf);
        if( S_ISDIR(statbuf.st_mode) )
        {
            if( strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0 )
             {
                continue;
             }
             printf("%*s%s/\n", depth, "", entry->d_name);
             printdir(entry->d_name, depth + 4);
        }
        else
        {
            printf("%*s%s\n",depth, "", entry->d_name);
        }
    }
    chdir("..");
}


int main(int argc, char *argv[])
{
    char * dirname = ".";
    if(argc >= 2)
    {
        dirname = argv[1];
    }

    printf("Directory scan of: %s\n", dirname);
    printdir(dirname, 0);
    printf("done.\n");
   

    exit(0);
}
