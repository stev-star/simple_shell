#include "shell.h"
/**
 * my_strlen - string length
 * @statement: string
 * gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hshReturn: number of characters in the specified string
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
