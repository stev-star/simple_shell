#include "shell.h"
/**
 * Reads a line of text from the input stream and stores it in the buffer
 * @param buffer_ptr A pointer to the buffer where the line of text will be stored.
 * @param buffer_size The size of the buffer in bytes.
 * @param input_stream The input stream to read from.
 * @returns The number of characters read, or -1 if an error occurs.
 */
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
