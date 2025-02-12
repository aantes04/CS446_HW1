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

int parseInput(char *input, char splitWords[][MAX_LENGTH], int maxWords);
void changeDirectories(char *path);
int executeCommand(char *const *enteredCommand, const char *infile, const char *outfile);

int main(){
    char input[MAX_LENGTH], splitWords[MAX_WORDS][MAX_LENGTH], *commands[MAX_WORDS+1], cwd[MAX_LENGTH];
    char *netid = "netid";

    while(1){
        getcwd(cwd, sizeof(cwd));
        printf("%s:%s$ ", netid, cwd);
        fgets(input, MAX_LENGTH, stdin);

        return 0;
    }
}
