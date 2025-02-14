/* 
Name: Arwen Antes
CS 446 - Homework 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_WORDS 10
#define MAX_LENGTH 500

//This function parses user input by tokens and saves it into an array
int parseInput(char *input, char splitWords[][MAX_LENGTH], int maxWords){
    int count = 0;
    char *token = strtok(input, " ");
    while(token != NULL && count < maxWords){
        strcpy(splitWords[count++], token);
        token = strtok(NULL, " ");
    }
    return count;
}

//This function allows for changing directories
void changeDirectories(char *path){
    if(chdir(path) != 0){
        printf("Failed to Change Directory: %s\n", strerror(errno));
    }
}

//This function executes the inputted command with possible redirection to the input and output
int executeCommand(char *const *enteredCommand, const char *infile, const char *outfile){
    pid_t id = fork();
    if(id < 0){
        printf("Fork Failed: %s\n", strerror(errno));
        return -1;
    }
    if(id == 0){
        int fileDir;
        if(infile){
            fileDir = open(infile, O_RDONLY);
        }
        else if(outfile){
            fileDir = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        }

        if(fileDir < 0){
            printf("Failed to Open: %s\n", strerror(errno));
            _exit(1);
        }
        dup2(fileDir, STDOUT_FILENO);
        close(fileDir);
        

        execvp(enteredCommand[0], enteredCommand);
        printf("Execution Failed: %s\n", strerror(errno));
        _exit(1);
    }
    else{
        int stat;
        wait(&stat);
        if(!WIFEXITED(stat) || WEXITSTATUS(stat) != 0){
            printf("Child finished with error: %d\n", WEXITSTATUS(stat));
        }
    }
    return 0;
}

int main(){
    char input[MAX_LENGTH], splitWords[MAX_WORDS][MAX_LENGTH], cwd[MAX_LENGTH];
    char *netid = "aantes";

    while(1){
        getcwd(cwd, sizeof(cwd));
        printf("%s:%s$ ", netid, cwd);
        if(fgets(input, MAX_LENGTH, stdin) == NULL){
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        int numWords = parseInput(input, splitWords, MAX_WORDS);
        if(numWords == 0) continue;
        if(strcmp(splitWords[0], "exit") == 0){
            break;
        }
        else if(strcmp(splitWords[0], "cd") == 0){
            if(numWords != 2){
                printf("Path Not Formatted Correctly!\n");
            }
            else{
                changeDirectories(splitWords[1]);
            }
        }
        else{
            char *infile = NULL, *outfile = NULL, *arguments[MAX_WORDS+1];
            int numArguments = 0;

            for(int i = 0; i < numWords; i++){
                if((strcmp(splitWords[i], "<") == 0) && (i+1 < numWords)){
                    infile = splitWords[i+1];
                    i++;
                }
                else if((strcmp(splitWords[i], ">") == 0) && (i+1 < numWords)){
                    outfile = splitWords[i+1];
                    i++;
                }
                else{
                    arguments[numArguments++] = splitWords[i];
                }
            }
            arguments[numArguments] = NULL;
            if(numArguments > 0){
                executeCommand(arguments, infile, outfile);
            }
        }
    }
    return 0;
}
