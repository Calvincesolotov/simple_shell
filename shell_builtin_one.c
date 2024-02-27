#include "shell.h"

/**
 * _print_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _print_history(info_t *info)
{
	print_linked_list(info->history);
	return (0);
}

/**
 * _unset_alias - unsets an alias
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _unset_alias(info_t *info, char *str)
{
	char *equal_sign_position, c;
	int ret;

	equal_sign_position = _sh_strchr(str, '=');
	if (!equal_sign_position)
		return (1);
	c = *equal_sign_position;
	*equal_sign_position = 0;
	ret = delete_node_at_index(&(info->alias),
		find_node_indexing(info->alias, node_begins_with(info->alias, str, -1)));
	*equal_sign_position = c;
	return (ret);
}

/**
 * _set_alias - sets an alias
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _set_alias(info_t *info, char *str)
{
	char *equal_sign_position;

	equal_sign_position = _sh_strchr(str, '=');
	if (!equal_sign_position)
		return (1);
	if (!*++equal_sign_position)
		return (_unset_alias(info, str));

	_unset_alias(info, str);
	return (add_node_to_end(&(info->alias), str, 0) == NULL);
}

/**
 * _print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int _print_alias(list_t *node)
{
	char *equal_sign_position = NULL, *a = NULL;

	if (node)
	{
		equal_sign_position = _sh_strchr(node->str, '=');
		for (a = node->str; a <= equal_sign_position; a++)
			_putchar(*a);
		_putchar('\'');
		input_string(equal_sign_position + 1);
		input_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *equal_sign_position = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equal_sign_position = _sh_strchr(info->argv[i], '=');
		if (equal_sign_position)
			_set_alias(info, info->argv[i]);
		else
			_print_alias(node_begins_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
