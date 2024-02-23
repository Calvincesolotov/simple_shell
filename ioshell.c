#include "shell.h"

/**
 * io_shell - Function that creates an interactive shell
 *@env: Environment parameter
 *Return: Nothing (void)
 */


void io_shell(char **env)
{
	char *line = NULL;
	size_t buffsize = 0;
	ssize_t read;
	(void)env;

	while (1)
	{
		write(STDOUT_FILENO, "cisfun$ ", 100);
		read = _getline(line, &buffsize, stdin);

		if (read == -1)
		{
			if (errno == 0)
			{
				break; /*EOF was reached with Ctrl+D*/
			}
			perror("getline");
			continue;
		}

	if (read > 0 && line[read - 1] == '\n')
	{
		line[read - 1] = '\0';
	}

	execfile(&line);
	}

	free(line);
}
