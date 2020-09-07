// for standard input output
#include <stdio.h>
// header for fork(), getcwd()
#include <unistd.h>
// for string manipulations
#include <string.h>
// for printing EXIT_FAILURE, etc
#include <stdlib.h>
// header for waitpid()
#include <sys/wait.h>
// for errno
#include <errno.h>

// global define
#define MAXCOM 1000
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

// // builtin commands list
// char* builtins[] = {
//   "exit",
//   "help",
//   "wget",
//   "pmap",
//   "ps"
// };
// // number of builtin commands
// int numBuiltins = sizeof(builtins)/sizeof(char*);

// initial function when shell starts printing copyright rights
void initShell(){
    
    printf("\n\n\n");
    printf("################################################\n");
    printf("\n");
    printf("             (c) Shruti Katpara                 \n");
    printf("\n");
    printf("################################################\n");
    printf("\n\n\n");
}
// end of initial function

// function to write prompt line and read the input command
char* Prompt(){
    char currDir[1024];
    // to store current directory path string in currDir array using getcwd()
    getcwd(currDir,sizeof(currDir));
    // printing currDir in prompt
    printf("$$$:%s ",currDir);
    // to store input line
    char* line = NULL;
    ssize_t bufsize = 0; // have getline allocate a buffer for us

    // checking if the getline() reads EOF or null and returning failure
    if (getline(&line, &bufsize, stdin) == -1){
      // checking for EOF of given input
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);  // We recieved an EOF
        } 
      // if its not EOF, then there will error in reading the input
        else{
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }
    // returning input command
    return line;
}
// end of Prompt()

// function to tokenize the input command
char **tokenize(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  // if memory allocation fails
  if (!tokens) {
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      // if realloc fails
      if (!tokens) {
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}
// end of tokenize()

// cd command function implementation
// for cd we dont have to fork the shell process
// because in cd we have to change the directory in current shell process
int cd(char* args[]){
    char s[1024];
    char* argument = "cd <nameOfDirectory>";
    if (args[1]==NULL){
        printf("Expected argument %s\n",argument);
    }
    else{
        if (chdir(args[1]) != 0){
            printf("%s\n", strerror(errno));
        }
    }
    return 1;
}
// end of cd() function


//function to execute the input commands
int execute(char** args)
{
    // if no arguments were passed
    if (args[0]==NULL){
        return 1;
    }
    else{
        // strcmp() will compare the first argument with "Cd"
        // returns 0 on success
        // for cd we dont have to fork the shell process
        // because in cd we have to change the directory in current shell process
        if (strcmp("Cd", args[0])==0){
            int temp = cd(args);
        }
        else {
            // forking the process
            int pid = fork();
            //int len = sizeof(args)/sizeof(char);

            //printf("%s\n",args[-1]);
            // if last argument is &
            // then exit from the parent process
            // because of this child will be orphaned now
            // which means it will execute on it own's in background
            // the command will be given back to shell
            // if (strcmp(args[len-1],"&")==0){
                
            //     if (pid==0){
            //         args[len-1] = NULL;
            //         // check using strcmp() which command is to executed
            //         // using execvp(), execute the binary file of that command
            //         // on error, it returns -1
            //         if (strcmp(args[0], "ls") == 0){
                        
            //             if (execvp("./ls",args) < 0){
            //                 printf("%s\n", strerror(errno));
            //             }
            //             exit(EXIT_FAILURE);
            //         }
            //         else if (strcmp(args[0], "Mkdir") == 0){
            //             if (execvp("./mkdir",args) < 0){
            //                 printf("%s\n", strerror(errno));
            //             }
            //             exit(EXIT_FAILURE);
            //         }
            //         else if (strcmp(args[0], "Cp") == 0){
            //             if (execvp("./Cp",args) < 0){
            //                 printf("%s\n", strerror(errno));
            //             }
            //             exit(EXIT_FAILURE);
            //         }
            //         else if (strcmp(args[0], "Mv") == 0){
            //             if (execvp("./mv",args) < 0){
            //             printf("%s\n", strerror(errno));
            //             }
            //             exit(EXIT_FAILURE);
            //         }
            //         else if (strcmp(args[0], "Pwd") == 0){
            //             if (execvp("./pwd",args) < 0){
            //             printf("%s\n", strerror(errno));
            //             }
            //             exit(EXIT_FAILURE);
            //         }
            //         else if (strcmp(args[0], "Chmod") == 0){
            //             if (execvp("./chmod",args) < 0){
            //             printf("%s\n", strerror(errno));
            //             }
            //             exit(EXIT_FAILURE);
            //         }
            //         else if (strcmp(args[0], "rm") == 0){
            //             if (execvp("./rm",args) < 0){
            //             printf("%s\n", strerror(errno));
            //             }
            //             exit(EXIT_FAILURE);
            //         }
            //         else if (strcmp(args[0], "cat") == 0){
            //             if (execvp("./cat",args) < 0){
            //             printf("%s\n", strerror(errno));
            //             }
            //             exit(EXIT_FAILURE);
            //         }
            //         else if (strcmp(args[0], "grep") == 0){
            //             if (execvp("./grep",args) < 0){
            //             printf("%s\n", strerror(errno));
            //             }
            //             exit(EXIT_FAILURE);
            //         }
            //         else{
            //             if(execvp(args[0],args)<0){
            //             printf("%s\n",strerror(errno));
            //             }
            //         }
            //     }
            //     else if (pid>0){
            //         exit(EXIT_SUCCESS);
            //     }
            //     else{
            //         printf("%s\n", strerror(errno));
            //     }
            // }
            // else{
                if (pid == 0) {
                    // Child process
                    // check using strcmp() which command is to executed
                    // using execvp(), execute the binary file of that command
                    // on error, it returns -1
                    if (strcmp(args[0], "ls") == 0){
                    if (execvp("./ls",args) < 0){
                        printf("%s\n", strerror(errno));
                    }
                    exit(EXIT_FAILURE);
                    }
                    else if (strcmp(args[0], "Mkdir") == 0){
                    if (execvp("./mkdir",args) < 0){
                        printf("%s\n", strerror(errno));
                    }
                    exit(EXIT_FAILURE);
                    }
                    else if (strcmp(args[0], "Cp") == 0){
                    if (execvp("./Cp",args) < 0){
                        printf("%s\n", strerror(errno));
                    }
                    exit(EXIT_FAILURE);
                    }
                    else if (strcmp(args[0], "Mv") == 0){
                    if (execvp("./mv",args) < 0){
                        printf("%s\n", strerror(errno));
                    }
                    exit(EXIT_FAILURE);
                    }
                    else if (strcmp(args[0], "Pwd") == 0){
                    if (execvp("./pwd",args) < 0){
                        printf("%s\n", strerror(errno));
                    }
                    exit(EXIT_FAILURE);
                    }
                    else if (strcmp(args[0], "Chmod") == 0){
                    if (execvp("./chmod",args) < 0){
                        printf("%s\n", strerror(errno));
                    }
                    exit(EXIT_FAILURE);
                    }
                    else if (strcmp(args[0], "rm") == 0){
                    if (execvp("./rm",args) < 0){
                        printf("%s\n", strerror(errno));
                    }
                    exit(EXIT_FAILURE);
                    }
                    else if (strcmp(args[0], "cat") == 0){
                    if (execvp("./cat",args) < 0){
                        printf("%s\n", strerror(errno));
                    }
                    exit(EXIT_FAILURE);
                    }
                    else if (strcmp(args[0], "grep") == 0){
                    if (execvp("./grep",args) < 0){
                        printf("%s\n", strerror(errno));
                    }
                    exit(EXIT_FAILURE);
                    }
                    else{
                    if(execvp(args[0],args)<0){
                        printf("%s\n",strerror(errno));
                    }
                    }
                } 
                else if (pid < 0) {
                    // error in forking the process
                    printf("%s\n", strerror(errno));
                } 
                else {
                    // Parent process
                    // using wait(NULL), parent process waits for its all children to finish processing
                    // and then executes.
                    int rc_wait = wait(NULL);
                }
            //}
        }
    // return status of 1 showing all execution was successful and prompt should continue
    return 1;
    }
}
// end of execute()

// main function
int main(){
    char* inputString;
    char **args;
    int status;

    // printing copyright
    // this will be executed everytime one runs this shell
    initShell();

    // shell continues untill there is successful execution of input commands.
    do {
        inputString = Prompt();
        args = tokenize(inputString);
        status = execute(args);

        // freeing up allocated memory.
        free(inputString);
        free(args);
    }
    while(status);
    return 0;
}