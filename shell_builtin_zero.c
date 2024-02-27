#include "shell.h"

/**
 * exit_shell - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int exit_shell(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = string_interger(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "unallowed number: ");
			is_puts(info->argv[1]);
			print_putchar('\n');
			return (1);
		}
		info->err_num = string_interger(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * change_directory - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int change_directory(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		input_string("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _get_environment_variable(info, "HOME=");
		if (!dir)
			chdir_ret = 
				chdir((dir = _get_environment_variable(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_get_environment_variable(info, "OLDPWD="))
		{
			input_string(s);
			_putchar('\n');
			return (1);
		}
		input_string(_get_environment_variable(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = 
			chdir((dir = _get_environment_variable(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "unable to change to ");
		is_puts(info->argv[1]), print_putchar('\n');
	}
	else
	{
		_set_environment(info, "OLDPWD", _get_environment_variable(info, "PWD="));
		_set_environment(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * display_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int display_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	input_string("The Function is yet to be implemented \n");
	if (0)
		input_string(*arg_array);
	return (0);
}
