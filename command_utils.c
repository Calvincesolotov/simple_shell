#include "shell.h"

/**
 * is_executable - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_characters - duplicates characters
 * @path_string: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicate_characters(char *path_string, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (path_string[i] != ':')
			buf[k++] = path_string[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_command_path - finds this command in the PATH string
 * @info: the info struct
 * @path_string: the PATH string
 * @command: the command to find
 *
 * Return: full path of command if found or NULL
 */
char *find_command_path(info_t *info, char *path_string, char *command)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!path_string)
		return (NULL);
	if ((string_length(command) > 2) && starts_with(command, "./"))
	{
		if (is_executable(info, command))
			return (command);
	}
	while (1)
	{
		if (!path_string[i] || path_string[i] == ':')
		{
			path = duplicate_characters(path_string, curr_pos, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (is_executable(info, path))
				return (path);
			if (!path_string[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
