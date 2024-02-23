#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void free_argv(char **argv)
{
    int z = 0;
    while (argv[z] != NULL)
    {
        free(argv[z]);
        z++;
    }
    free(argv);
}
