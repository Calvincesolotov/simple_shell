#include "shell.h"
/**
 * file_function - main function
 * @env:pointer to file
 * @filename:file to open
 * Return:always 0
 */

void file_function(const char *filename, char **env)
{
	FILE *file = fopen(filename, "r");
	char *line = NULL;
	size_t buffsize = 0;
	ssize_t read;
	(void)env;

	if (file == NULL)
	{
		fprintf(stderr, "Failed to open file: %s\n", filename);
		exit(EXIT_FAILURE);
	}

	while ((read = _getline(line, &buffsize, file)) != -1)
	{
		if (read > 0 && line[read - 1] == '\n')
		{
			line[read - 1] = '\0';
		}

	execfile(&line);
	}

	free(line);
	fclose(file);
}
