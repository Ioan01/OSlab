//
// Created by ioan on 30.04.2022.
//

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "processes.h"

int* _status = NULL;

void run(char * argv[])
{
    int pid = fork();

    if (pid < 0)
    {
        printf("Error\n");
    }
    else if (pid==0)
    {
        execlp(argv[0],argv[0],argv[1],argv[2],argv[3],argv[4],argv[5],NULL);
        exit(0);
    }
    int status;
    waitpid(pid,&status,0);

    if (!_status)
        _status = malloc(sizeof(int));
    *_status = status;
}

void status()
{
    if (!_status)
        printf("No command ran yet\n");
    else printf("%d \n",*_status);
}
