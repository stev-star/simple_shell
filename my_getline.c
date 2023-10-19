#include "shell.h"
size_t my_strlen(const char *str);

ssize_t my_getline(char **buffer_ptr, size_t *buffer_size, FILE *input_stream)
{
	char *line;
	ssize_t chars_read;

	if (*buffer_ptr == NULL || *buffer_size == 0)
	{
		*buffer_size = 1024;
		*buffer_ptr = malloc(*buffer_size);
		if (*buffer_ptr == NULL)
		{
			return (-1);
		}
	}

	line = fgets(*buffer_ptr, *buffer_size, input_stream);
	if (line != NULL)
	{
		chars_read = my_strlen(*buffer_ptr);
		if (chars_read > 0 && (*buffer_ptr)[chars_read - 1] == '\n')
		{
			(*buffer_ptr)[chars_read - 1] = '\0';
			chars_read--;
		}
		return (chars_read);
	}
	else
	{
		return (-1);
	}
}
