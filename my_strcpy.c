#include "shell.h"

char *my_strcpy(char *new, char *original)
{
        int a = 0, length;

        length = 0;
        while (original[length] != '\0')
                length++;

        for (; a < length; a++)
		new[a] = origin[a];

	new[a] = '\0';

	return (new);
}
