#include "shell.h"

/**
 * main - Entry point
 * @ac: counter
 * @av: arg vector
 * @env: the environ variable
 * Return: 0 - Success
 */
int main(int ac __attribute__((unused)), char **av, char **env)
{
	char input[BUFFER];
	int interactive = isatty(STDIN_FILENO);
	int estat;

	while (1)
	{
		if (interactive)
			printf("cisfun$ "); /* only prints in interactive mode */

		/* collects user input */
		if (!readInput(input, sizeof(input)))
		{
			/* exit loop on EOF or invalid input */
			if (interactive)
				printf("\n");
			exit(0);
		}

		if (strcmp(input, "exit") == 0)
			exit(EXIT_SUCCESS);

		/* executes user command */
		estat = executeInput(input, av, env);
	}

	return (estat);
}
