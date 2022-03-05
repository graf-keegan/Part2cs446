/*  Sebastian Reel and Keegan Graf
    Programming Assignment 1 (Part 2)
    Purpose: Shell Code (add to this)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdbool.h>

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
    // initializing the file streams for input, output, and redirection
    FILE *input_fp = NULL;
    FILE *output_fp = NULL;
    FILE *redirect_fp = NULL;

    //this is for executeCommand
    char * tokens[10];
    char * outputTokens[10];
    bool isExits;
    bool isRedirect = false;
    //------------------------
    // batch
    bool isBatch = false;

    // checking if batch or not
    if(argc == 2){
        isBatch = 1;
    } else {
        isBatch = 0;
    }

    // main loop for interactive terminal
    while(isExits == false){
        // this is the batch case of is a bile is added to the command line arguements
        if(isBatch){
            char line[200];
            stdin = fopen(argv[argc - 1], "r");
            while(fgets(line, 200, stdin)){
                printf("%s\n", line);
                executeCommand(line, &isRedirect, tokens, outputTokens, &isExits);
            }
            isExits = true;
        // the main interactive terminal without any more arguements
        } else {
            char s[100] = "";
            promptUser(isBatch);
            fgets(s, 100, stdin);
            executeCommand(s, &isRedirect, tokens, outputTokens, &isExits);
        }     
    }
    
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
    // Prints the entire user, home device, and current working directory to the terminal / interactive terminal
    if (isBatch == false){
        char hs[_SC_HOST_NAME_MAX + 1];
        gethostname(hs, _SC_HOST_NAME_MAX + 1);
        //printf("HOST : %s\n", hs);

        char cwd[256];
        getcwd(cwd, sizeof(cwd));

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
    char *wordsThatGetSplit[100];
    char *dupS = strdup(special);
    int numTok = parseInput(dupS, outputTokens);
    int i=0;

    while (outputTokens[i]!=NULL) {
        // try catch me
        if (strchr(outputTokens[i], '>')) {
            *isRedirect = true;
            free(dupS); 
            return outputTokens[i+1];
        }
        i++;
    }

    *isRedirect = false;
    free(dupS); //OMG IT FIXED IT!
    return NULL;
}

void launchProcesses(char* tokens[], int numTokens, bool isRedirect){
    // These will be used to parse the newline off of the commands (any commands that arent completed)
    tokens[numTokens - 1][strlen(tokens[numTokens - 1])-1] = '\0';
    tokens[numTokens - 1][strlen(tokens[numTokens - 1])-1] = '\0';
    
    if(isRedirect == 0){
        // creates a child process using the execvp function, taking in commands
        // includes commands not listed in the help command. (like cat, echo, etc.)
        if(!fork()){
            execvp(tokens[0], tokens);
            exit(0);
        } else {
            wait(NULL);
            return;
        }
    } else {
        int i = 0;
        while(i < numTokens){
            printf("%s <--\n", tokens[i]);
            if(strchr(tokens[i], '>')) {
                // try catch me
            freopen(tokens[i+1], "w",stdout);
            tokens[i] = NULL;

                if(!fork()){
                    execvp(tokens[0], tokens);
                    exit(0);
                } else {
                    wait(NULL);
                    return;
                }
            }
            i++;
        }
    }
}

bool exitProgram(char* tokens[], int numTokens){
    // removed the newlines on the exit keyword
    // this will exsit the program if the keyword is specifically called.
    if(!(strcmp(tokens[0], "exit\n\n")) && numTokens == 1){
        return true;
    }
    if(!strcmp(tokens[0], "exit\n\n")){
    printError();
    }
    return false;
}

void changeDirectories(char* tokens[], int numTokens){
    // checks for the 2nd token in the string array, and then removes the newlines off of it so it may be run correctly.
    if((!strcmp("cd", tokens[0])) && numTokens == 2){
        tokens[1][strlen(tokens[1])-1] = '\0';
        tokens[1][strlen(tokens[1])-1] = '\0';
        if(chdir(tokens[1]) == -1){
            printError();
        }
    }
    // if there is jsut "cd" and no specified path, then it will preint an error.
    if((!strcmp("cd\n\n", tokens[0])) && numTokens == 1){
        printError();
    }
}

void printHelp(char* str[], int index){
    // Help Sections
    // if help command it called, then this menu is printed to give users instruction on what they can do in the interactive terminal.
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
        char *trashTokens[30];


        Command = strchr(cmd, '>');

        if(Command != NULL){
            // = redirectCommand(cmd, cmd, isRedirect, trashTokens, trashTokens, isExits);
            if(Command == NULL){
                numTok = parseInput(dupCmd, trashTokens);
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
    launchProcesses(outputTokens, numTok, *isRedirect);    

    return Command;
}