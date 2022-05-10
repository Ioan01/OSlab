//
// Created by ioan on 30.04.2022.
//

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <uv/unix.h>
#include "processes.h"

int* _status = NULL;

void run(char * argv[])
{

    int index = 0;
    while (argv[index] != 0)
    {
        if (argv[index][0] == '|')
        {
            runPipes(argv,index);
            return;
        }
        index++;
    }


    int pid = fork();

    if (pid < 0)
    {
        printf("Error\n");
    }
    else if (pid==0)
    {
        execvp(argv[0],argv);
        exit(0);
    }
    int status;
    waitpid(pid,&status,0);

    if (!_status)
        _status = malloc(sizeof(int));
    *_status = status;
}

void runPipes(char *argv[],int argvIndex)
{
    int p_fd[2];


    if (pipe(p_fd) < 0)
    {
        printf("Error\n");
        return;
    }


    int pid = fork();

    if (pid < 0)
    {
        printf("Error\n");
    }
    else if (pid==0)
    {
        close(p_fd[0]);

        dup2(fileno(stdin),p_fd[1] );


        argv[argvIndex-1] = 0;
        execvp(argv[0],argv);


        close(p_fd[1]);
        exit(0);
    }


    pid = fork();

    if (pid < 0)
    {
        printf("Error\n");
    }
    else if (pid==0)
    {
        close(p_fd[1]);

        dup2(fileno(stdout),p_fd[0]);

        execvp(argv[argvIndex+1],&argv[argvIndex+1]);


        close(p_fd[0]);
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
