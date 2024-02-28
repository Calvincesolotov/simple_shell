#include "shell.h"

/**
 * interactive_shell - checks if shell is in interactive mode
 * @info: struct containing shell information
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive_shell(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * isdelimeter - checks if character is a delimiter
 * @c: character to check
 * @delim: delimiter string
 * Return: 1 if true, 0 if false
 */
int isdelimeter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * isalpha_char - checks if character is alphabetic
 * @c: character to check
 * Return: 1 if alphabetic, 0 otherwise
 */
int isalpha_char(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _string_interger - converts a string to an integer
 * @s: string to convert
 * Return: 0 if no numbers in string, converted number otherwise
 */
int _string_interger(char *s)
{
	int index, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (index = 0; s[index] != '\0' && flag != 2; index++)
	{
		if (s[index] == '-')
			sign *= -1;

		if (s[index] >= '0' && s[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
