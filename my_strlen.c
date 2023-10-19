#include "shell.h"
/**
 * my_strlen - string length
 * @statement: string
 * Return: length of the string.
 */
size_t my_strlen(const char *statement)
{
	size_t a = 0;

	while (statement[a] != '\0')
	{
		a++;
	}
	return (a);
}
