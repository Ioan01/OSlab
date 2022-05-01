//
// Created by ioan on 05.04.2022.
//

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "builtins.h"
#include "processes.h"

#define MAX_PARAMETERS 10
#define MAX_COMMAND_LEN 64
#define MAX_PARAMETER_LEN 64


void hello()
{
    system("neofetch");
}

void cleanShell(char** splitParams) {
    for (int i = 0; i < MAX_PARAMETERS; ++i) {
        splitParams[i] = NULL;
    }
}



void shell(char *dir)
{
    dir[strrchr(dir,'/')-dir] = '\0';

    char* newDir = malloc(sizeof(char) * 1024);
    strcpy(newDir,dir);




    char exit = 0;

    char* input;
    char command[MAX_COMMAND_LEN];

    char *splitParameters[128];

    

    //hello();
    while (!exit)
    {
        cleanShell(splitParameters);

        printf("\n%s: ",newDir);
        gets(command);

        chdir(newDir);

        input = strtok(command," ");
        int index = 0;

        do {
            splitParameters[index] = strtok(NULL," ");
            index++;
        } while (splitParameters[index-1] != NULL);




        if (!strcmp(command,"hello"))
            hello();
        if (!strcmp(command, HELP))
            help();
        else if (!strcmp(command, EXIT))
            exit = 1;
        else if (!strcmp(command, CURRENT_DIR))
        {
            cd(newDir, splitParameters[0]);
            chdir(newDir);
        }

        else if (!strcmp(command, PRINT_CURRENT_DIR))
            pwd(newDir);
        else if (!strcmp(command, ENTRY_TYPE))
            type(newDir, splitParameters[0]);
        else if (!strcmp(command,CREATE_ENTRY))
            create(newDir,splitParameters[0],splitParameters[1],splitParameters[2],splitParameters[3]);
        else if (!strcmp(command,COMMAND))
            run(splitParameters);
        else if (!strcmp(command,STATUS))
            status();
        else printf("Command not found\n");



    }
}


