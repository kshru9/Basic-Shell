#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int remove_directory(char *path) {

    struct stat rem;
    // stat the removing path
    if (stat(path,&rem)<0){
        printf("%s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }

    // if the destination is file
    if (S_ISREG(rem.st_mode)){
        // remove it
        if (remove(path)<0){
            printf("%s\n",strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    // if it is directory,
    // recurse
    else if (S_ISDIR(rem.st_mode)){
        // firstly open directory
        DIR *d = opendir(path);
        size_t path_len = strlen(path);
        int r = -1;

        if (d) {
            struct dirent *p;

            r = 0;
            while (!r && (p=readdir(d))) {
                int r2 = -1;
                char *buf;
                size_t len;

                // Skip the names "." and ".." as we don't want to recurse on them.
                if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
                    continue;
                // store length of path and current readdir path
                len = path_len + strlen(p->d_name) + 2; 
                // malloc buf to store that path
                buf = malloc(len);

                if (buf) {
                    struct stat statbuf;
                    snprintf(buf, len, "%s/%s", path, p->d_name);
                    // recurse for each content of the directory
                    r2 = remove_directory(buf);
                    free(buf);
                }
                r = r2;
            }
            closedir(d);
        }
        // if readdir fails, 
        // then there is no content in opened dire
        // hence just remove the empty directory
        if (!r)
            r = rmdir(path);
        return r;
    }
}

int rm(int argc, char* args[]){
    // if only rm without -r flag is passed.
    if (argc==2){
        return remove_directory(args[1]);
    }
    else if (argc==3){
        char* temp = "-r";
        // if flag is -r
        if (strcmp(args[1],temp)==0){
            return remove_directory(args[2]);
        }
        else{
            printf("Expected argument: rm [optional] path\n");
            exit(EXIT_FAILURE);
        }
    }
    else{
        printf("Expected argument: rm [optional] path\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[]){
    return rm(argc,argv);
}