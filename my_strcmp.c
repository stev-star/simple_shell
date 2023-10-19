#include "shell.h"
/**
 * Compares two strings.
 * @param first_string The first string to compare.
 * @param comp_string The second string to compare.
 * @returns A negative value if the first string is less than the second string, 
 * a zero value if the two strings are equal, 
 * and a positive value if the first string is greater than the second string.
 */
int my_strcmp(const char *first_string, const char *comp_string)
{
	while (*first_string && *comp_string && *first_string == *comp_string)
	{
		first_string++;
		comp_string++;
	}

	return ((int)(*first_string - *comp_string));
}
