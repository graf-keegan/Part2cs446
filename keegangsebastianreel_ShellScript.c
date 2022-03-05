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
char *redirectCommand(char* special, char* line, bool* isRedirectm, char* tool[], char* outputTokens[], bool* isExits);
void launchProcesses(char* tokens[], int numToekns, bool isRedirect);
bool exitProgram(char* tokens[], int numTokens);
void changeDirectories(char* tokens[], int numTokens);
void printHelp(char* str[], int index);
char* executeCommand(char* cmd, bool* isRedirect, char* tokens[], char* outputTokens[], bool *isExits);

// Main
int main(int argc, char *argv[]){
    // fix things here

    //this is for executeCommand
    char * tokens[10];
    char * outputTokens[10];
    bool isExits;
    bool isRedirect = false;
    //------------------------

    bool isBatch = false;
    int i;
    //printf("Program: %s", argv[0]);
    
    // needs to be improved for interactive mode
    /*if(argc==1)
        printf("\nNo Batchfile detected.\nStarting interactive terminal.\n");

    // case for example if the user puts ./xxx batchfile
    if(argc==2){
        printf("\nNum of Arguements: %d", argc);
        for(i = 0; i < argc; i++)
            printf("\nargv[%d]: %s", i, argv[i]);
            isBatch == true;
    }

    // Edge case for too many arguements being inputted
    if(argc>2){
        printf("!Error: Too many arguements!");
        exit(1);
    }
*/
    // Prompt User
    // Prompt the user with a display of the system username, hostname, and current working directory
    
    while(isExits == false){
        char s[100] = "";
        promptUser(isBatch);
        fgets(s, 100, stdin);
        executeCommand(s, &isRedirect, tokens, outputTokens, &isExits);
    }
/*

    // FIle I/O
    // File pointer and character array for input
    FILE *fp;
    char arr[255];
    
    // Input stream
    fp = fopen("test.txt","w");
    if(fp == NULL){
        printf("!Error opening file.");
        exit(1);
    } 
    else if(isBatch == true){
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
    //This is used for execute function(change later)
    */
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
    printf("Shell Program Error Encountered.\n");
}

char *redirectCommand(char* special, char* line, bool* isRedirect, char* tool[], char* outputTokens[], bool* isExits){
    printf("%s\n", special);
    char *dupS = strdup(special);

    return NULL;
}

void launchProcesses(char* tokens[], int numTokens, bool isRedirect){

}

bool exitProgram(char* tokens[], int numTokens){
    if(!(strcmp(tokens[0], "exit\n\n")) && numTokens == 1){
        return true;
    }
    if(!strcmp(tokens[0], "exit\n\n")){
    printError();
    }
    return false;
}

void changeDirectories(char* tokens[], int numTokens){
    if((!strcmp("cd", tokens[0])) && numTokens == 2){
        tokens[1][strlen(tokens[1])-1] = '\0';
        tokens[1][strlen(tokens[1])-1] = '\0';
        if(chdir(tokens[1]) == -1){
            printError();
        }
    }
    if((!strcmp("cd\n\n", tokens[0])) && numTokens == 1){
        printError();
    }
}

void printHelp(char* str[], int index){
    if((!strcmp("help\n\n", str[0])) && index == 1){
        printf("These shell commands are defined internally.\n");
        printf("help-prints this screen so you can see available shell commands.\n");
        printf("cd -changes directories to specified path; if not given, defaults to home.\n");
        printf("exit -closes the example shell.\n");
        printf("[input] > [output] -pipes input file into output file\n\n");
        printf("And more! If it's not explicitly defined here (or in the documentation for the assignment), then the command should try to be executed by launchProcesses. That's how we get ls -la to work here!\n");
    } else if(!strcmp("help\n\n", str[0])){
        printError();
    }
}

char* executeCommand(char* cmd, bool* isRedirect, char* tokens[], char* outputTokens[], bool *isExits){
        char *dupCmd = strdup(cmd);
        strcat(dupCmd, "\n");
        outputTokens[10];
        char * newRedirect = "";
        char * Command = "";
        int numTok = parseInput(dupCmd, outputTokens);


        Command = strchr(dupCmd, '>');

        if(Command != NULL){
            //newRedirect = redirectCommand(cmd, cmd, isRedirect, tokens, outputTokens, isExits);
            //printf("test");
            if(Command == NULL){
                numTok = parseInput(dupCmd, outputTokens);
                if(!numTok){
                    return NULL;
                }
            }
        }
        else{
            *isRedirect = false;
            if(exitProgram(outputTokens, numTok)){
                *isExits = true;
                return Command;
            }

        }


    changeDirectories(outputTokens, numTok);
    printHelp(outputTokens, numTok);
    //launchProcesses(outputTokens, numTok, *isRedirect);    

    return Command;
}