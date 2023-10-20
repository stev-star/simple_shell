#include "shell.h"

/**
 * Path - handles PATH, when cmd isn't a path like '/bin/'
 * @envp: the env pointer
 * @args: array of commands
 * @av: for the executable name
 */
void Path(char **envp, char **args, char **av)
{
	char *tokens, *path = getenv("PATH");
	char buffer[BUF];

	if (path == NULL)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}

	tokens = strtok(path, ":");
	while (tokens != NULL)
	{
		snprintf(buffer, sizeof(buffer), "%s/%s", tokens, args[0]);
		execve(buffer, args, envp);
		tokens = strtok(NULL, ":");
	}
	if (errno == ENOENT)
		fprintf(stderr, "%s: 1: %s: not found\n", av[0], args[0]);
	else
		perror(av[0]);
	exit(EXIT_FAILURE);
}
