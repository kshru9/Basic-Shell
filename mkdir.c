#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
// for mkdir()
#include <sys/types.h>

int main(int argc, char* argv[]){
    if (argc<2)
    {
        printf("Expected argument: Mkdir [path ... ]\n");
    }
    else{
        for (int i = 1; i < argc; i+=1){
            // use mkdir() function to make a directory of given path
            // and initially give full access to all the groups
            if (mkdir(argv[i],777)<0){
                printf("%s\n",strerror(errno));
            }
        }
    }
    return 0;
}