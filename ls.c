#include <stdio.h>    
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>   
#include <dirent.h>    // opendir, readdir, closedir
#include <string.h>    // strlen, strncpy, strncat
#include <stdbool.h>   // For booleans
#include <errno.h>
#include <time.h>   
#include <pwd.h>
#include <grp.h>

#define STRINGSIZE 1024


int ls(int argc, char* argv[]){
    struct stat sb;
    char* pathname = ".";
    bool list;
    DIR *dp;

    // if no argument is passed and ls is called
    if (argc<1){
        printf("Expected argument: ls <path>\n");
    }
    // if ls is called without any directory name
    else if (argc==1){
        // execute ls for current working directory represented as '.'
        pathname = ".";
        // we stat the argument to check if it is directory
        if (stat(pathname, &sb) == -1){
            printf("%s\n",strerror(errno));
            exit(EXIT_FAILURE);
        }
        // if it is directory
        if (S_ISDIR(sb.st_mode)){
            // opendir()
            if ((dp = opendir(pathname)) == NULL){
                printf("%s\n",strerror(errno));
                exit(EXIT_FAILURE);
            }
            // read the contents of directory opened
            // readdir returns the stream of all contents in the opened directory
            struct dirent *d;
            while ((d = readdir(dp)) != NULL) {
                printf("%s\n", d->d_name);
            }
            closedir(dp);
        }
    }
    else{
        // when multiple directories are passed in ls command
        // execute ls for each directory one by one
        for (int i = 1; i < argc; i+=1){
            // point to ith directory
            pathname = argv[i];

            // stat it to check if valid directory name is passed
            if (stat(pathname, &sb) == -1){
                printf("%s\n",strerror(errno));
                exit(EXIT_FAILURE);
            }
            if (S_ISDIR(sb.st_mode)){
                // open directory
                if ((dp = opendir(pathname)) == NULL){
                    printf("%s\n",strerror(errno));
                    exit(EXIT_FAILURE);
                }
                // print all the content files and directories of opened directory
                struct dirent *d;
                printf("------%d directory contents---------\n",i);
                while ((d = readdir(dp)) != NULL) {
                    printf("%s\n", d->d_name);
                }
                closedir(dp);
            }
            
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    printf("");
    return ls(argc,argv);
}