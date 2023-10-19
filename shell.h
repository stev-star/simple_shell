#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>

char *get_path(char *command);
extern char **environ;

/* For builtin*/
void builtin_cd(char *args);
void builtin_exit(void);
void err_msg(char *command);

size_t my_strlen(const char *statement);
void signal_handler(int signal);
char *my_strdup(const char *statement);
char *my_strcpy(char *new, char *original);
char *my_strcat(char *dest, char *str_to_copy);
int my_strcmp(const char *first_string, const char *comp_string);
ssize_t my_getline(char **buffer_ptr, size_t *buffer_size, FILE *input_stream);
/*void prompt_user(char **line, size_t *len);
void handle_commands(char *line, char ***command, size_t *i);
void tokenize_command(char *line, char ***command, size_t *max_command, size_t *i);
void allocate_space_for_command(char ***command, size_t *max_command, size_t i);
void check_program_name(char *line, char **path);
void search_directories(char **path, char ***directories, char *line, char ***command, size_t *max_directories, size_t *searching_i, size_t *found);
void search_directories(char **path, char ***directories, char **command, size_t *max_directories, size_t *searching_i, size_t *found);
void clean_up(char **command, char **dir, char **path_env_var, char **concat_path, char **line);
void handle_fork(char *path, char **command, char **direct_ries, size_t searching_i, char *line);*/
int split_command(const char *command, const char *delimiters, char **tokens, size_t max_tokens);
char *find_executable(const char *command, const char *path);
int execute_command(const char *command, char **tokens);


#endif
