#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]){
    if (argc<3 || argc >3){
        printf("Expected argument: chmod ooo <filename>\n");
        exit(EXIT_FAILURE);
    }
    else{
        char* file;
        char* perm;
        perm = argv[1];
        file = argv[2];

        for (int i = 0; i<3; i+=1){
            // for user permission
            if (i==0){
                if (perm[i] == '0'){
                    if (chmod(file,!S_IRUSR & !S_IWUSR & !S_IXUSR)<0){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '1'){
                    printf("YESONE\n");
                    if (chmod(file, S_IXUSR)<0){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '2'){
                    printf("Working\n");
                    if (chmod(file,S_IWUSR & !S_IXUSR & !S_IRUSR)<0){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '3'){
                    if (chmod(file,S_IWUSR & S_IXUSR & !S_IRUSR)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '4'){
                    if (chmod(file,S_IRUSR & !S_IWUSR & !S_IXUSR)<0){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '5'){
                    if (chmod(file,S_IRUSR & S_IXUSR & !S_IWUSR)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '6'){
                    if (chmod(file,S_IRUSR & S_IWUSR & !S_IXUSR)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '7'){
                    if (chmod(file,S_IRUSR & S_IWUSR & S_IXUSR)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
            }
            // for group permissions
            else if (i==1){
                if (perm[i] == '0'){
                    if (chmod(file,!S_IRGRP & !S_IWGRP & !S_IXGRP)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '1'){
                    if (chmod(file,S_IXGRP & !S_IRGRP & !S_IWGRP)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '2'){
                    printf("Working\n");
                    if (chmod(file,S_IWGRP & !S_IRGRP & !S_IXGRP)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '3'){
                    if (chmod(file,S_IWGRP & S_IXGRP & !S_IRGRP)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '4'){
                    if (chmod(file,S_IRGRP & !S_IWGRP & !S_IXGRP)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '5'){
                    if (chmod(file,S_IRGRP & S_IXGRP & !S_IWGRP)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '6'){
                    if (chmod(file,S_IRGRP & S_IWGRP & !S_IXGRP)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '7'){
                    if (chmod(file,S_IRGRP & S_IWGRP & S_IXGRP)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
            }
            // for other permissions
            else if (i==2){
                if (perm[i] == '0'){
                    if (chmod(file,!S_IROTH & !S_IWOTH & !S_IXOTH)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '1'){
                    if (chmod(file,S_IXOTH & !S_IWOTH & !S_IROTH)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '2'){
                    printf("Working\n");
                    if (chmod(file,S_IWOTH & !S_IROTH & !S_IXOTH)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '3'){
                    if (chmod(file,S_IWOTH & S_IXOTH & !S_IROTH)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '4'){
                    if (chmod(file,S_IROTH & !S_IWOTH & !S_IXOTH)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '5'){
                    if (chmod(file,S_IROTH & S_IXOTH & !S_IWOTH)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '6'){
                    if (chmod(file,S_IROTH & S_IWOTH & !S_IXOTH)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                else if (perm[i] == '7'){
                    if (chmod(file,S_IROTH & S_IWOTH & S_IXOTH)){
                        printf("%s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
    }
    return 0;
}