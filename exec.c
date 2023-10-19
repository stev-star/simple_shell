#include "shell.h"
#include <errno.h>

/**
 * executeInput - executes the users commands
 * @cmds: the user input
 * @av: arg vector
 * @env: the env variable
 * Return: exit status
 */
int executeInput(char *cmds, char **av, char **env)
{
	char *args[BUFFER];
	int status, wxit;
	size_t count = 0;
	pid_t _child = fork();
	char *token, *envp[BUFFER];

	if (_child == -1)
	{
		perror("process failed");
		exit(EXIT_FAILURE);
	} else if (_child == 0)
	{
		token = strtok(cmds, " \n");
		while (token != NULL)
		{
			args[count++] = token;
			token = strtok(NULL, " \n");
		}
		args[count] = NULL;
		_environ(envp, env);
		if (strchr(args[0], '/') != NULL)
		{
			if (execve(args[0], args, envp) == -1)
			{
				if (errno == ENOENT || errno == EIO)
					fprintf(stderr, "%s: 1: %s: not found\n", av[0], args[0]);
				else
					perror(av[0]);
				exit(EXIT_FAILURE);
			}
		} else
			npath(envp, args, av);
	} else
	{waitpid(_child, &status, 0);
		if (WIFEXITED(status))
			wxit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			return (WTERMSIG(status));
	}
	return (wxit);
}
