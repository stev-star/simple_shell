#include "shell.h"

/**
 * my_environ - poppulates the envp array
 * @envp: the array of env variables
 * @env: environment variable
 */
void my_environ(char **envp, char **env)
{
	int num = 0;

	/**
	 * for (; env[num] != NULL; num++)
	 *	envp[num] = env[num];
	 * envp[num] = NULL;
	 */
	while (env[num] != NULL)
	{
		envp[num] = env[num];
		num++;
	}
	envp[num] = NULL;
}
