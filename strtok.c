#include "shell.h"
/**
 * string_tokenizer - Function that tokenizes a string
 * @inputcommand: The users input command
 * @delim: The delimiter
 * @tokens:inputs
 * Return: Tokens and NULL if it failed
 */

int string_tokenizer(char *inputcommand, char **tokens, char *delim)
{
	int count_token = 0;
	char *start = inputcommand;

	while (inputcommand != NULL)
	{
		if (*inputcommand == *delim)
		{
			/*Replace delimiter with null terminator '\0'*/
			*inputcommand = '\0';
			tokens[count_token++] = start;
			/*Below start of the next token*/
			start = inputcommand + 1;
		}
		inputcommand++;

	}
	tokens[count_token++] = start;
	return (count_token);
}
