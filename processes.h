//
// Created by ioan on 30.04.2022.
//

#ifndef DSH_PROCESSES_H
#define DSH_PROCESSES_H

#
#define COMMAND "run"
#define STATUS "status"


void run(char* argv[]);

void runPipes(char *argv[],int argvIndex);

#endif //DSH_PROCESSES_H
