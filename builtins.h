//
// Created by ioan on 05.04.2022.
//

#ifndef DSH_BUILTINS_H
#define DSH_BUILTINS_H

#include <stdio.h>

#define HELP "help"
#define EXIT "exit"
#define CURRENT_DIR "cd"
#define PRINT_CURRENT_DIR "pwd"
#define ENTRY_TYPE "type"
#define CREATE_ENTRY "create"


void help();

void exitSh(int code);

void cd(char *dir, const char *newDir);

void pwd(const char *cd);

void type(const char *cd, const char *file);

void create(const char* cd,const char* type,char* name,char* target,char* dir);

#endif //DSH_BUILTINS_H
