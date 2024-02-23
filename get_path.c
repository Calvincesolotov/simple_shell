#include "shell.h"

/**
 * get_path - Function to get the path of a command
 * input_command: The command entered by the user
 * Return: The path of the command
 */

char *get_path(char *input_command)
{
	char *path, *duplicate_path, *path_token, *file_path;
	int input_command_length, directory_length;
	struct stat buffer;

	path = getenv("PATH");

	if (path)
	{
		/*Duplicate the path and don't forget to free*/
		duplicate_path = strdup(path);

		/*Get the length of the input_command*/
		input_command_length = strlen(input_command);

		/*
		* Tokenize the path. the ":" is the delimiter.
		* I am using my custom strtok function (string_tokenizer)
		*/
		path_token = strtok(duplicate_path, ":");

		while (path_token != NULL)
		{
			/*Get the directory length*/
			directory_length = strlen(path_token);

			/*Allocate memory for the input_command and the directory name*/
			/*We add 2 for the / and the null terminator character*/
			file_path = malloc(input_command_length + directory_length + 2);

			/*Copy the directory path and concatenate the input_command to it*/
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, input_command);
			strcat(file_path, "\0");

			/*
			* Test if the file path exists and return it if it does,
			* otherwise move to the next directory
			*/
			if (stat(file_path, &buffer) == 0)
			{
				/*Return value of 0 if successful*/
				/*free allocated memory before returning your file_path*/
				free(duplicate_path);
				return (file_path);
			}
			else
			{
				/*Free the file path memory so that we can look for another path*/
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		/*
		* If file path doesn't exist for the input_command return NULL
		* and free up memory for the duplicate_path
		*/
		free(duplicate_path);
		free(file_path);

		if (stat(input_command, &buffer) == 0)
		{
			return (input_command);
		}

		return (NULL);
	}

	return (NULL);

}
