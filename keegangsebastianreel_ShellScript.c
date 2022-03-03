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

/*
What are we implementing?
A: ls, clear, cat (files), ls -la, exit, cd (by one and by all), help
implement redirecting with cat from one file to another
implement write copy
*/

// Function Prototypes
int parseInput(char* input, char* splitWords[]);
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
        printf("\n Not enough arguements.");

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
    }
    fprintf(fp, "Test text.");
    fclose(fp);

    // Output Stream
    if ((fp = fopen("test.txt","r")) == NULL){
        printf("!Error opening file.");
        exit(1);
    }
    while (fgets(arr, 255, fp)){
        printf("\n%s\n", arr);
    }
    fclose(fp);

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

void promptUser(bool isBatch){

}

void printError(){

}

char redirectCommand(char* special, char* line, bool* isRedirectm, char* tool[], char* outputTokens[], bool* isExits){

}

void launchProcesses(char* tokens[], int numToekns, bool isRedirect){

}

bool exitProgram(char* tokens[], int numTokens){

}

void changeDirectories(char* tokens[], int numTokens){

}

void printHelp(char* str, int index){

}

char* executeCommand(char* cmd, bool* isRedirect, char* tokens[], char* outputTokens[], bool *isExists){

}