#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

int grep(int argc, char* argv[]){
    char* searchterm = argv[1];
    struct stat sb;

    // if no searchterm is paased to grep
    // match nothing
    if (stat(searchterm,&sb)>=0){
        return 0;
    }
    else{
        // if no file is passed to grep command
        // read the input from stdin file 
        // and execute grep
        if (argc==2){
            char* buf = NULL;
            size_t len = 0;
            size_t nread;
            
            // getline() adjust the buf and len as per requirement
            // hence when input size is arbitarily long
            // getline uses realloc as per requirement
            while((nread = getline(&buf,&len,stdin))!=-1){
                // strstr() searches the searchterm string in given string 
                if (strstr(buf, searchterm)!=NULL){
                    printf("%s\n",buf);
                }
            }
            free(buf);
        }
        else{
            // if searchterm and file both are non empty
            for (int i = 2; i < argc; i+=1){
                printf("-----------------executing grep for file: %s------------------------\n",argv[i]);
                char* buf = NULL;
                size_t len = 0;
                size_t nread;
                FILE *stream;
                // open ith file
                if ((stream = fopen(argv[i], "r")) == NULL){
                    printf("grep: cannot open file: %s\n",argv[i]);
                    exit(EXIT_FAILURE);
                }
                // read each line of file
                while((nread = getline(&buf,&len,stream)) != NULL){
                    // compare and search the search term
                    if (strstr(buf, searchterm)!=NULL){
                        printf("%s\n",buf);
                    }
                    // if we get to end of file
                    // break
                    if (feof(stream)!=0){
                        break;
                    }
                }
                free(buf);
                fclose(stream);
            }
        }
    }
    return 0;
}


int main(int argc, char* argv[]){
    // if no arguments are passed to grep command
    if (argc == 1){
        printf("Expected argument: grep: searchterm [file ...]\n");
        exit(EXIT_FAILURE);
    }
    else{
        return grep(argc, argv);
    }
    return 0;
}