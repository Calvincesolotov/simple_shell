#include "shell.h"

/**
 * custom_unsetenv - A custom_unsetenv function
 * @variable_name: The variable name
 * Return: Nothing seeing that the function is a void function
 */

void custom_unsetenv(const char *variable_name)
{
	/*Checks if the variable_name exists*/
	if (variable_name == NULL)
	{
		write(STDERR_FILENO, "unsetenv: Argument not valid\n", 80);
		return;
	}

	/*A non zero return value shows that it failed*/
	if (unsetenv(variable_name) != 0)
	{
		write(STDERR_FILENO, "unsetenv: Failed\n", 80);
		return;
	}
}
