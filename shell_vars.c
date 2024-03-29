#include "shell.h"

/**
 * is_chain_delimiter - test if current char in buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_chain_delimiter(info_t *info, char *buf, size_t *p)
{
    size_t del_meter = *p;

    if (buf[del_meter] == '|' && buf[del_meter + 1] == '|')
    {
        buf[del_meter] = 0;
        del_meter++;
        info->cmd_buf_type = CMD_OR;
    }
    else if (buf[del_meter] == '&' && buf[del_meter + 1] == '&')
    {
        buf[del_meter] = 0;
        del_meter++;
        info->cmd_buf_type = CMD_AND;
    }
    else if (buf[del_meter] == ';') /* end of command */
    {
        buf[del_meter] = 0;
        info->cmd_buf_type = CMD_CHAIN;
    }
    else
        return (0);
    *p = del_meter;
    return (1);
}

/**
 * check_chain_continuation - checks if we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain_continuation(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t del_meter = *p;

    if (info->cmd_buf_type == CMD_AND)
    {
        if (info->status)
        {
            buf[i] = 0;
            del_meter = len;
        }
    }
    if (info->cmd_buf_type == CMD_OR)
    {
        if (!info->status)
        {
            buf[i] = 0;
            del_meter = len;
        }
    }

    *p = del_meter;
}

/**
 * replace_alias - replaces an alias in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
    int i;
    list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = node_begins_with(info->alias, info->argv[0], '=');
        if (!node)
            return (0);
        free(info->argv[0]);
        p = _sh_strchr(node->str, '=');
        if (!p)
            return (0);
        p = _str_duplicate(p + 1);
        if (!p)
            return (0);
        info->argv[0] = p;
    }
    return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_variables(info_t *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
            continue;

        if (!_strcmp(info->argv[i], "$?"))
        {
            replace_string(&(info->argv[i]),
                           _str_duplicate(convert_digit(info->status, 10, 0)));
            continue;
        }
        if (!_strcmp(info->argv[i], "$$"))
        {
            replace_string(&(info->argv[i]),
                           _str_duplicate(convert_digit(getpid(), 10, 0)));
            continue;
        }
        node = node_begins_with(info->env, &info->argv[i][1], '=');
        if (node)
        {
            replace_string(&(info->argv[i]),
                           _str_duplicate(_sh_strchr(node->str, '=') + 1));
            continue;
        }
        replace_string(&info->argv[i], _str_duplicate(""));

    }
    return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
    free(*old);
    *old = new;
    return (1);
}
