#include "shell.h"

/**
 * _print_environment - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _print_environment(info_t *info)
{
    print_list_strings(info->env);
    return (0);
}

/**
 * _get_environment_variable - gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: environment variable name
 *
 * Return: the value
 */
char *_get_environment_variable(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *p;

    while (node)
    {
        p = starts_with(node->str, name);
        if (p && *p)
            return (p);
        node = node->next;
    }
    return (NULL);
}

/**
 * _set_environment_variable - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _set_environment_variable(info_t *info)
{
    if (info->argc != 3)
    {
        is_puts("Incorrect number of arguments\n");
        return (1);
    }
    if (_set_environment(info, info->argv[1], info->argv[2]))
        return (0);
    return (1);
}

/**
 * _unset_environment_variable - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _unset_environment_variable(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        is_puts("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= info->argc; i++)
        _unset_environment(info, info->argv[i]);

    return (0);
}

/**
 * populate_environment_list - populates environment linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_environment_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_to_end(&node, environ[i], 0);
    info->env = node;
    return (0);
}
