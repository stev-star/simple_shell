#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define BUFFER 51200

int readInput(char *input, size_t size);
int executeInput(char *cmds, char **av, char **env);
int nexecuteInput(char *cmds, char **av, char **env);
void _environ(char **envp, char **env);
void npath(char **envp, char **args, char **av);

#endif /*SSHELL_H*/
