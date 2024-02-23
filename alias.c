#include "shell.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * custom_alias - Function for a custom alias builtin command
 * @argc: Argument count
 * @argv: Number of arguments
 * Return: Nothing since it's a void function
 */

void custom_alias(int argc, char *argv[])
{
	if (argc == 1)
	{
		print_aliases();
	}
	else
	{
		int x;

		for (x = 1; x < argc; x++)
		{
			char *name = strtok(argv[x], "-");
			char *value = strtok(NULL, "-");

			if (value == NULL)
			{
				/*Print the alias*/
				print_alias(name);
			}
			else
			{
				custom_setenv(name, value);
			}
		}
	}
}

/**
 * print_aliases - Function that prints the aliases name, name2, etc
 * 1 per line, in the form name='value'
 * Return: void
 */

void print_aliases(void)
{
	char **env_ptr = environ;

	while (*env_ptr != NULL)
	{
		char *name = strtok(*env_ptr, "=");
		char *value = strtok(NULL, "=");

		if (name != NULL && value != NULL)
		{
			char alias_output[1024];
			int len = snprintf
			(alias_output, sizeof(alias_output), "%s='%s'\n", name, value);

			write(STDOUT_FILENO, alias_output, len);
		}

		env_ptr++;
	}
}

/**
 * print_alias - Function that prints an alias one per line
 * @name: in the form name='value'
 * Return: void
 */

void print_alias(const char *name)
{
	char *value = getenv(name);

	if (value != NULL)
	{
		char alias_output[1024];
		int len = snprintf(alias_output,
		sizeof(alias_output), "%s='%s'\n", name, value);

		write(STDOUT_FILENO, alias_output, len);
	}
	else
	{
		char alias_not_found_output[1024];

		int len = snprintf(
			alias_not_found_output, sizeof(
				alias_not_found_output), "Alias '%s' not found\n", name);

		write(STDOUT_FILENO, alias_not_found_output, len);
	}
}
