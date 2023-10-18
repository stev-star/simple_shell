#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

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

#endif
