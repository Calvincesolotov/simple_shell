#include "shell.h"

/*
 * custom_setenv - A custom setenv function
 * @variable name: The vairable name
 * @value: The value of the environment
 * Return: Nothing seeing that it is a void function
 */

void custom_setenv(const char *variable_name, const char *value)
{
	/*Checks if variable_name and value exist*/
	if (variable_name == NULL || value == NULL)
	{
		write(STDERR_FILENO, "setenv: Invalid arguments\n", 80);
		return;
	}

	/*A non zero return value indicates that it failed*/
	if (setenv(variable_name, value, 1) != 0)
	{
		write(STDERR_FILENO, "setenv: Setting environment variable failed\n", 80);
		return;
	}
}
