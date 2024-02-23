#include "shell.h"

/**
 * execfile - FUnction that executes a command using execve
 * @argv: Parameter
 * Return: Nothing
 */

void execfile(char **argv)
{
	char *input_command = NULL, *typed_input = NULL;

	if (argv)
	{
		/*
		 * Grab the input_command. 0, which is the first index
		 * is actually the typed_input
		 */

		input_command = argv[0];

		/*Generate the path to this command then pass it to execve*/
		typed_input = get_path(input_command);

		/*Now execute the command with execve. For now we will use NULL for env*/
		if (execve(typed_input, argv, NULL) == -1)
		{
			write(STDOUT_FILENO, "Error!\n", 80);
			exit(1);
		}

		else
		{
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("Execution failed");
				exit(EXIT_FAILURE);
			}

		}
	}
}
