#include "shell.h"

int my_strcmp(const char *first_string, const char *comp_string)
{
	while (*first_string && *comp_string && *first_string == *comp_string)
	{
		first_string++;
		second_string++;
	}

	return ((int)(*first_string - *comp_string));
}
