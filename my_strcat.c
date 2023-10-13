#include "shell.h"

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
