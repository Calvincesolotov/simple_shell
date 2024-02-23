#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * replace_var - Function that handles variables replacement
 * command: The input command
 * exit_status: The exit status integer
 * Return: Nothing (void)
 */

void replace_var(char *command, int exit_status)
{
	int a;
	int b;
	int x;
	int y;
	size_t var_len;
	size_t replacement_len;
	char *pid_position;
	char *path_position;
	char *path_value;



	/*First, we get the position of the $? variable in the command*/
	char *exit_status_position = strstr(command, "$?");

	/*Next, we check if the $? variable was found*/
	if (exit_status_position != NULL)
	{
	/*Convert the exit status to a string*/
	char exit_status_str[100]; /*Max length of exit status is 100*/
	int exit_status_len = 0;/*Length of the exit_status*/
	int temp_status = exit_status;

	/*Next we take care of negative exit status with the symbol '-'*/
	if (exit_status < 0)/*That means a negative*/
	{
		exit_status_str[0] = '-';
		exit_status_len++;
		temp_status = -temp_status;
	}

	/*Next we get the number of digits in the exit status*/
	do {
		exit_status_str[exit_status_len++] = '0' + (temp_status % 10);/*Modulo 10*/
		temp_status /= 10;
	} while (temp_status > 0);

	/*Next we reverse the string*/

	for (a = 0, b = exit_status_len - 1; a < b; a++, b--)
	{
		char temp = exit_status_str[a];

		exit_status_str[a] = exit_status_str[b];
		exit_status_str[b] = temp;
	}

	/*Now we replace the variable with the exit status*/
	var_len = strlen(exit_status_position);/*variable length*/
	replacement_len = exit_status_len;

	memmove(exit_status_position + replacement_len, exit_status_position + 2, var_len - 1);
	memcpy(exit_status_position, exit_status_str, replacement_len);
	}
	/*We go over the same process for the $$ variable*/

	/*Get the position of the $$ variable in the command*/
	pid_position = strstr(command, "$$");/*pid_pos- Process id position*/

	/*Check if the variable was found*/
	if (pid_position != NULL)
	{
	/*Get the process ID (PID)*/
	int pid = getpid();

	/*Convert the PID to a string*/
	char pid_str[100];/*Max length of the pid is 100*/
	int pid_len = 0;/*Pid length*/
	int temp_pid = pid;

	/*Get the number of digits in the PID*/
	do {
		pid_str[pid_len++] = '0' + (temp_pid % 10);/*Modulo 10*/
		temp_pid /= 10;
	} while (temp_pid > 0);

	/*Reverse the string*/

	for (x = 0, y = pid_len - 1; x < y; x++, y--)
	{
		char temp = pid_str[x];

		pid_str[x] = pid_str[y];
		pid_str[y] = temp;
	}

	/*Now replace the variable with the PID*/
	var_len = strlen(pid_position);
	replacement_len = pid_len;

	memmove(pid_position + replacement_len, pid_position + 2, var_len - 1);
	memcpy(pid_position, pid_str, replacement_len);
	}

	/*Now we handle the variable expansion*/

	/*Get the position of the $PATH variable in the command*/
	path_position = strstr(command, "$PATH");

	/* Check if the $PATH variable was found */
	if (path_position != NULL)
	{
		/*Get the value of the PATH environment variable */
		path_value = getenv("PATH");

		/* Replace the $PATH variable with its value */
		var_len = strlen(path_position);/*Variable length*/
		replacement_len = strlen(path_value);/* Replacement length*/

		memmove(path_position + replacement_len, path_position + 5, var_len - 4);
		memcpy(path_position, path_value, replacement_len);
	}
}
