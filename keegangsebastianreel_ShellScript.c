/*  Sebastian Reel and Keegan Graf
    Programming Assignment 1 (Part 2)
    Purpose: Shell Code (add to this)
*/

#include <stdio.h>
#include <string.h> // iumportant when you are going to use strtok to break strings into a series of tokens using delim and str
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h> // this has something to do with the execvp
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdbool.h>
/*
reminder for building the terminal:
    Print a prompt and wait for input. 
    Get the command line input.
    Parse the command line input.
    Find associated files.
    Pass any parameters from the shell to the OS command function.
    Execute the command (with applicable parameters).
*/ 

// Function Prototypes
int parseInput(char* input, char* splitWords[]);
void shellLoop();
void promptUser(bool isBatch);
void printError();
char redirectCommand(char* special, char* line, bool* isRedirectm, char* tool[], char* outputTokens[], bool* isExits);
void launchProcesses(char* tokens[], int numToekns, bool isRedirect);
bool exitProgram(char* tokens[], int numTokens);
void changeDirectories(char* tokens[], int numTokens);
void printHelp(char* str, int index);
char* executeCommand(char* cmd, bool* isRedirect, char* tokens[], char* outputTokens[], bool *isExists);

// Main
int main(int argc, char *argv[]){
    // fix shit here
    int i;
    printf("Program: %s", argv[0]);
    // needs to be improved for interactive mode
    if(argc==1)
        printf("\n No Batchfile detected.");

    // case for example if the user puts ./xxx batchfile
    if(argc>=2){
        printf("\nNum of Arguements: %d", argc);
        for(i = 0; i < argc; i++)
            printf("\nargv[%d]: %s", i, argv[i]);
    }

    // FIle I/O
    FILE *fp;
    char arr[255];
    
    // Input stream
    fp = fopen("test.txt","w");
    if(fp == NULL){
        printf("!Error opening file.");
        exit(1);
    } else {
        fprintf(fp, "Testing that the file opens and writes and reads.");
        fclose(fp);
    }

    // Output Stream
    if ((fp = fopen("test.txt","r")) == NULL){
        printf("!Error opening file.");
        return 1;
    }
    while (fgets(arr, 255, fp)){
        printf("\n%s\n", arr);
    }
    fclose(fp);
    
    // Redirection Stream
    //



    bool b;
    promptUser(b);

    printf("\n\nCorrectly Working.\n\n");
    return 0;
}

// Function Definitions
// Parse Input function is copy/pasted from Sara Davis to implement into the program 
int parseInput(char* input, char* splitWords[]){
      int wordInd = 0;
      splitWords[0] = strtok(input, " ");
      while(splitWords[wordInd] != NULL){
              splitWords[++wordInd] = strtok(NULL, " ");
      }
      return wordInd;
}

void shellLoop(){
    char *line;
    char **args;
    int status;
    /*
    while(status){
        printf("> ");
        //line
        args = parseInput(args, )
        //status
    }
    */
}

void promptUser(bool isBatch){
    // Prompt User
    //printf("USER : %s\n", getenv("USER"));
    if (isBatch == false){
        char hs[_SC_HOST_NAME_MAX + 1];
        gethostname(hs, _SC_HOST_NAME_MAX + 1);
        //printf("HOST : %s\n", hs);

        char cwd[256];
        getcwd(cwd, sizeof(cwd));
        //printf("PATH : %s\n", cwd);

        // Final Print
        printf("%s@%s:%s$ ", getenv("USER"), hs, cwd);
    } else {
        isBatch == true;
    }
}

void printError(){
    // Implements the error message whenever the user enters nonsense or a command not implemented by us pr execvp
    // Use for most edge cases
    printf("\nShell Program Error Encountered");
}

char redirectCommand(char* special, char* line, bool* isRedirectm, char* tool[], char* outputTokens[], bool* isExits){

}

void launchProcesses(char* tokens[], int numTokens, bool isRedirect){
    /*
    char *command = "ls";
    tokens[] = {"ls", "-l", NULL};

    if(fork() == numTokens){

    }
    */
}

bool exitProgram(char* tokens[], int numTokens){

}

void changeDirectories(char* tokens[], int numTokens){

}

void printHelp(char* str, int index){

}

char* executeCommand(char* cmd, bool* isRedirect, char* tokens[], char* outputTokens[], bool *isExists){

}