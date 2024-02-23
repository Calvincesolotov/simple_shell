#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

#define MAX_INPUT_LENGTH 1024

/**
 * getline - Function that reads commands from the user
 * command: The buffer to store the typed command or input
 * buffersize: The size of the command buffer
 * Return: Number of characters read, excluding
 * the null terminator or -1 if it failed
 */

ssize_t _getline(char *command, size_t *size, FILE *stdin)
{
	static char buffer[MAX_INPUT_LENGTH];
	static size_t i = 0;/*The index*/
	static ssize_t input = 0;

	ssize_t len = 0;

	while ((size_t) len < (*size - 1))
	{
		if (i >= (size_t) input)
		{
			/*We use the read function to read the users input*/
			input = read(fileno(stdin), buffer, sizeof(buffer));
			if (input <= 0)
			{
				return (-1);
			}

			i = 0;
		}

		/*Copy the next character from the buffer to the command*/
		command[len] = buffer[i++];

		/*Now to handle the end of line character '\n'*/
		if (command[len] == '\n')
		{
			break;
		}
		len++;
	}
	command[len] = '\0';

	return (len);
}
