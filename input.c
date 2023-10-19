#include "shell.h"

/**
 * readInput - collects user input
 * @input: the user input
 * @size: the sizeof(user input)
 * Return: 0 if getline failed, 1 if success
 */
int readInput(char *input, size_t size)
{
	int i = getline(&input, &size, stdin);

	if (input[strlen(input) - 1] == '\n')
		input[strlen(input) - 1] = '\0';

	if (i == -1)
		return (0);
	return (1);
}
