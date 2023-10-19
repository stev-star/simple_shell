#include "shell.h"

/**
 * _environ - poppulates the envp array
 * @envp: the array of env variables
 * @env: environment variable
 */
void _environ(char **envp, char **env)
{
	int count = 0;

	for (; env[count] != NULL; count++)
		envp[count] = env[count];
	envp[count] = NULL;
}
