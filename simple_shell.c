#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define ALLOWED_LENGTH_OF_INPUT 1024

/**
 * main - The main function for the simple shell
 * argc: The number of arguments in the function
 * argv: Contains the arguments passed
 * env: Defines the characteristics of a specific environment
 * Return: 0 if successful
 */


int main(int argc, char *argv[], char **env)
{
	/*char input[ALLOWED_LENGTH_OF_INPUT];*/
	/*Below holds the address of the input line and*/
	/*the duplicate line that will be used for tokenization*/
	char *line = NULL, *duplicate_line =  NULL;
	char prompt[] = "cisfun$ ";/*Define the prompt*/
	/*Below find the length of the prompt and exclude the null terminator*/
	size_t prompt_length = sizeof(prompt) - 1;
	size_t buffsize = 0;/*Initial allocated buffer size in bytes*/
	ssize_t input_characters;/*The input entered by the user*/
	char *delim = " ,;,&&,||";
	int x_tokens = 0;/*The number of tokens*/
	char *token;
	int a;
	int exit_status = 0;
	char *filename;
	pid_t pid;
	/*Below takes care of unused parameter compilation warning*/
	(void)argc;
	(void)env;



	if (argc == 2)
	{
		filename = argv[1];
		file_function(filename, env);
	}
	else
	{


	while (1)/*While true creates an infinite loop*/
	{
		/*First print the prompt on the terminal*/
		write(STDOUT_FILENO, prompt, prompt_length);

		/*
		*getline function is called with the address of'/
		*the line and buffsize address
		*Return value of getline is stored in input_characters.
		*It contains the number of characters read, the newline
		*character ('\n') and '-1' if an error occured or even end of file
		*was reached
		*/

		line = malloc(sizeof(char) * buffsize);

		input_characters = _getline(line, &buffsize, stdin);

		/*Handling the # comments*/
		/*Check if the command is a comment (#)*/
		if (line[0] == '#')
		{
			/*Skip the execution of comments*/
			free(line);
			continue;
		}

		/*Now we check if the getline function failed or reached EOF using CTR+D*/
		if (input_characters == -1)
		{
			write(STDOUT_FILENO, "There was an error reading the input.\n", 80);
			return (1);
		}

		/*Allocate space for the duplicate_line*/
		duplicate_line = malloc(sizeof(char) * input_characters);

		if (duplicate_line == NULL)
		{
			perror("tsh: Error");
			return (-1);
		}

		/*Copy line to duplicate_line*/
		strcpy(duplicate_line, line);

		/*Tokenize the string (line) and get the*/
		/* total number of tokens[Length of string]*/
		/*delim stands for delimiter and it is what separates the string eg a space*/
		/*or a semicolon*/

		x_tokens = 0;

		token = strtok(line, delim);

		while (token != NULL)
		{
			x_tokens++;
			token = strtok(NULL, delim);
		}
		x_tokens++;

		/*Create space to hold the array of strings*/
		argv = malloc(sizeof(char *) * x_tokens);

		/*Now store each token in the argv array*/
		token = strtok(duplicate_line, delim);

		for (a = 0; token != NULL; a++)
		{
			/*We add +1 to account for the null terminator*/
			argv[a] = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(argv[a], token);

			token = strtok(NULL, delim);
		}

		argv[a] = NULL;

		/*Implementing the exit function to exit the shell when the user types exit*/
		if (strcmp(argv[0], "exit") == 0)/*argv[0] is the first argument*/
		{
			/*Free the allocated memory*/
			free(duplicate_line);
			free_argv(argv);
			free(line);

			/*Implementing arguments to the built in exit function*/
			if (argv[1] != NULL)/*argv[1] is the second argument*/
			{
				/*Use atoi to convert the argument to an integer*/
				int argument = atoi(argv[1]);

				exit(argument);
			}

			/*No argument was provided and so just exit the shell*/
			else
			{
				/*Exit the shell*/
				exit(0);
			}
		}

		/*Implementing the env function to print the current environment*/
		else if (strcmp(argv[0], "env") == 0)
		{
			char **env_ptr = env;

			while (*env_ptr != NULL)
			{
				write(STDOUT_FILENO, *env_ptr, strlen(*env_ptr));
				write(STDOUT_FILENO, "\n", 1);
				env_ptr++;
			}

		/*Free the allocated memory*/
		free(duplicate_line);
		argv[a] = NULL;
		free(argv);

		}

		/*Implementing the custom_setenv builtin command*/
		else if (strcmp(argv[0], "setenv") == 0)
		{
			if (argv[1] != NULL && argv[2] != NULL)
			{
				custom_setenv(argv[1], argv[2]);
			}
			else
			{
				write(STDERR_FILENO, "setenv: Arguments not valid\n", 80);
			}
		}

		/*Implementing the custom_unsetenv builtin command*/

		else if (strcmp(argv[0], "unsetenv") == 0)
		{
			if (argv[1] != NULL && argv[2] != NULL)
			{
				custom_unsetenv(argv[1]);
			}
			else
			{
				write(STDERR_FILENO, "unsetenv: Arguments not valid\n", 80);
			}
		}

		/*Implementing the builtin cd command*/
		else if (strcmp(argv[0], "cd") == 0)
		{
			char *dir = argv[1];/*The second index, which is the second argument*/

			if (dir == NULL) /*Means no argument is given to cd*/
			{
				/*Take the user to HOME directory*/
				dir = getenv("HOME");
			}

			else if (strcmp(dir, "-") == 0)
			{
				dir = getenv("OLDPWD");

			}

			/*
			* 0 indicates that it was successful. We use the setenv to
			* updated the OLDPWD with the value of PWD
			*/

			if (cd_command(dir) == 0)
			{
				if (setenv("OLDPWD", getenv("PWD"), 1) == -1)
				{
					perror("Error: setenv");
					return (-1);
				}
			}

		}

		/*Implementing the builtin alias command*/
		else if (strcmp(argv[0], "alias") == 0)
		{
			custom_alias(a, argv);
			free_argv(argv);
			free(line);
		}

		replace_var(line, exit_status);

		/*Now it is time to fork a new process. The fork function is used to create*/
		/*A copy of the current parent process. The new process is called the child*/
		/*In the parent process, fork returns the process id (pid)*/
		/*The child returns 0*/

		pid = fork();

		if (pid < 0)
		{
			perror("Error\n");
			continue;
		}
		else if (pid == 0)
		{
			/*If fork() returns 0, that means we are in the child process and so we*/
			/*Call the execfile function to Execute the commands*/
			execfile(argv);
		}
		else
		{
			/*Call the parent process using wait when the child process finishes*/
			wait(NULL);
		}

		free(duplicate_line);
		free(argv);
	}

	}
	/*Free up the memory that was allocated dynamically*/
	free(line);
	return (0);
}
