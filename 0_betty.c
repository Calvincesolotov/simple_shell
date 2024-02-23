#include <unistd.h>
#include "shell.h"

/**
 * msg_print - Function that prints message
 * to the standard output file descriptor
 * Return: 0 if succesful
 */

int msg_print(void)
{
	char task0[] = "A code that passes betty checks\n";

	write(STDOUT_FILENO, task0, sizeof(task0) - 1);

	return (0);
}
