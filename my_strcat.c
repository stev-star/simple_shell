#include "shell.h"
/**
 * my_strcat - Concatenates two strings.
 * @param dest The destination string.
 * @param str_to_copy The string to be copied.
 * @returns A pointer to the destination string.
 */
char *my_strcat(char *dest, char *str_to_copy)
{
	int a, b;

	a = 0;
	while (dest[a] != '\0')
		a++;

	b = 0;
	while (str_to_copy[b] != '\0')
	{
		dest[a] = str_to_copy[b];
		b++;
		a++;
	}
	dest[a] = '\0';
	return (str_to_copy);
}
