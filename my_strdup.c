#include "shell.h"
/**
 * my_strdup - string duplication
 * @statement: string to be duplicated
 * Return: duplicated string
 */
char *my_strdup(const char *statement)
{
	size_t len = my_strlen(statement) + 1;
	char *new_string = (char *)malloc(len);
	size_t a = 0;

	if (new_string == NULL)
		return (NULL);

	for (; a < len; a++)
	{
		new_string[a] = statement[a];
	}
	return (new_string);
}
