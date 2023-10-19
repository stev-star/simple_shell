#include "shell.h"

/**
 * npath - handles PATH, when cmd isn't a path like '/bin/'
 * @envp: the env pointer
 * @args: array of commands
 * @av: for the executable name
 */
void npath(char **envp, char **args, char **av)
{
	char *token, *path = getenv("PATH");
	char buffer[BUFFER];

	if (path == NULL)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}

	token = strtok(path, ":");
	while (token != NULL)
	{
		snprintf(buffer, sizeof(buffer), "%s/%s", token, args[0]);
		execve(buffer, args, envp);
		token = strtok(NULL, ":");
	}
	if (errno == ENOENT)
		fprintf(stderr, "%s: 1: %s: not found\n", av[0], args[0]);
	else
		perror(av[0]);
	exit(EXIT_FAILURE);
}
