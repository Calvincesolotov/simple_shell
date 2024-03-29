#include "shell.h"

/**
 * **split_strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **split_strtow(char *str, char *d)
{
	int i, j, k, m, word_count = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!isdelimeter(str[i], d) && (isdelimeter(str[i + 1], d) || !str[i + 1]))
			word_count++;

	if (word_count == 0)
		return (NULL);
	s = malloc((1 + word_count) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < word_count; j++)
	{
		while (isdelimeter(str[i], d))
			i++;
		k = 0;
		while (!isdelimeter(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **split_strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_strtow2(char *str, char d)
{
	int i, j, k, m, word_count = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			word_count++;
	if (word_count == 0)
		return (NULL);
	s = malloc((1 + word_count) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < word_count; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
