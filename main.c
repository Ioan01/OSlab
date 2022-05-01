#include <stdio.h>
#include "shell.h"


int main(int argc, char **argv)
{
    printf("%d %s",argc,argv[0]);
    shell(argv[0]);
    return 0;
}
