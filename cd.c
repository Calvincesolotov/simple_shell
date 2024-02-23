#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

/**
 * cd_command - A function that changes the directory in
 * a shell program
 * @dir_path: Directory path
 * Return: 0 if successful
 */

int cd_command(char *dir_path)
{
	/*_dir is the cwd*/
	char _dir[1024];/*1024 is the max input length of directory*/

	/*
	* We use getcwd to get the current working directory. The
	* return value is stored in _dir. A NULL return value indicates
	* an error.
	*/
	if (getcwd(_dir, sizeof(_dir)) == NULL)
	{
		perror("Error: getcwd");
		return (-1);
	}

	/*
	* We use chdir to change the directory. We pass the dir_path
	* as a parameter to represent the path specified directory path.
	* a return value of -1 prints an error
	*/
	if (chdir(dir_path) == -1)
	{
		perror("Error: chdir");
		return (-1);
	}

	/*
	* We use the setenv function to update the PWD. A return value of
	* -1 indicates an error
	*/
	if (setenv("PWD", _dir, 1) == -1)
	{
		perror("Error: setenv");
		return (-1);
	}

	return (0);
}
