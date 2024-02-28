#include "shell.h"

/**
 * get_histo_information - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_histo_information(info_t *info)
{
	char *buf, *dir;

	dir = _get_environment_variable(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (string_length(dir) +string_length(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	string_copy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_histo_info - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_histo_info(info_t *info)
{
	ssize_t fd;
	char *filename = get_histo_information(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		print_input_string(node->str, fd);
		put_to_field('\n', fd);
	}
	put_to_field(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_hist_info - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_hist_info(info_t *info)
{
	int i, last = 0, count_lines = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_histo_information(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_histo_files(info, buf + last, count_lines++);
			last = i + 1;
		}
	if (last != i)
		build_histo_files(info, buf + last, count_lines++);
	free(buf);
	info->histcount = count_lines;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	reformat_history_number(info);
	return (info->histcount);
}

/**
 * build_histo_files - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @count_lines: the history count_lines, histcount
 *
 * Return: Always 0
 */
int build_histo_files(info_t *info, char *buf, int count_lines)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_to_end(&node, buf, count_lines);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * reformat_history_number - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int reformat_history_number(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
