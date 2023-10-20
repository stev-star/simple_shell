#include "shell.h"
#include <errno.h>

/**
 * executeCommand - executes the users commands
 * @cmds: the user input
 * @av: arg vector
 * @env: the env variable
 * Return: exit status
 */
int executeCommand(char *cmds, char **av, char **env)
{
	char *args[BUF];
	int status, wfit;
	size_t count = 0;
	pid_t child_pid = fork();
	char *tokens, *envp[BUF];

	if (child_pid == -1)
	{
		perror("process failed");
		exit(EXIT_FAILURE);
	} else if (child_pid == 0)
	{
		tokens = strtok(cmds, " \n");
		while (tokens != NULL)
		{
			args[count++] = tokens;
			tokens = strtok(NULL, " \n");
		}
		args[count] = NULL;
		my_environ(envp, env);
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
			Path(envp, args, av);
	} else
	{waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			wfit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			return (WTERMSIG(status));
	}
	return (wfit);
}
