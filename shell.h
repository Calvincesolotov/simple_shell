#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

/* buffers */
#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024


/* command chaining directives*/
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* convert numbers() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/*using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to next node
 */typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;


typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* shell_looping.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* command utils file */
int is_executable(info_t *info, char *path);
char *duplicate_characters(char *path_string, int start, int stop);
char *find_command_path(info_t *info, char *path_string, char *command);


/* handle_errors.c */
void is_puts(char *string);
int print_putchar(char c);
int put_to_field(char c, int fd);
int print_input_string(char *string, int fd);

/* string_one.c file */
/*int _strlen(char *);*/
int string_length(char *s);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string_two.c file */
char *string_copy(char *dest, char *src);
char *_str_duplicate(const char *);
void input_string(char *str);
int _putchar(char);

/* shell_exits.c */
char *_sh_strncpy(char *dest, char *src, int n);
char *_sh_strncat(char *dest, char *src, int n);
char *_sh_strchr(char *s, char c);

/* shell_tokenizer.c file*/
char **split_strtow(char *, char *);
char **split_strtow2(char *, char);

/* reallocate.c */
char *_mem_set(char *s, char b, unsigned int n);
void _free(char **);
void *_reallocate_memory(void *, unsigned int, unsigned int);

/*memory.c file*/
int free_memory(void **ptr);

/*a-to-i-file.c*/
int interactive_shell(info_t *info);
int isdelimeter(char c, char *delim);
int isalpha_char(int c);
int _string_interger(char *s);

/* handle_errors1.c */
int string_interger(char *s);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_digit(long int num, int base, int flags);
void delete_commenting(char *buf);

/* shell_builtin_zero.c file*/
int exit_shell(info_t *info);
int change_directory(info_t *info);
int display_help(info_t *info);


/*shell_builtin_one.c */
int _print_history(info_t *info);
int _print_alias(list_t *node);
int _myalias(info_t *info);

/*signal handling.c file*/
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);




/* getinfo.c */
void clear_info_struct(info_t *info);
void set_info_struct(info_t *info, char **av);
void free_info_struct(info_t *info, int all);



/*manage_env.c file*/
int _print_environment(info_t *info);
char *_get_environment_variable(info_t *info, const char *name);
int _set_environment_variable(info_t *info);
int _unset_environment_variable(info_t *info);
int populate_environment_list(info_t *info);

/* get_environment.c file */
char **get_environment(info_t *info);
int _unset_environment(info_t *, char *);
int _set_environment(info_t *, char *, char *);

/* print_history.c file */
char *get_histo_information(info_t *info);
int write_histo_info(info_t *info);
int read_hist_info(info_t *info);
int build_histo_files(info_t *info, char *buf, int linecount);
int reformat_history_number(info_t *info);

/*listmanagement.c */
list_t *add_node_to_start(list_t **head, const char *str, int num);
list_t *add_node_to_end(list_t **head, const char *str, int num);
size_t print_list_strings(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);

/*listfile.c */
size_t list_len(const list_t *);
char **print_list_array(list_t *head);
size_t print_linked_list(const list_t *h);
list_t *node_begins_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
ssize_t find_node_indexing(list_t *head, list_t *node);


/*shell_vars.c*/
int is_chain_delimiter(info_t *info, char *buf, size_t *p);
void check_chain_continuation(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(info_t *info);
int replace_variables(info_t *info);
int replace_string(char **old, char *new);
#endif
