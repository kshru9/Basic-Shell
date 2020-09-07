#include <stdio.h>
// for getcwd()
#include <unistd.h>

int pwd(char* args[]){
    // create a buffer to store pwd
    char s[1024];
    // getcwd() returns current working directory path
    printf("%s\n", getcwd(s,1024));
    return 0;
}

int main(int argc, char* argv[]){
    // if any arguments is passed in pwd
    if (argc>1){
        printf("Expected argument: Pwd");
        return 1;
    }
    else{
        return pwd(argv);
    }
}