#include <stdio.h>
// for stat()
#include <sys/stat.h>
#include <unistd.h>
// for errorno
#include <errno.h>
// for exit() free() malloc()
#include <stdlib.h>
// for opendir(), readdir(), closedir()
#include <dirent.h>
// for string manipulation methods
#include <string.h>
// for basename()
#include <libgen.h>

int mv(int argc, char* args[]){
    char* dest; 
    for (int i = 1; i < argc-1; i+=1){
        
        char* source = args[i];
        // malloc memory to store destination path
        dest = (char*)malloc(sizeof(char*)*(strlen(args[argc-1])));
        dest = strcpy(dest, args[argc-1]);

        DIR *dp;

        // if opendir() fails means dest is file
        // so just do rename , rename() handles making a new file 
        // if the source file doesnot exist in dest dir.
        if ((dp = opendir(dest)) == NULL){
            if (rename(source,dest)<0){
                printf("%s\n",strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
        else {
            // read the directory contents...
            // check if the source already exist.
            struct dirent *d;
            int exist = 0;
            while ((d = readdir(dp)) != NULL) {
                if (strcmp(d->d_name,source)==0){
                    printf("Destination file: %s already exist\n",d->d_name);
                    exist = 1;
                }
            }
            // if the current ith file already exist in given destination
            // do not move the file
            if (exist){
                continue;
            }
            char* file = basename(source);
            strcat(dest, "/");
            strcat(dest, file);
            if (rename(source,dest)<0){
                printf("%s\n",strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
        free(dest);
        closedir(dp);
    }
    return 0;
}

int main(int args, char* argv[]){
    // if <3 arguments are passed
    // print the prompt for expected argument
    if (args <3){
        printf("Expected arguments: Mv <source> <destination>");
    }
    else{
        int temp = mv(args,argv);
    }
    return 0;
}