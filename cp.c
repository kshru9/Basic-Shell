#include <fcntl.h>
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
// for mkdir()
#include <sys/types.h>

#define BUF_SIZE 1024

int cp(int argc, char* args[]){
        if (strcmp(args[1],"-r")==0){
            // open the source directory
            DIR *d = opendir(args[2]);
            // if open fails, exit
            if (d<0){
                printf("%s\n",strerror(errno));
                exit(EXIT_SUCCESS);
            }
            else{
                // malloc memory to store destination path
                char* dest = malloc(strlen(args[3])*sizeof(char*) + 1);
                dest  = strcpy(dest, args[3]);

                // make a path inside dest path
                strcat(dest,"/");
                strcat(dest,basename(args[2]));

                // mkdir() inside dest dir
                if (mkdir(dest,777)<0){
                    printf("%s\n",strerror(errno));
                    exit(EXIT_FAILURE);
                }
                

                // read source dir
                struct dirent *p;
                int empty = 1;
                while((p = readdir(d))!=NULL){
                    if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
                    continue;
                    
                    empty = 0;
                    // malloc memory to store dest pathname
                    char* temp = malloc(strlen(dest)*sizeof(char*) + 1);
                    temp = strcpy(temp, dest);
                    strcat(temp,"/");
                    
                    // malloc memory to store source file
                    char* source = malloc(strlen(args[2])*sizeof(char*) + 1);
                    source = strcpy(source, args[2]);
                    strcat(source,"/");
                    strcat(source, p->d_name);
                    
                    // stat the source dir file
                    struct stat sb;
                    if (stat(source,&sb)<0){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                    
                    // concatenate basename of source
                    strcat(temp, basename(source));
                    
                    // if dir inside source dir
                    if (S_ISDIR(sb.st_mode)){
                        if (mkdir(temp,777)<0){
                            printf("%s\n",strerror(errno));
                            exit(EXIT_FAILURE);
                        }
                    }
                    // if file inside source dir
                    else if (S_ISREG(sb.st_mode)){
                        char* buf[BUF_SIZE];
                        // open source file
                        int sourceFd = open(source, O_RDONLY);
                        if (sourceFd<0){
                            printf("%s\n",strerror(errno));
                            exit(EXIT_FAILURE);
                        }

                        // create that file in destination directory
                        int destFd = open(temp, O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC);
                        if (destFd<0){
                            printf("%s\n",strerror(errno));
                            exit(EXIT_FAILURE);
                        }

                        // copy contents of source file to destination file
                        size_t linesRead = 0;
                        while((linesRead = read(sourceFd,buf,BUF_SIZE)) > 0){
                            if (write(destFd,buf,linesRead)!=linesRead){
                                printf("\nError writing file %s\n",p->d_name);
                            }
                        }

                        // close all files and free the memory
                        if (close(sourceFd)<0){
                            printf("%s\n",strerror(errno));
                        }
                        if (close(destFd)<0){
                            printf("%s\n",strerror(errno));
                        }
                    }
                    free(temp);
                    free(source);
                }
                free(dest);
            }
        }
        else{
            for (int i = 1; i < argc-1; i+=1){
                char* buf[BUF_SIZE];
                
                // open ith source file
                int sourceFd = open(args[i], O_RDONLY);
                if (sourceFd<0){
                    printf("%s\n",strerror(errno));
                    exit(EXIT_FAILURE);
                }
                printf("SRCOPENINNOT-R\n");
                // malloc memory to store destination path
                char* dest = malloc(strlen(args[argc-1])*sizeof(char*) + 1);
                dest  = strcpy(dest, args[argc-1]);

                struct stat sb;
                // if stat fails
                // it means the destination given is not a directory
                if (stat(dest, &sb)<0){
                    // create a dest file
                    int destFd = open(dest, O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC);

                    if (destFd<0){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                    // copy every line of source to dest
                    size_t linesRead = 0;
                    while((linesRead = read(sourceFd,buf,BUF_SIZE)) > 0){
                        if (write(destFd,buf,linesRead)!=linesRead){
                            printf("\nError writing file %s\n",args[2]);
                            
                        }
                    }

                    if (close(sourceFd)<0){
                        printf("%s\n",strerror(errno));
                    }
                    if (close(destFd)<0){
                        printf("%s\n",strerror(errno));
                    }
                }
                else if (S_ISDIR(sb.st_mode)){
                    // concatenate source filename to destination
                    strcat(dest, "/");
                    strcat(dest, basename(args[i]));
                    
                    // create that file in destination directory
                    int destFd = open(dest, O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC);
                    if (destFd<0){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }

                    // copy contents of source file to destination file
                    size_t linesRead = 0;
                    while((linesRead = read(sourceFd,buf,BUF_SIZE)) > 0){
                        if (write(destFd,buf,linesRead)!=linesRead){
                            printf("\nError writing file %s\n",args[i]);
                        }
                    }

                    // close all files and free the memory
                    if (close(sourceFd)<0){
                        printf("%s\n",strerror(errno));
                    }
                    if (close(destFd)<0){
                        printf("%s\n",strerror(errno));
                    }
                    
                }
                free(dest);
            }
    }
    
    return 0;
}
 
int main(int argc, char* args[])
{
    // if not all three arguments are passed
    if (argc<3){
        printf("Expected argument: Cp [OPTIONAL] <source> <destination>");
        exit(EXIT_FAILURE);
    }
    else{
        int temp = cp(argc,args);
    }
	return 0;
}