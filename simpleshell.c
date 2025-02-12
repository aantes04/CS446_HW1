/*
Name: Arwen Antes
CS 446 - Homework 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_WORDS 10
#define MAX_LENGTH 500

int parseInput(char *input, char splitWords[][MAX_LENGTH], int maxWords){
    int count = 0;
    char *token = strtok(input, " ");
    while(token != NULL && count < maxWords){
        strcpy(splitWords[count++], token);
        token = strtok(NULL, " ");
    }
    return count;
}
void changeDirectories(char *path){
    if(chdir(path) != 0){
        perror("CD Failed");
    }
}
int executeCommand(char *const *enteredCommand, const char *infile, const char *outfile){
    pid_t id = fork();
    if(id < 0){
        perror("Fork Failed");
        return -1;
    }
    if(id == 0){
        int fileDir;
        if(infile){
            fileDir = open(infile, O_RDONLY);
            if(fileDir < 0){
                perror("Input File Error");
                exit(EXIT_FAILURE);
            }
        }
        else if (outfile){
            fileDir = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if(fileDir < 0){
                perror("Output File Error");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        execvp(enteredCommand[0], enteredCommand);
        perror("Execution Failed");
        exit(EXIT_FAILURE);
    }
    else{
        int stat;
        waitpid(id, &stat, 0);
    }
    return 0;
}

int main(){
    char input[MAX_LENGTH], splitWords[MAX_WORDS][MAX_LENGTH], *commands[MAX_WORDS+1], cwd[MAX_LENGTH];
    char *netid = "netid";

    while(1){
        getcwd(cwd, sizeof(cwd));
        printf("%s:%s$ ", netid, cwd);
        fgets(input, MAX_LENGTH, stdin);

        input[strcspn(in, "\n")] = 0;
        int numWords = parseInput()
    }
}
