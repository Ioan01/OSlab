//
// Created by ioan on 05.04.2022.
//

#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include "builtins.h"

#define MAX_PARAMETERS 10
#define MAX_COMMAND_LEN 64
#define MAX_PARAMETER_LEN 64


void hello()
{
    system("neofetch");
}


void shell(const char *dir)
{
    char exit = 0;

    char command[MAX_COMMAND_LEN];
    char parameters[MAX_PARAMETER_LEN];

    char *splitParameters[MAX_PARAMETERS][MAX_PARAMETER_LEN];


    //hello();
    while (!exit)
    {
        scanf("%[^ \n]%[^\n]%^s", command, parameters);

        if (!strcmp(command, HELP))
            help();
        else if (!strcmp(command, EXIT))
            exit = 1;
        else if (!strcmp(command, CURRENT_DIR))
            cd(dir, parameters);
        else if (!strcmp(command, PRINT_CURRENT_DIR))
            pwd(dir);
        else if (!strcmp(command, ENTRY_TYPE))
            type(dir, parameters);


    }
}

