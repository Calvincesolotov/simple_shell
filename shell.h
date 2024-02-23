#ifndef _SHELL_H
#define _SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

/*These are the function prototypes for our simple shell program*/

int msg_print(void);
void execfile(char **argv);
char *get_path(char *input_command);
ssize_t _getline(char *command, size_t *size, FILE *stdin);
int cd_command(char *dir_path);
void free_argv(char **argv);
void custom_setenv(const char *variable_name, const char *value);
void custom_unsetenv(const char *variable_name);
int string_tokenizer(char *inputcommand, char **tokens, char *delim);
void custom_alias(int argc, char *argv[]);
void print_aliases(void);
void print_alias(const char *name);
extern char **environ;
void replace_var(char *command, int exit_status);
void io_shell(char **env);
void file_function(const char *filename, char **env);

#endif

