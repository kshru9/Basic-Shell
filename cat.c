#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
// for STDOUT_FILENO
#include <unistd.h>
// for open() close() write()
#include <fcntl.h>

int cat(int argc, char* argv[]){
    // for all the files passed in argument
    for (int i = 1; i < argc; i+=1){
        printf("---------------------------cat command output for file: %s-------------------------\n", argv[i]);
        // open the file in read only mode
        int fd = open(argv[i] , O_RDONLY);
        // if open() fails
        if (fd < 0){
            printf("%s\n",strerror(errno));
            exit(EXIT_FAILURE);
        }
        else{
            // read byte by byte from the opened file and write in STDOUT file
            char* buf;
            while(read(fd,&buf,1)){
                write(STDOUT_FILENO,&buf,1);
            }
            printf("\n");
            close(fd);
        }
    }
    return 0;
}

int main(int argc, char* argv[]){
    // if no arguments are passed to cat command
    if (argc==1){
        printf("Expected argument: cat <filename1> <filename2> ...\n");
        exit(EXIT_FAILURE);
    }
    else {
        int temp = cat(argc,argv);
        return temp;
    }
}