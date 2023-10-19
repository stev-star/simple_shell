#include "shell.h"
/**
 * Copies a string to another string.
 * @param new The destination string.
 * @param original The string to be copied.
 * @returns A pointer to the destination string.
 **/
char *my_strcpy(char *new, char *original)
{
	int a = 0, length;

	length = 0;
	while (original[length] != '\0')
		length++;

	for (; a < length; a++)
		new[a] = original[a];

	new[a] = '\0';

	return (new);
}
