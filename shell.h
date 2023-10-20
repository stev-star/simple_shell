#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define BUF 1024

int Input(char *input, size_t size);
int executeCommand(char *cmds, char **av, char **env);
int nexecuteInput(char *cmds, char **av, char **env);
void my_environ(char **envp, char **env);
void Path(char **envp, char **args, char **av);

#endif /*SHELL_H*/
